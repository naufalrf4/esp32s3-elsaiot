#ifndef RTC_H
#define RTC_H

#include <Wire.h>
#include <RTClib.h>

#define SDA_PIN 21
#define SCL_PIN 20

RTC_DS3231 rtc;

void initRTC() {
  Wire.begin(SDA_PIN, SCL_PIN);

  if (!rtc.begin()) {
    Serial.println("❌ RTC not detected! Check SDA/SCL.");
    while (1);
  }

  if (rtc.lostPower()) {
    Serial.println("⚠️ RTC lost power. Setting to compile time...");
    rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));
  } else {
    Serial.println("✅ RTC initialized.");
  }
}

DateTime readRTC() {
  return rtc.now();
}

String formatTimestamp(DateTime now) {
  char buf[25];
  snprintf(buf, sizeof(buf), "%04d-%02d-%02dT%02d:%02d:%02dZ",
           now.year(), now.month(), now.day(),
           now.hour(), now.minute(), now.second());
  return String(buf);
}

#endif
