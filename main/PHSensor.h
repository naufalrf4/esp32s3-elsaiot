#ifndef PH_SENSOR_H
#define PH_SENSOR_H

#include <Arduino.h>

#define PH_SENSOR_PIN 14

int raw_adc_ph = 0;
float voltage_ph = 0.0;
float value_ph = 0.0;

extern float ph_slope;
extern float ph_offset;

void initPHSensor() {
  pinMode(PH_SENSOR_PIN, INPUT);
  Serial.println("🌊 PH Sensor initialized.");
}

float readPH() {
  raw_adc_ph = analogRead(PH_SENSOR_PIN);
  voltage_ph = raw_adc_ph * (3.3 / 4095.0);

  value_ph = (ph_slope * voltage_ph) + ph_offset;

  if (value_ph < 0) value_ph = 0;
  if (value_ph > 14) value_ph = 14;

  return roundf(value_ph * 100) / 100.0;
}

#endif
