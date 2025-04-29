#ifndef SEND_DATA_H
#define SEND_DATA_H

#include <WiFi.h>
#include <WiFiClientSecure.h>
#include <PubSubClient.h>
#include <ArduinoJson.h>
#include "DeviceConfig.h"
#include "CalibrateSensor.h"
#include "OffsetSensor.h"

WiFiClientSecure espClientSecure;
PubSubClient client(espClientSecure);

// === MQTT Callback Handler ===
void mqttCallback(char* topic, byte* payload, unsigned int length) {
  String incoming = "";
  for (unsigned int i = 0; i < length; i++) {
    incoming += (char)payload[i];
  }

  Serial.println("📥 MQTT Incoming: " + incoming);

  String calibrateTopic = "elsaiot/" + getDeviceID() + "/calibrate";
  String offsetTopic = "elsaiot/" + getDeviceID() + "/offset";

  if (String(topic) == calibrateTopic) {
    handleCalibrateMessage(incoming);
  } 
  else if (String(topic) == offsetTopic) {
    handleOffsetMessage(incoming);
  } 
  else {
    Serial.println("⚠️ Unknown topic received.");
  }
}

// === Initialize MQTT Connection ===
void initSendData() {
  espClientSecure.setInsecure();
  client.setServer(MQTT_SERVER, MQTT_PORT);
  client.setCallback(mqttCallback);

  while (!client.connected()) {
    String clientId = getDeviceID();
    Serial.print("🔌 Connecting to MQTT... ");
    if (client.connect(clientId.c_str(), MQTT_USER, MQTT_PASSWORD)) {
      Serial.println("✅ MQTT Connected");

      subscribeCalibrate();
      subscribeOffset();
    } else {
      Serial.print("❌ Failed. State: ");
      Serial.println(client.state());
      delay(3000);
    }
  }
}

// === Publish Sensor Data to MQTT ===
void sendSensorData(float ph, float suhu, int tds, float do_mg) {
  if (!client.connected()) {
    initSendData();
  }
  client.loop();

  String topic = "elsaiot/" + getDeviceID() + "/data";

  StaticJsonDocument<256> doc;
  doc["ph"] = ph;
  doc["temperature"] = suhu;
  doc["tds"] = tds;
  doc["dissolved_oxygen"] = do_mg;

  char buffer[256];
  serializeJson(doc, buffer);

  if (client.publish(topic.c_str(), buffer)) {
    Serial.println("📤 MQTT Payload Sent:");
    Serial.println(buffer);
  } else {
    Serial.println("❌ MQTT Send Failed");
  }
}

#endif