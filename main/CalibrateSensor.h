#ifndef CALIBRATE_SENSOR_H
#define CALIBRATE_SENSOR_H

#include <ArduinoJson.h>
#include "DeviceConfig.h"

extern PubSubClient client;

float ph_regression_m = 1.0;
float ph_regression_c = 0.0;

float tds_regression_m = 1.0;
float tds_regression_c = 0.0;

float do_regression_m = 1.0;
float do_regression_c = 0.0;

void handleCalibrateMessage(const String& payload) {
  StaticJsonDocument<512> doc;
  DeserializationError error = deserializeJson(doc, payload);

  if (error) {
    Serial.println("❌ Failed to parse calibrate payload");
    return;
  }

  if (doc.containsKey("ph")) {
    ph_regression_m = doc["ph"]["m"];
    ph_regression_c = doc["ph"]["c"];
    Serial.printf("✅ PH Calibrated: m=%.3f, c=%.3f\n", ph_regression_m, ph_regression_c);
  }

  if (doc.containsKey("tds")) {
    tds_regression_m = doc["tds"]["m"];
    tds_regression_c = doc["tds"]["c"];
    Serial.printf("✅ TDS Calibrated: m=%.3f, c=%.3f\n", tds_regression_m, tds_regression_c);
  }

  if (doc.containsKey("do")) {
    do_regression_m = doc["do"]["m"];
    do_regression_c = doc["do"]["c"];
    Serial.printf("✅ DO Calibrated: m=%.3f, c=%.3f\n", do_regression_m, do_regression_c);
  }
}

void subscribeCalibrate() {
  String topic = "elsaiot/" + getDeviceID() + "/calibrate";
  client.subscribe(topic.c_str());
  Serial.println("📡 Subscribed to topic: " + topic);
}

#endif
