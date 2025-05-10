#ifndef DO_SENSOR_H
#define DO_SENSOR_H

#include <Arduino.h>
#include <Adafruit_ADS1X15.h>

#define DO_CHANNEL 2

extern Adafruit_ADS1115 ads;
extern float do_regression_m;
extern float do_regression_c;

int16_t do_adc_raw = 0;
float do_voltage = 0.0;
float do_value = 0.0;

void initDOSensor() {
  Serial.println("🐟 DO Sensor initialized.");
}

float readVoltDO() {
  do_adc_raw = ads.readADC_SingleEnded(DO_CHANNEL);
  do_voltage = do_adc_raw * (3.3 / 32767.0);
  return do_voltage;
}

float readDO() {
  do_voltage = readVoltDO();
  do_value = (do_regression_m * do_voltage) + do_regression_c;

  if (do_value < 0) do_value = 0;
  if (do_value > 20) do_value = 20;

  Serial.print("[DO] ADC: "); Serial.print(do_adc_raw);
  Serial.print(" | Voltage: "); Serial.print(do_voltage, 3);
  Serial.print(" V | DO: "); Serial.println(do_value, 2);

  return do_value;
}

#endif
