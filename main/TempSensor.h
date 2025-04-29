#ifndef TEMPERATURE_SENSOR_H
#define TEMPERATURE_SENSOR_H

#include <OneWire.h>
#include <DallasTemperature.h>

#define ONE_WIRE_BUS 5

OneWire oneWire(ONE_WIRE_BUS);
DallasTemperature sensors(&oneWire);

void initTemperatureSensor() {
  sensors.begin();
  Serial.println("🌡️ Temperature sensor initialized.");
}

// === Read Temperature (°C) ===
float readTemperatureC() {
  sensors.requestTemperatures();
  float tempC = sensors.getTempCByIndex(0);

  if (tempC <= -100 || tempC >= 85) {
    Serial.println("⚠️ Invalid temperature reading detected.");
    return -127.0;
  }

  return tempC;
}

#endif
