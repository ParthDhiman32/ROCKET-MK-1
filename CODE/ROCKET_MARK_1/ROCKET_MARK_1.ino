#include <Wire.h>
#include <SPI.h>
#include "SD.h"
#include "DHT.h"
#include <TinyGPS++.h>
#include <Adafruit_BMP280.h>

#define RXD2 16 
#define TXD2 17 
#define GPS_BAUD 9600 
#define DHTPIN 4 
#define DHTTYPE DHT11  
#define SD_CS_PIN 5  
#define BMP280_ADDRESS 0x76 

Adafruit_BMP280 bmp;
TinyGPSPlus gps;
HardwareSerial gpsSerial(2);
DHT dht(DHTPIN, DHTTYPE);

unsigned long lastLogTime = 0;
const unsigned long LOG_INTERVAL = 1000; 
const char* logFile = "/flight_log.csv";

void setup() {
  Serial.begin(115200);
  gpsSerial.begin(GPS_BAUD, SERIAL_8N1, RXD2, TXD2);
  dht.begin();
  
  if (!bmp.begin(BMP280_ADDRESS)) {
    Serial.println("BMP280 Initialization Failed!");
  }

  if (SD.begin(SD_CS_PIN)) {
    File file = SD.open(logFile, FILE_WRITE);
    if (file) {
      file.println("UTC,Lat,Lng,Alt_GPS,Speed,Sats,Temp_DHT,Hum,Temp_BMP,Press,Alt_BMP");
      file.close();
    }
  }
}

void loop() {
  while (gpsSerial.available() > 0) {
    gps.encode(gpsSerial.read());
  }

  if (millis() - lastLogTime >= LOG_INTERVAL) {
    lastLogTime = millis();

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

    String utcStr = "NO_FIX";
    if (gps.time.isValid()) {
      utcStr = String(gps.time.hour()) + ":" + String(gps.time.minute()) + ":" + String(gps.time.second());
    }

    String dataLine = "";
    dataLine += utcStr + ",";
    dataLine += String(lat, 6) + ",";
    dataLine += String(lng, 6) + ",";
    dataLine += String(alt_gps, 1) + ",";
    dataLine += String(speed, 1) + ",";
    dataLine += String(sats) + ",";
    dataLine += String(t_dht, 1) + ",";
    dataLine += String(h, 1) + ",";
    dataLine += String(t_bmp, 2) + ",";
    dataLine += String(p_bmp, 2) + ",";
    dataLine += String(a_bmp, 2) + "\n";

    Serial.print(dataLine);

    File file = SD.open(logFile, FILE_APPEND);
    if (file) {
      file.print(dataLine);
      file.close();
    }
  }
}