#include <SPI.h>
#include <LoRa.h>

#define LORA_CS_PIN   5
#define LORA_RST_PIN  14
#define LORA_DIO0_PIN 2

void setup() {
  Serial.begin(115200);
  while (!Serial);
  delay(1000);

  LoRa.setPins(LORA_CS_PIN, LORA_RST_PIN, LORA_DIO0_PIN);
  if (!LoRa.begin(433E6)) {
    Serial.println("[FAILED] LoRa initialization failed!");
    while (true);
  }

  // Match avionics flight settings
  LoRa.setSyncWord(0xF3);
  LoRa.setSignalBandwidth(500E3);
  LoRa.setSpreadingFactor(7);
  LoRa.setCodingRate4(5);
  
  Serial.println("Ground Station Ready. Listening for telemetry...\n");
}

void loop() {
  int packetSize = LoRa.parsePacket();
  if (packetSize) {
    char packetBuffer[300] = {0};
    int idx = 0;
    
    while (LoRa.available() && idx < sizeof(packetBuffer) - 1) {
      packetBuffer[idx++] = (char)LoRa.read();
    }
    packetBuffer[idx] = '\0';

    parseTelemetry(packetBuffer);
  }
}

void parseTelemetry(char* data) {
  char* token = strtok(data, ",");
  if (!token) return;
  int packetId = atoi(token);

  token = strtok(NULL, ",");
  char rtcTime[10] = "00:00:00";
  if (token) strncpy(rtcTime, token, sizeof(rtcTime));

  token = strtok(NULL, ",");
  char gpsTime[10] = "00:00:00";
  if (token) strncpy(gpsTime, token, sizeof(gpsTime));

  token = strtok(NULL, ",");
  double lat = token ? atof(token) : 0.0;

  token = strtok(NULL, ",");
  double lng = token ? atof(token) : 0.0;

  token = strtok(NULL, ",");
  float altGps = token ? atof(token) : 0.0;

  token = strtok(NULL, ",");
  float speed = token ? atof(token) : 0.0;

  token = strtok(NULL, ",");
  uint32_t sats = token ? atoi(token) : 0;

  token = strtok(NULL, ",");
  float tDht = token ? atof(token) : 0.0;

  token = strtok(NULL, ",");
  float hDht = token ? atof(token) : 0.0;

  token = strtok(NULL, ",");
  float tBmp = token ? atof(token) : 0.0;

  token = strtok(NULL, ",");
  float pBmp = token ? atof(token) : 0.0;

  token = strtok(NULL, ",");
  float altBmp = token ? atof(token) : 0.0;

  token = strtok(NULL, ",");
  float accX = token ? atof(token) : 0.0;

  token = strtok(NULL, ",");
  float accY = token ? atof(token) : 0.0;

  token = strtok(NULL, ",");
  float accZ = token ? atof(token) : 0.0;

  token = strtok(NULL, ",");
  float gyroX = token ? atof(token) : 0.0;

  token = strtok(NULL, ",");
  float gyroY = token ? atof(token) : 0.0;

  token = strtok(NULL, ",");
  float gyroZ = token ? atof(token) : 0.0;

 // Expanded print statement including GPS coordinates and speed
  Serial.printf("[%s] ID:%d | Lat:%.4f, Lng:%.4f | Alt:%.2fm | Speed:%.1f | AccZ:%.2f | Temp:%.1fC | RSSI:%ddBm\n",
                rtcTime, packetId, lat, lng, altBmp, speed, accZ, tBmp, LoRa.packetRssi());
}