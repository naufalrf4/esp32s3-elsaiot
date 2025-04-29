#ifndef CALIBRATE_SENSOR_H
#define CALIBRATE_SENSOR_H

#include <ArduinoJson.h>
#include "DeviceConfig.h"

extern PubSubClient client;

float ph_slope = 1.0;
float ph_offset = 0.0;

float tds_factor = 0.5;

float do_slope = 1.0;
float do_offset = 0.0;

void handleCalibrateMessage(const String& payload) {
  StaticJsonDocument<512> doc;
  DeserializationError error = deserializeJson(doc, payload);

  if (error) {
    Serial.println("❌ Failed to parse calibrate payload");
    return;
  }

  if (doc.containsKey("ph")) {
    ph_slope = doc["ph"]["slope"];
    ph_offset = doc["ph"]["offset"];
    Serial.printf("✅ PH Calibrated: slope=%.3f, offset=%.3f\n", ph_slope, ph_offset);
  }

  if (doc.containsKey("tds")) {
    tds_factor = doc["tds"]["factor"];
    Serial.printf("✅ TDS Calibrated: factor=%.3f\n", tds_factor);
  }

  if (doc.containsKey("do")) {
    do_slope = doc["do"]["slope"];
    do_offset = doc["do"]["offset"];
    Serial.printf("✅ DO Calibrated: slope=%.3f, offset=%.3f\n", do_slope, do_offset);
  }
}

void subscribeCalibrate() {
  String topic = "elsaiot/" + getDeviceID() + "/calibrate";
  client.subscribe(topic.c_str());
  Serial.println("📡 Subscribed to topic: " + topic);
}

#endif
