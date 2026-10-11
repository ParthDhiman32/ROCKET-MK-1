#include <SPI.h>
#include <LoRa.h>

#define LORA_CS_PIN   5
#define LORA_RST_PIN  14
#define LORA_DIO0_PIN 2

void setup() {
  Serial.begin(115200);
  delay(1000);
  Serial.println("DEBUG: Ground station booting up...");

  LoRa.setPins(LORA_CS_PIN, LORA_RST_PIN, LORA_DIO0_PIN);
  if (!LoRa.begin(433E6)) {
    Serial.println("ERROR: LoRa init failed! Check wiring.");
    while (true);
  }
  Serial.println("SUCCESS: LoRa initialized!");

  LoRa.setSyncWord(0xF3);
  LoRa.setSignalBandwidth(500E3);
  LoRa.setSpreadingFactor(7);
  LoRa.setCodingRate4(5);
}

void loop() {
  int packetSize = LoRa.parsePacket();
  if (packetSize > 0) {
    char packetBuffer[320];
    memset(packetBuffer, 0, sizeof(packetBuffer));

    // Completely drain the LoRa FIFO buffer for this packet
    int i = 0;
    while (LoRa.available() && i < sizeof(packetBuffer) - 1) {
      packetBuffer[i++] = (char)LoRa.read();
    }
    packetBuffer[i] = '\0';

    // Declare variables for all 19 fields
    int packetId;
    char rtcTime[16], gpsTime[16];
    double lat, lng;
    float altGps, speed;
    unsigned int sats;
    float tempDht, hum, tempBmp, press, altBmp;
    float accX, accY, accZ, gyroX, gyroY, gyroZ;

    // Parse incoming raw CSV packet
    int matchedFields = sscanf(packetBuffer, "%d,%15[^,],%15[^,],%lf,%lf,%f,%f,%u,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f",
        &packetId, rtcTime, gpsTime, &lat, &lng, &altGps, &speed, &sats,
        &tempDht, &hum, &tempBmp, &press, &altBmp,
        &accX, &accY, &accZ, &gyroX, &gyroY, &gyroZ
    );

    // Re-serialize and print only when all 19 fields successfully match
    if (matchedFields == 19) {
      Serial.printf("%d,%s,%s,%.6f,%.6f,%.1f,%.1f,%u,%.1f,%.1f,%.2f,%.2f,%.2f,%.2f,%.2f,%.2f,%.2f,%.2f,%.2f\n",
          packetId, rtcTime, gpsTime, lat, lng, altGps, speed, sats,
          tempDht, hum, tempBmp, press, altBmp,
          accX, accY, accZ, gyroX, gyroY, gyroZ
      );
    }
  }
}