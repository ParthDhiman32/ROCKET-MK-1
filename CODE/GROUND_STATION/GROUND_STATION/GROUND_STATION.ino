#include <SPI.h>
#include <LoRa.h>

#define LORA_CS_PIN   5
#define LORA_RST_PIN  14
#define LORA_DIO0_PIN 2

void setup() {
  Serial.begin(115200);
  while (!Serial);
  delay(1000);

  Serial.println("\n=== ROCKET MK-1 GROUND STATION RECEIVER ===");

  LoRa.setPins(LORA_CS_PIN, LORA_RST_PIN, LORA_DIO0_PIN);

  Serial.print("Initializing High-Speed LoRa Receiver... ");
  if (!LoRa.begin(433E6)) {
    Serial.println("[FAILED] Check wiring and antenna!");
    while (1);
  }

  // Must match the sender radio configuration exactly
  LoRa.setSyncWord(0xF3);
  LoRa.setSignalBandwidth(500E3);
  LoRa.setSpreadingFactor(7);
  LoRa.setCodingRate4(5);

  Serial.println("[SUCCESS]");
  Serial.println("=== GROUND STATION READY: STREAMING TO SERIAL STUDIO ===\n");
}

void loop() {
  int packetSize = LoRa.parsePacket();
  if (packetSize) {
    // Stream incoming bytes directly to Serial without string heap allocation overhead
    while (LoRa.available()) {
      Serial.write((uint8_t)LoRa.read());
    }
  }
}