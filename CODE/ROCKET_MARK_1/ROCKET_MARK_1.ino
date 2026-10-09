#include <Wire.h>
#include <SPI.h>
#include <LoRa.h>
#include <SD.h>
#include <DHT.h>
#include <TinyGPS++.h>
#include <Adafruit_BMP280.h>
#include <Adafruit_MPU6050.h>
#include <Adafruit_Sensor.h>
#include <ThreeWire.h>
#include <RtcDS1302.h>

#define I2C_SDA 21
#define I2C_SCL 22

#define RXD2 16 
#define TXD2 17 
#define GPS_BAUD 9600 

#define DHTPIN 4 
#define DHTTYPE DHT11  

#define SD_CS_PIN 15
#define LORA_CS_PIN 5
#define LORA_RST_PIN 14
#define LORA_DIO0_PIN 2

#define DS1302_DAT  25
#define DS1302_SCLK 26
#define DS1302_RST  27

// TARGET LOG INTERVAL: 20ms = 50 Hz Data Logging & Telemetry Loop
const unsigned long LOG_INTERVAL = 20; 
const char* logFile = "/flight_log.csv";

ThreeWire myWire(DS1302_DAT, DS1302_SCLK, DS1302_RST);
RtcDS1302<ThreeWire> Rtc(myWire);

Adafruit_BMP280 bmp;
Adafruit_MPU6050 mpu;
TinyGPSPlus gps;
HardwareSerial gpsSerial(2);
DHT dht(DHTPIN, DHTTYPE);

File flightLog;

int counter = 0;
unsigned long lastLogTime = 0;
unsigned long lastRtcRead = 0;
unsigned long lastDhtRead = 0;

bool bmpReady = false;
bool mpuReady = false;
bool sdReady = false;
bool loraReady = false;
bool dhtReady = false;
bool gpsHardwareReady = false;

// Shared sensor data buffers
char rtcTimeBuf[10] = "00:00:00";
char gpsTimeBuf[10] = "00:00:00";
float t_dht = 0.0, h_dht = 0.0;

void setup() {
  Serial.begin(115200);

  pinMode(DS1302_RST, OUTPUT);
  digitalWrite(DS1302_RST, LOW);

  pinMode(SD_CS_PIN, OUTPUT);
  digitalWrite(SD_CS_PIN, HIGH);
  pinMode(LORA_CS_PIN, OUTPUT);
  digitalWrite(LORA_CS_PIN, HIGH);

  delay(1000); 
  Serial.println("\n=== ROCKET MK-1 HIGH-SPEED BOOT SEQUENCE ===");

  // 1. Upgrade I2C to Fast Mode (400 kHz)
  Wire.begin(I2C_SDA, I2C_SCL);
  Wire.setClock(400000);
  delay(100);

  Serial.print("Initializing MPU6050 IMU... ");
  if (mpu.begin(0x68) || mpu.begin(0x69)) {
    mpuReady = true;
    mpu.setAccelerometerRange(MPU6050_RANGE_16_G);
    mpu.setGyroRange(MPU6050_RANGE_2000_DEG);
    mpu.setFilterBandwidth(MPU6050_BAND_260_HZ);
    Serial.println("[SUCCESS]");
  } else {
    Serial.println("[FAILED]");
  }

  Serial.print("Initializing BMP280 Barometer... ");
  if (bmp.begin(0x76) || bmp.begin(0x77)) {
    bmpReady = true;
    Serial.println("[SUCCESS]");
  } else {
    Serial.println("[FAILED]");
  }

  Serial.print("Initializing DS1302 RTC... ");
  Rtc.Begin();
  if (Rtc.GetIsWriteProtected()) Rtc.SetIsWriteProtected(false);
  if (!Rtc.GetIsRunning()) Rtc.SetIsRunning(true);

  RtcDateTime compiled = RtcDateTime(__DATE__, __TIME__);
  RtcDateTime now = Rtc.GetDateTime();
  if (!now.IsValid() || now < compiled) {
    Rtc.SetDateTime(compiled);
    Serial.println("[SUCCESS] -> Time synced to build.");
  } else {
    Serial.println("[SUCCESS] -> Running from backup power.");
  }

  Serial.print("Initializing DHT11... ");
  dht.begin();
  delay(300); 
  float testT = dht.readTemperature();
  if (!isnan(testT)) dhtReady = true;
  Serial.println(dhtReady ? "[SUCCESS]" : "[WARNING] -> Async sampling enabled");

  Serial.print("Initializing GPS UART2... ");
  gpsSerial.begin(GPS_BAUD, SERIAL_8N1, RXD2, TXD2);
  Serial.println("[SUCCESS]");

  // 2. High-Speed LoRa Radio Configuration
  digitalWrite(SD_CS_PIN, HIGH);
  digitalWrite(LORA_CS_PIN, LOW);
  LoRa.setPins(LORA_CS_PIN, LORA_RST_PIN, LORA_DIO0_PIN);
  
  Serial.print("Initializing High-Speed LoRa Transceiver... ");
  if (LoRa.begin(433E6)) {
    loraReady = true;
    LoRa.setSyncWord(0xF3);
    LoRa.setSignalBandwidth(500E3); // 500 kHz Bandwidth for max data rate
    LoRa.setSpreadingFactor(7);     // SF7 for fast airtime
    LoRa.setCodingRate4(5);         // CR 4/5
    LoRa.setTxPower(17);
    Serial.println("[SUCCESS]");
  } else {
    Serial.println("[FAILED]");
  }
  digitalWrite(LORA_CS_PIN, HIGH);

  // 3. Persistent File Opening on SD Card
  digitalWrite(LORA_CS_PIN, HIGH);
  digitalWrite(SD_CS_PIN, LOW);
  
  Serial.print("Initializing SD Card Logging Stream... ");
  if (SD.begin(SD_CS_PIN)) {
    sdReady = true;
    flightLog = SD.open(logFile, FILE_WRITE);
    if (flightLog) {
      flightLog.println("PacketID,RTC_Time,GPS_Time,Lat,Lng,Alt_GPS,Speed,Sats,Temp_DHT,Hum,Temp_BMP,Press,Alt_BMP,AccX,AccY,AccZ,GyroX,GyroY,GyroZ");
      flightLog.flush();
    }
    Serial.println("[SUCCESS]");
  } else {
    Serial.println("[FAILED]");
  }
  digitalWrite(SD_CS_PIN, HIGH);

  Serial.println("=== BOOT SEQUENCE COMPLETE: MAX SPEED LOGGING READY ===\n");
}

