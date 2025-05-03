#include <Arduino.h>
#include "PH.h"
#include "TDS.h"

void setup() {
  Serial.begin(115200);
  delay(1000);

  initPHSensor();
  initTDSSensor();
}

void loop() {
  readPH();
  readTDS();

  delay(2000);
}
