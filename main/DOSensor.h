#ifndef DO_SENSOR_H
#define DO_SENSOR_H

#include <Arduino.h>

#define DO_SENSOR_PIN 16

int raw_adc_do = 0;
float voltage_do = 0.0;
float value_do = 0.0;

extern float do_slope;
extern float do_offset;

void initDOSensor() {
  pinMode(DO_SENSOR_PIN, INPUT);
  Serial.println("🐟 DO Sensor initialized.");
}

float readDO() {
  raw_adc_do = analogRead(DO_SENSOR_PIN);
  voltage_do = raw_adc_do * (3.3 / 4095.0);
  value_do = (do_slope * voltage_do) + do_offset;

  if (value_do < 0) value_do = 0;
  if (value_do > 20) value_do = 20;

  return value_do;
}

#endif
