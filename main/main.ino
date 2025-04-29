#include <Arduino.h>
#include "RTCMod.h"
#include "TFT.h"
#include "WifiConf.h"
#include "TempSensor.h"
#include "SendData.h"
#include "TDSSensor.h"
#include "PHSensor.h"

void setup() {
  Serial.begin(115200);
  delay(1000);

  initTFT();
  showStatus("System Init...");
  initRTC();
  initTemperatureSensor();
  initTDSSensor();
  initPHSensor();

  showStatus("Connecting WiFi...");
  connectToWiFi();

  showStatus("Init MQTT...");
  initSendData();

  showStatus("System Ready!");
  delay(1000);
}

void loop() {
  updateHeader();
  DateTime now = readRTC();

  float tempC = readTemperatureC();
  float ph    = readPH();
  float tds   = readTDS();
  float doVal = random(400, 900) / 100.0;

  Serial.printf("🕒 %02d/%02d/%04d %02d:%02d:%02d | 🌡️ %.2f °C | pH: %.2f | TDS: %d ppm | DO: %.2f mg/L\n",
                now.day(), now.month(), now.year(),
                now.hour(), now.minute(), now.second(),
                tempC, ph, tds, doVal);

  showClock(now);
  drawTemp(tempC);
  drawPH(ph);
  drawTDS(tds);
  drawDO(doVal);

  sendSensorData(
    ph, tempC, tds, doVal
  );

  delay(1000);
}