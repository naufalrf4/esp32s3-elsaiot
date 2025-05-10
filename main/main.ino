#include <Arduino.h>
#include "RTCMod.h"
#include "TFT.h"
#include "WifiConf.h"
#include "TempSensor.h"
#include "SendData.h"
#include "TDSSensor.h"
#include "DOSensor.h"
#include "PHSensor.h"
#include "InitADS.h"

void setup() {
  Serial.begin(115200);
  delay(3000);

  initTFT();
  showStatus("System Init...");
  // initRTC();
  initADS();
  initTemperatureSensor();
  initTDSSensor();
  initPHSensor();
  initDOSensor();

  showStatus("Connecting WiFi...");
  connectToWiFi();

  showStatus("Init MQTT...");
  initSendData();

  showStatus("System Ready!");
  delay(1000);
}

void loop() {
  updateHeader();
  // DateTime now = readRTC();

  float tempC = readTemperatureC();
  float phVal = readPH();
  float phVolt = readVoltPH();
  float tdsVal = readTDS();
  float tdsVolt = readVoltTDS();
  float doVal = readDO();
  float doVolt = readVoltDO();

  Serial.printf("🌡️ %.2f °C | pH: %.2f (%.3f V) | TDS: %d ppm (%.3f V) | DO: %.2f mg/L (%.3f V)\n",
                now.day(), now.month(), now.year(),
                now.hour(), now.minute(), now.second(),
                tempC, phVal, phVolt, tdsVal, tdsVolt, doVal, doVolt);

  // showClock(now);
  drawTemp(tempC);
  drawPH(phVal);
  drawTDS(tdsVal);
  drawDO(doVal);

  sendSensorData(phVal, tempC, tdsVal, doVal, phVolt, tdsVolt, doVolt);

  delay(1000);
}
