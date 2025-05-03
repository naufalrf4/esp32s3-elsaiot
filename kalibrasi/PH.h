#ifndef PH_SENSOR_H
#define PH_SENSOR_H

#include <Arduino.h>

#define PH_SENSOR_PIN 14

int raw_adc_ph = 0;
float voltage_ph = 0.0;
float value_ph = 0.0;

float ph_voltage_offset = 0.0;
float ph_voltage_divisor = 1.0;
float ph_regresi_m = 1.0;
float ph_regresi_c = 0.0;

void initPHSensor() {
  pinMode(PH_SENSOR_PIN, INPUT);
  Serial.println("🌊 PH Sensor initialized.");
}

float readPH() {
  raw_adc_ph = analogRead(PH_SENSOR_PIN);
  voltage_ph = raw_adc_ph * (3.3 / 4095.0);

  float temp_ph = (voltage_ph - ph_voltage_offset) / ph_voltage_divisor;
  value_ph = (ph_regresi_m * temp_ph) + ph_regresi_c;

  if (value_ph < 0) value_ph = 0;
  if (value_ph > 14) value_ph = 14;

  Serial.print("[PH] ADC: "); Serial.print(raw_adc_ph);
  Serial.print(" | Voltage: "); Serial.print(voltage_ph, 3);
  Serial.print(" V | pH: "); Serial.println(value_ph, 2);

  return roundf(value_ph * 100) / 100.0;
}

#endif