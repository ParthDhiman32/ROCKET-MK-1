#include <SPI.h>
#include <LoRa.h>
#include <AudioFileSourcePROGMEM.h>
#include <AudioGeneratorMP3.h>
#include <AudioOutputI2S.h> // Reverted back to the standard library I2S output

#define LORA_CS_PIN   5
#define LORA_RST_PIN  14
#define LORA_DIO0_PIN 2

// --- INCLUDE YOUR 2 CONVERTED MP3 HEADER FILES ---
#include "out_of_trajectory.h"    
#include "hard_deceleration.h"    

// Audio pipeline objects
AudioGeneratorMP3 *mp3;
AudioFileSourcePROGMEM *file;
AudioOutputI2S *out;

// Mission State tracking
int missionState = 1;
int previousMissionState = -1;

// Simulation timer variables (switches state every 3 seconds for testing)
unsigned long lastSimTime = 0;
const unsigned long simInterval = 3000; 

void setup() {
  Serial.begin(115200);
  while (!Serial);
  delay(1000);

  Serial.println("\n=== ROCKET MK-1 GROUND STATION: DUAL-WARNING MP3 AUDIO ===");

  // Initialize I2S Audio Output (BCLK: 26, LRC: 25, DIN: 22)
  out = new AudioOutputI2S();
  out->SetGain(0.85); // Volume level (0.0 to 1.0)
  out->SetPinout(26, 25, 22); 

  mp3 = new AudioGeneratorMP3();

  // Initialize LoRa
  LoRa.setPins(LORA_CS_PIN, LORA_RST_PIN, LORA_DIO0_PIN);
  if (!LoRa.begin(433E6)) {
    Serial.println("[LoRa FAILED] Check antenna! (Running simulation loop)");
  } else {
    Serial.println("[LoRa SUCCESS]");
  }

  // Must match sender radio configuration exactly
  LoRa.setSyncWord(0xF3);
  LoRa.setSignalBandwidth(500E3);
  LoRa.setSpreadingFactor(7);
  LoRa.setCodingRate4(5);
}

// Function to trigger warning MP3s based on state
void playWarningMP3(int state) {
  // Stop any currently playing audio stream
  if (mp3->isRunning()) {
    mp3->stop();
  }

  const uint8_t *audioData = nullptr;
  uint32_t audioLen = 0;

  // Map state 5 and state 6 to their respective header arrays
  if (state == 5) {
    audioData = out_of_trajectory_mp3;
    audioLen = out_of_trajectory_len;
    Serial.println("[AUDIO] Playing: Out of Trajectory Warning");
  } 
  else if (state == 6) {
    audioData = hard_deceleration_mp3;
    audioLen = hard_deceleration_len;
    Serial.println("[AUDIO] Playing: Hard Deceleration Warning");
  }

  // If a valid warning audio file was selected, start playback
  if (audioData != nullptr && audioLen > 0) {
    file = new AudioFileSourcePROGMEM(audioData, audioLen);
    mp3->begin(file, out);
  }
}

void loop() {
  // 1. CRITICAL: Keep the MP3 decoder pumping data in the background non-stop
  if (mp3->isRunning()) {
    if (!mp3->loop()) {
      mp3->stop();
    }
  }

  // 2. Non-blocking state sweep timer (advances state every 3 seconds for testing)
  if (millis() - lastSimTime >= simInterval) {
    lastSimTime = millis();
    missionState++;
    if (missionState > 10) missionState = 1; // Loops back to 1
  }

  // 3. State Transition Audio Trigger Check (Fires ONCE when entering State 5 or 6)
  if (missionState != previousMissionState) {
    previousMissionState = missionState;
    playWarningMP3(missionState);
  }

  // 4. Telemetry Stream: Sends sensor string + integer state at index 19 to Serial Studio
  static unsigned long lastStreamTime = 0;
  if (millis() - lastStreamTime >= 1000) { // Stream every 1 second
    lastStreamTime = millis();

    String sensorPayload = "101,18:26:41,00:00:00,0.0,0.0,0.0,0.0,0.29,5.95,0.30,38,98835.20,209.39,-1.69,-0.13,9.50,-0.00,-0.03,-0.01";
    
    Serial.print("$");
    Serial.print(sensorPayload);
    Serial.print(",");
    Serial.println(missionState);
  }

  // 5. Real LoRa Packet Handling (Appends current state integer to live incoming packets)
  int packetSize = LoRa.parsePacket();
  if (packetSize) {
    String incomingPacket = "";
    while (LoRa.available()) {
      incomingPacket += (char)LoRa.read();
    }
    incomingPacket.trim();
    if (incomingPacket.startsWith("$")) incomingPacket = incomingPacket.substring(1);

    Serial.print("$");
    Serial.print(incomingPacket);
    Serial.print(",");
    Serial.println(missionState);
  }
}