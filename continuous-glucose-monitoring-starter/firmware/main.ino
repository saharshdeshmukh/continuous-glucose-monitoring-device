#include <Wire.h>
#include <MAX30100_PulseOximeter.h>
#include <LiquidCrystal_PCF8574.h>
#include <BluetoothSerial.h>
#include <OneWire.h>
#include <DallasTemperature.h>
#include <WiFi.h>
#include <BlynkSimpleEsp32.h>

// Your #define pins and constants
// All buffers: hrBuf, spBuf, etc.
// All helper functions: onBeatDetected(), calcGlucose(), resetBatch(), calcFinals(), sendToBlynk(), checkWiFiConnection()
void setup() {
  // put your setup code here, to run once:void setup() {
  Serial.begin(115200);
  SerialBT.begin("GlucoseMonitor");
  pinMode(LED_PIN, OUTPUT);

  // Initialize LCD
  Wire.begin(SDA_PIN, SCL_PIN);
  lcd.begin(16, 2);
  lcd.setBacklight(255);
  lcd.print("Connecting WiFi...");

  // Connect to WiFi
  WiFi.begin(ssid, pass);
  unsigned long startTime = millis();
  while (WiFi.status() != WL_CONNECTED && millis() - startTime < 15000) {
    delay(500);
    lcd.print(".");
  }
  
  if (WiFi.status() == WL_CONNECTED) {
    lcd.clear();
    lcd.print("WiFi Connected");
    Blynk.config(auth);
    Blynk.connect();
    delay(1000);
  } else {
    lcd.clear();
    lcd.print("WiFi Failed");
    delay(2000);
  }

  // Initialize sensors
  tempSensor.begin();
  tempSensor.setWaitForConversion(false);

  if (!pox.begin()) {
    lcd.clear(); 
    lcd.print("MAX30100 FAIL");
    while (1) delay(1000);
  }
  pox.setIRLedCurrent(MAX30100_LED_CURR_7_6MA);
  pox.setOnBeatDetectedCallback(onBeatDetected);

  lcd.clear(); 
  lcd.print("Ready");
  lcd.setCursor(0, 1); 
  lcd.print("Place finger");
  resetBatch();
}


}

void loop() {
  // put your main code here, to run repeatedly:void loop() {
  static uint32_t lastReport = 0;
  static float    prevHR = 0, prevSpO2 = 0;

  Blynk.run();
  checkWiFiConnection();
  pox.update();
  tempSensor.requestTemperatures();
  lastTemp = tempSensor.getTempCByIndex(0);

  fingerDetected = (millis() - lastBeat) < FINGER_TIMEOUT;

  if (millis() - lastReport >= REPORT_MS) {
    lastReport = millis();

    float hr = pox.getHeartRate();
    float sp = pox.getSpO2();
    float tp = lastTemp;

    if (fingerDetected && valid(hr, sp)) {
      /* Smoothing */
      hr = (hr + 2 * prevHR) / 3;
      sp = (sp + 2 * prevSpO2) / 3;
      prevHR = hr;  
      prevSpO2 = sp;

      float gl = calcGlucose(sp, hr, tp);

      hrBuf[bufIndex] = hr;
      spBuf[bufIndex] = sp;
      tpBuf[bufIndex] = tp;
      glBuf[bufIndex] = gl;
      ++bufIndex;
    }

    /* Batch ready? */
    if (bufIndex >= READINGS_NEEDED) {
      calcFinals();
      showFinal = true;

      /* Send to Bluetooth */
      String json = String("{\"HR\":") + String((int)avgHR) +
                   ",\"SpO2\":" + String((int)avgSpO2) +
                   ",\"Glucose\":" + String(avgGlucose, 1) +
                   ",\"Temp\":" + String(avgTemp, 1) + "}";
      SerialBT.println(json);
      Serial.println("Sent → " + json);

      /* Send to Blynk */
      sendToBlynk();

      resetBatch();
    }

    /* Update LCD */
    if (showFinal) {
      lcd.setCursor(0, 0);
      lcd.print("HR:"); lcd.print((int)avgHR); lcd.print(" ");
      lcd.print("SpO2:"); lcd.print((int)avgSpO2); lcd.print("   ");

      lcd.setCursor(0, 1);
      lcd.print("G:"); lcd.print(avgGlucose, 1);
      lcd.print(" T:"); lcd.print(avgTemp, 1);
      lcd.print("   ");
    } else if (!fingerDetected) {
      lcd.setCursor(0, 0); lcd.print("Place finger    ");
      lcd.setCursor(0, 1); lcd.print("on sensor       ");
    }
  }
}


}