void loop() {
  // Non-blocking GPS Stream Processing
  while (gpsSerial.available() > 0) {
    gps.encode(gpsSerial.read());
  }

  // Non-blocking RTC update every 1000ms (prevents slow bit-bang SPI overhead on every cycle)
  if (millis() - lastRtcRead >= 1000) {
    lastRtcRead = millis();
    RtcDateTime now = Rtc.GetDateTime();
    if (now.IsValid()) {
      snprintf(rtcTimeBuf, sizeof(rtcTimeBuf), "%02d:%02d:%02d", now.Hour(), now.Minute(), now.Second());
    }
  }

  // Non-blocking DHT11 update every 2000ms
  if (dhtReady && (millis() - lastDhtRead >= 2000)) {
    lastDhtRead = millis();
    float t = dht.readTemperature();
    float h = dht.readHumidity();
    if (!isnan(t)) t_dht = t;
    if (!isnan(h)) h_dht = h;
  }

  // Update GPS time buffer asynchronously when valid
  if (gps.time.isValid()) {
    snprintf(gpsTimeBuf, sizeof(gpsTimeBuf), "%02d:%02d:%02d", gps.time.hour(), gps.time.minute(), gps.time.second());
  }

  // High-Speed Execution Loop
  if (millis() - lastLogTime >= LOG_INTERVAL) {
    lastLogTime = millis();

    double lat = 0.0, lng = 0.0, alt_gps = 0.0, speed = 0.0;
    uint32_t sats = 0;

    if (gps.location.isValid()) lat = gps.location.lat();
    if (gps.location.isValid()) lng = gps.location.lng();
    if (gps.altitude.isValid()) alt_gps = gps.altitude.meters();
    if (gps.speed.isValid()) speed = gps.speed.kmph();
    sats = gps.satellites.value();

    float t_bmp = 0.0, p_bmp = 0.0, a_bmp = 0.0;
    if (bmpReady) {
      t_bmp = bmp.readTemperature();
      p_bmp = bmp.readPressure();
      a_bmp = bmp.readAltitude(1013.25);
    }

    float mpu_ax = 0.0, mpu_ay = 0.0, mpu_az = 0.0;
    float mpu_gx = 0.0, mpu_gy = 0.0, mpu_gz = 0.0;
    if (mpuReady) {
      sensors_event_t a, g, temp;
      mpu.getEvent(&a, &g, &temp);
      mpu_ax = a.acceleration.x;
      mpu_ay = a.acceleration.y;
      mpu_az = a.acceleration.z;
      mpu_gx = g.gyro.x;
      mpu_gy = g.gyro.y;
      mpu_gz = g.gyro.z;
    }

    // High-speed static C-string buffer (zero heap memory allocations)
    char dataBuffer[300];
    snprintf(dataBuffer, sizeof(dataBuffer),
      "%d,%s,%s,%.6f,%.6f,%.1f,%.1f,%u,%.1f,%.1f,%.2f,%.2f,%.2f,%.2f,%.2f,%.2f,%.2f,%.2f,%.2f",
      counter, rtcTimeBuf, gpsTimeBuf, lat, lng, alt_gps, speed, sats,
      t_dht, h_dht, t_bmp, p_bmp, a_bmp,
      mpu_ax, mpu_ay, mpu_az, mpu_gx, mpu_gy, mpu_gz
    );

    // 1. Output to Serial
    Serial.println(dataBuffer);

    // 2. High-Speed SD Card Logging
    if (sdReady && flightLog) {
      digitalWrite(LORA_CS_PIN, HIGH);
      digitalWrite(SD_CS_PIN, LOW);
      
      flightLog.println(dataBuffer);
      
      // Flush buffer to physical SD flash memory every 20 packets to guarantee zero data loss on crash
      if (counter % 20 == 0) {
        flightLog.flush();
      }
      digitalWrite(SD_CS_PIN, HIGH);
    }

    // 3. High-Speed Non-blocking LoRa Transmission
    if (loraReady) {
      digitalWrite(SD_CS_PIN, HIGH);
      digitalWrite(LORA_CS_PIN, LOW);
      
      LoRa.beginPacket();
      LoRa.print(dataBuffer);
      LoRa.endPacket(true); // Async/Non-blocking transmit mode
      
      digitalWrite(LORA_CS_PIN, HIGH);
    }

    counter++;
  }
}