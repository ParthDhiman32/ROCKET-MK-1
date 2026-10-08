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

#define RXD2 16 
#define TXD2 17 
#define GPS_BAUD 9600 
#define DHTPIN 4 
#define DHTTYPE DHT11  
#define BMP280_ADDRESS 0x76 

#define SD_CS_PIN 15
#define ss 5
#define rst 14
#define dio0 2

// DS1302 Pin Definitions
#define DS1302_DAT  19
#define DS1302_SCLK 18
#define DS1302_RST  27

ThreeWire myWire(DS1302_DAT, DS1302_SCLK, DS1302_RST);
RtcDS1302<ThreeWire> Rtc(myWire);

int counter = 0;

Adafruit_BMP280 bmp;
Adafruit_MPU6050 mpu;
TinyGPSPlus gps;
HardwareSerial gpsSerial(2);
DHT dht(DHTPIN, DHTTYPE);

unsigned long lastLogTime = 0;
const unsigned long LOG_INTERVAL = 1000; 
const char* logFile = "/flight_log.csv";

void setup() {
  Serial.begin(115200);
  
  // High-speed I2C bus setup for MPU6050 / BMP280
  Wire.begin();
  Wire.setClock(400000);

  // Initialize DS1302 RTC
  Rtc.Begin();
  if (Rtc.GetIsWriteProtected()) {
    Rtc.SetIsWriteProtected(false);
  }
  if (!Rtc.GetIsRunning()) {
    Rtc.SetIsRunning(true);
  }

  gpsSerial.begin(GPS_BAUD, SERIAL_8N1, RXD2, TXD2);
  dht.begin();

  LoRa.setPins(ss, rst, dio0);
  while (!LoRa.begin(433E6)) {
    Serial.println("Starting LoRa failed!");
    delay(500);
  }
  LoRa.setSyncWord(0xF3);
  Serial.println("Avionics to Ground Telemetry Connection Established");
  
  if (!bmp.begin(BMP280_ADDRESS)) {
    Serial.println("BMP280 Initialization Failed!");
  }

  if (!mpu.begin()) {
    Serial.println("Failed to find MPU6050!");
  } else {
    mpu.setAccelerometerRange(MPU6050_RANGE_16_G);
    mpu.setGyroRange(MPU6050_RANGE_2000_DEG);
    mpu.setFilterBandwidth(MPU6050_BAND_260_HZ);
  }

  if (SD.begin(SD_CS_PIN)) {
    File file = SD.open(logFile, FILE_WRITE);
    if (file) {
      file.println("PacketID,Time,Lat,Lng,Alt_GPS,Speed,Sats,Temp_DHT,Hum,Temp_BMP,Press,Alt_BMP,AccX,AccY,AccZ,GyroX,GyroY,GyroZ");
      file.close();
    }
  } else {
    Serial.println("SD Card Initialization Failed!");
  }
}

void loop() {
  while (gpsSerial.available() > 0) {
    gps.encode(gpsSerial.read());
  }

  if (millis() - lastLogTime >= LOG_INTERVAL) {
    lastLogTime = millis();

    sensors_event_t a, g, temp;
    mpu.getEvent(&a, &g, &temp);

    float t_dht = dht.readTemperature();
    float h = dht.readHumidity();
    float t_bmp = bmp.readTemperature();
    float p_bmp = bmp.readPressure();
    float a_bmp = bmp.readAltitude(1013.25);
    double lat = gps.location.lat();
    double lng = gps.location.lng();
    double alt_gps = gps.altitude.meters();
    double speed = gps.speed.kmph();
    uint32_t sats = gps.satellites.value();
    
    float mpu_ax = a.acceleration.x;
    float mpu_ay = a.acceleration.y;
    float mpu_az = a.acceleration.z;
    float mpu_gx = g.gyro.x;
    float mpu_gy = g.gyro.y;
    float mpu_gz = g.gyro.z;

    // Primary GPS time -> Fallback DS1302 RTC
    String timeStr = "00:00:00";
    if (gps.time.isValid()) {
      char timeBuf[10];
      snprintf(timeBuf, sizeof(timeBuf), "%02d:%02d:%02d", gps.time.hour(), gps.time.minute(), gps.time.second());
      timeStr = String(timeBuf);
    } else {
      RtcDateTime now = Rtc.GetDateTime();
      if (now.IsValid()) {
        char timeBuf[10];
        snprintf(timeBuf, sizeof(timeBuf), "%02d:%02d:%02d", now.Hour(), now.Minute(), now.Second());
        timeStr = String(timeBuf);
      }
    }

    String dataLine = String(counter) + ",";
    dataLine += timeStr + ",";
    dataLine += String(lat, 6) + ",";
    dataLine += String(lng, 6) + ",";
    dataLine += String(alt_gps, 1) + ",";
    dataLine += String(speed, 1) + ",";
    dataLine += String(sats) + ",";
    dataLine += String(t_dht, 1) + ",";
    dataLine += String(h, 1) + ",";
    dataLine += String(t_bmp, 2) + ",";
    dataLine += String(p_bmp, 2) + ",";
    dataLine += String(a_bmp, 2) + ",";
    dataLine += String(mpu_ax, 2) + ",";
    dataLine += String(mpu_ay, 2) + ",";
    dataLine += String(mpu_az, 2) + ",";
    dataLine += String(mpu_gx, 2) + ",";
    dataLine += String(mpu_gy, 2) + ",";
    dataLine += String(mpu_gz, 2);

    Serial.println(dataLine);

    File file = SD.open(logFile, FILE_APPEND);
    if (file) {
      file.println(dataLine);
      file.close();
    }

    LoRa.beginPacket();
    LoRa.println(dataLine);
    LoRa.endPacket();

    counter++;
  }
}