#include <SPI.h>
#include <LoRa.h>

#define LORA_CS_PIN   5
#define LORA_RST_PIN  14
#define LORA_DIO0_PIN 2

// Speaker / Buzzer configuration on D15 (GPIO 15)
#define SPEAKER_PIN   15
#define LEDC_BASE_FREQ 2000
#define LEDC_TIMER_BIT 8

// Mission States & Status
int missionState = 1;
String missionStatusText = "STANDBY";
String terrainWarning = "NOMINAL";

// Simulation timer variables
unsigned long lastSimTime = 0;
const unsigned long simInterval = 3000; // Switch state every 3 seconds
bool simulationMode = true;             // Set to false when ready for real LoRa flight packets

void setup() {
  Serial.begin(115200);
  while (!Serial);
  delay(1000);

  Serial.println("\n=== ROCKET MK-1 GROUND STATION: SIMULATION MODE ACTIVE ===");

  // Initialize Speaker using ESP32 Arduino Core v3.x LEDC API
  pinMode(SPEAKER_PIN, OUTPUT);
  ledcAttach(SPEAKER_PIN, LEDC_BASE_FREQ, LEDC_TIMER_BIT);
  ledcWrite(SPEAKER_PIN, 0); // Off initially

  LoRa.setPins(LORA_CS_PIN, LORA_RST_PIN, LORA_DIO0_PIN);

  Serial.print("Initializing High-Speed LoRa Receiver... ");
  if (!LoRa.begin(433E6)) {
    Serial.println("[FAILED] Check wiring and antenna! (Running simulation anyway)");
  } else {
    Serial.println("[SUCCESS]");
  }

  LoRa.setSyncWord(0xF3);
  LoRa.setSignalBandwidth(500E3);
  LoRa.setSpreadingFactor(7);
  LoRa.setCodingRate4(5);
}

void playTerrainWarning() {
  // Synthetic "WHOOP WHOOP PULL UP" dual-tone siren pattern on D15
  for (int i = 0; i < 2; i++) {
    ledcWriteTone(SPEAKER_PIN, 900);  // Low tone
    delay(150);
    ledcWriteTone(SPEAKER_PIN, 1400); // High tone
    delay(150);
  }
  ledcWrite(SPEAKER_PIN, 0); // Stop speaker
}

void updateMissionState(int stateCode) {
  missionState = stateCode;
  switch (missionState) {
    case 1:
      missionStatusText = "LAUNCH DETECTED";
      terrainWarning = "NOMINAL";
      break;
    case 2:
      missionStatusText = "APOGEE REACHED";
      terrainWarning = "NOMINAL";
      break;
    case 3:
      missionStatusText = "PARACHUTE DEPLOYED";
      terrainWarning = "NOMINAL";
      break;
    case 4:
      missionStatusText = "PARACHUTE DEPLOYMENT FAILURE";
      terrainWarning = "WARNING: CHUTE FAIL";
      break;
    case 5:
      missionStatusText = "OUT OF TRAJECTORY";
      terrainWarning = "WARNING: DRIFTING";
      break;
    case 6:
      missionStatusText = "HARD DECELERATION";
      terrainWarning = "TERRAIN TERRAIN PULL UP";
      playTerrainWarning(); // Trigger D15 Audio Alarm
      break;
    case 7:
      missionStatusText = "MAIN CHUTE RELEASE";
      terrainWarning = "NOMINAL";
      break;
    case 8:
      missionStatusText = "DESCENT STABILIZED";
      terrainWarning = "NOMINAL";
      break;
    case 9:
      missionStatusText = "TOUCHDOWN DETECTED";
      terrainWarning = "NOMINAL";
      break;
    case 10:
      missionStatusText = "MISSION COMPLETE";
      terrainWarning = "NOMINAL";
      break;
    default:
      missionStatusText = "IN FLIGHT / NOMINAL";
      terrainWarning = "NOMINAL";
      break;
  }
}

void loop() {
  // 1. Simulation Loop: Automatically sweep states 1-10 every 3 seconds
  if (simulationMode && (millis() - lastSimTime >= simInterval)) {
    lastSimTime = millis();
    updateMissionState(missionState);

    // Build dummy sensor payload + consolidated status string
    String dummySensors = "1,12:00:00,12:00:00,15.2,65,24.1,1013.2,120,1.2,0.1,9.8,0.0,0.0,0.0,28.5,77.1";
    String consolidatedStatus = "[State " + String(missionState) + "] " + missionStatusText + " | " + terrainWarning;

    Serial.print("$");
    Serial.print(dummySensors);
    Serial.print(",");
    Serial.println(consolidatedStatus);

    // Increment state, loop back to 1 after 10
    missionState++;
    if (missionState > 10) missionState = 1;
  }

  // 2. Real LoRa Packet Handling (Active when simulationMode is false)
  int packetSize = LoRa.parsePacket();
  if (!simulationMode && packetSize) {
    String incomingPacket = "";
    while (LoRa.available()) {
      incomingPacket += (char)LoRa.read();
    }
    incomingPacket.trim();
    if (incomingPacket.startsWith("$")) incomingPacket = incomingPacket.substring(1);

    if (incomingPacket.indexOf("STATE:") != -1) {
      int idx = incomingPacket.indexOf("STATE:");
      int parsedState = incomingPacket.substring(idx + 6, idx + 8).toInt();
      updateMissionState(parsedState);
    }

    String consolidatedStatus = "[State " + String(missionState) + "] " + missionStatusText + " | " + terrainWarning;
    Serial.print("$");
    Serial.print(incomingPacket);
    Serial.print(",");
    Serial.println(consolidatedStatus);
  }
}