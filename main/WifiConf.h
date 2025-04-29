#ifndef WIFI_CONF_H
#define WIFI_CONF_H

#include <WiFi.h>
#include <WiFiManager.h>
#include "DeviceConfig.h"

// === CONFIGURATION ===
#define AP_TIMEOUT_SEC        180
#define WIFI_CONNECT_TIMEOUT   90
#define RESET_PIN               0 

bool wifi_debug = true;

void connectToWiFi() {
  WiFiManager wm;

  String apSSID = getDeviceID();

  if (wifi_debug) {
    Serial.println("📡 Launching WiFiManager with SSID: " + apSSID);
  }

  wm.setDebugOutput(wifi_debug);
  wm.setConfigPortalTimeout(AP_TIMEOUT_SEC);
  wm.setConnectTimeout(WIFI_CONNECT_TIMEOUT);

  pinMode(RESET_PIN, INPUT_PULLUP);
  if (digitalRead(RESET_PIN) == LOW) {
    wm.resetSettings();
    if (wifi_debug) Serial.println("🔄 Reset WiFi settings via button");
    delay(1000);
  }

  bool res = wm.autoConnect(apSSID.c_str(), DEFAULT_AP_PASSWORD);

  if (!res) {
    Serial.println("❌ WiFi failed. Rebooting...");
    delay(3000);
    ESP.restart();
  }

  Serial.println("✅ WiFi Connected");
  Serial.println("📶 IP Address: " + WiFi.localIP().toString());
}

inline bool wifiIsOK() {
  return WiFi.status() == WL_CONNECTED;
}

inline int wifiRSSI() {
  return wifiIsOK() ? WiFi.RSSI() : -1000;
}

#endif