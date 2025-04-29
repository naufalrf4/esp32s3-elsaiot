#ifndef CHECK_SPEC_H
#define CHECK_SPEC_H

#include <Arduino.h>
#include <WiFi.h>

void printHardwareInfo() {
  Serial.println("=== ESP32 Hardware Check ===");

  Serial.printf("Chip Model      : %s\n", ESP.getChipModel());
  Serial.printf("Chip Revision   : %d\n", ESP.getChipRevision());
  Serial.printf("CPU Cores       : %d\n", ESP.getChipCores());
  Serial.printf("CPU Frequency   : %lu MHz\n", getCpuFrequencyMhz());

  Serial.printf("Flash Size      : %lu MB\n", ESP.getFlashChipSize() / (1024 * 1024));
  Serial.printf("Flash Speed     : %lu MHz\n", ESP.getFlashChipSpeed() / 1000000);

  if (psramFound()) {
    Serial.printf("PSRAM Detected  : YES (%lu MB)\n", ESP.getPsramSize() / (1024 * 1024));
  } else {
    Serial.println("PSRAM Detected  : NO ❌");
  }

  Serial.println("MAC Address     : " + WiFi.macAddress());
  Serial.printf("Free Heap       : %lu bytes\n", ESP.getFreeHeap());
  Serial.println("=================================");
}

#endif
