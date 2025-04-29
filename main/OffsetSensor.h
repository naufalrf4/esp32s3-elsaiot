#ifndef OFFSET_SENSOR_H
#define OFFSET_SENSOR_H

#include <ArduinoJson.h>
#include "DeviceConfig.h"

extern PubSubClient client;

// === Default ===
float ph_good = 6.5;
float ph_bad = 8.0;

int tds_good = 400;
int tds_bad = 800;

float do_good = 7.0;
float do_bad = 4.0;

void handleOffsetMessage(const String& payload) {
  StaticJsonDocument<512> doc;
  DeserializationError error = deserializeJson(doc, payload);

  if (error) {
    Serial.println("❌ Failed to parse offset payload");
    return;
  }

  if (doc.containsKey("threshold")) {
    ph_good = doc["threshold"]["ph_good"];
    ph_bad = doc["threshold"]["ph_bad"];
    tds_good = doc["threshold"]["tds_good"];
    tds_bad = doc["threshold"]["tds_bad"];
    do_good = doc["threshold"]["do_good"];
    do_bad = doc["threshold"]["do_bad"];

    Serial.println("✅ Threshold updated successfully");
  }
}

void subscribeOffset() {
  String topic = "elsaiot/" + getDeviceID() + "/offset";
  client.subscribe(topic.c_str());
  Serial.println("📡 Subscribed to topic: " + topic);
}

#endif
