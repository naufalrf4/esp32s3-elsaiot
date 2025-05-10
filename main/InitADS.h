#ifndef INIT_ADS_H
#define INIT_ADS_H

#include <Wire.h>
#include <Adafruit_ADS1X15.h>

#define SDA_PIN 21
#define SCL_PIN 20

Adafruit_ADS1115 ads;

inline void initADS() {
  Wire.begin(SDA_PIN, SCL_PIN);
  ads.begin();
  ads.setGain(GAIN_ONE);
  Serial.println("📈 ADS1115 initialized.");
}

#endif
