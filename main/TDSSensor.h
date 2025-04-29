#ifndef TDS_SENSOR_H
#define TDS_SENSOR_H

#include <Arduino.h>

#define TDS_SENSOR_PIN 12

int raw_adc_tds = 0;
float voltage_tds = 0.0;
float value_tds = 0.0;

extern float tds_factor;

void initTDSSensor() {
  pinMode(TDS_SENSOR_PIN, INPUT);
  Serial.println("🌊 TDS Sensor initialized.");
}

// === Read TDS Value (ppm) ===
float readTDS() {
  raw_adc_tds = analogRead(TDS_SENSOR_PIN);
  
  voltage_tds = raw_adc_tds * (3.3 / 4095.0);

  value_tds = (voltage_tds / 3.3) * 1000.0; 

  value_tds = value_tds * tds_factor;

  if (value_tds < 0) value_tds = 0;
  if (value_tds > 1000) value_tds = 1000;

  return value_tds;
}

#endif
