#ifndef PH_SENSOR_H
#define PH_SENSOR_H

#include <Arduino.h>
#include <Adafruit_ADS1X15.h>

#define PH_CHANNEL 0  // ADS1115 A0

extern Adafruit_ADS1115 ads;
extern float ph_regression_m;
extern float ph_regression_c;

int16_t ph_adc_raw = 0;
float ph_voltage = 0.0;
float ph_value = 0.0;

void initPHSensor() {
  Serial.println("🌊 PH Sensor initialized.");
}

float readVoltPH() {
  ph_adc_raw = ads.readADC_SingleEnded(PH_CHANNEL);
  ph_voltage = ph_adc_raw * (3.3 / 32767.0);
  return ph_voltage;
}

float readPH() {
  ph_voltage = readVoltPH();
  ph_value = (ph_regression_m * ph_voltage) + ph_regression_c;

  if (ph_value < 0) ph_value = 0;
  if (ph_value > 14) ph_value = 14;

  Serial.print("[PH] ADC: "); Serial.print(ph_adc_raw);
  Serial.print(" | Voltage: "); Serial.print(ph_voltage, 3);
  Serial.print(" V | pH: "); Serial.println(ph_value, 2);

  return ph_value;
}

#endif
