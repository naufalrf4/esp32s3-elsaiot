#ifndef TDS_SENSOR_H
#define TDS_SENSOR_H

#include <Arduino.h>
#include <Adafruit_ADS1X15.h>

#define TDS_CHANNEL 1

extern Adafruit_ADS1115 ads;
extern float tds_regression_m;
extern float tds_regression_c;

int16_t tds_adc_raw = 0;
float tds_voltage = 0.0;
float tds_value = 0.0;

void initTDSSensor() {
  Serial.println("🌊 TDS Sensor initialized.");
}

float readVoltTDS() {
  tds_adc_raw = ads.readADC_SingleEnded(TDS_CHANNEL);
  tds_voltage = tds_adc_raw * (3.3 / 32767.0);
  return tds_voltage;
}

float readTDS() {
  tds_voltage = readVoltTDS();
  tds_value = (tds_regression_m * tds_voltage) + tds_regression_c;

  if (tds_value < 0) tds_value = 0;
  if (tds_value > 1000) tds_value = 1000;

  Serial.print("[TDS] ADC: "); Serial.print(tds_adc_raw);
  Serial.print(" | Voltage: "); Serial.print(tds_voltage, 3);
  Serial.print(" V | TDS: "); Serial.println(tds_value, 1);

  return tds_value;
}

#endif
