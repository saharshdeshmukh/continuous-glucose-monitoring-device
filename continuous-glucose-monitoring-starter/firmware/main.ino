/*
  firmware/main.ino
  Skeleton for ESP32 reading sensors, computing estimated glucose, and sending to Firebase.

  Replace sensor reading code and Firebase parts with your actual libraries and keys.
  Do NOT commit secrets (Wi-Fi password, Firebase keys). Use firebase_config.json locally and add it to .gitignore.
*/

#include <Arduino.h>

// Example: placeholder sensor values
float readSpO2() {
  // TODO: replace with real code to read MAX30100
  return 96.5;
}

float readBPM() {
  // TODO: replace with real code to read heart rate
  return 72.0;
}

// Glucose estimation formula:
// Glucose = 160 + (0.2 * SpO2) - (0.65 * BPM)
float estimateGlucose(float spo2, float bpm) {
  return 160.0 + (0.2 * spo2) - (0.65 * bpm);
}

void setup() {
  Serial.begin(115200);
  Serial.println("CGM device skeleton starting...");
  // Initialize sensors, display, Wi-Fi, Firebase, etc.
}

void loop() {
  float spo2 = readSpO2();
  float bpm  = readBPM();
  float glucose = estimateGlucose(spo2, bpm);

  Serial.print("SpO2: "); Serial.print(spo2);
  Serial.print("  BPM: "); Serial.print(bpm);
  Serial.print("  Est. Glucose (mg/dL): "); Serial.println(glucose);

  // TODO: send to Firebase / LCD display
  delay(3000); // wait 3 seconds before next reading
}
