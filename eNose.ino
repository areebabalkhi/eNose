#include "SparkFun_SGP30_Arduino_Library.h"  // Air quality sensor library
#include <Wire.h>

const int MQ3Pin = A0;  // Alcohol sensor pin
SGP30 mySensor;
long t1, t2;

long CO2, TVOC, H2, ethanol, alcohol;

void setup() {
  // put your setup code here, to run once:

  Serial.begin(9600);
  Wire.begin();
  Wire.setClock(400000);

  // Serial.println("hello");

  if (mySensor.begin() == false) {
    Serial.println(F("SGP30 not detected. Check connections. Freezing..."));
    while (1)
      ;  // Do nothing more
  }

  // Serial.println("hello2");
  mySensor.initAirQuality();
  t1 = millis();
}

void loop() {
  // put your main code here, to run repeatedly:
  t2 = millis();
  if (t2 >= t1 + 1000) {
    t1 = t2;
    mySensor.measureAirQuality();
    CO2 = mySensor.CO2; // in ppm
    TVOC = mySensor.TVOC; // in ppb

    mySensor.measureRawSignals();
    H2 = mySensor.H2;
    ethanol = mySensor.ethanol;

    alcohol = analogRead(MQ3Pin);

    Serial.print(CO2);
    Serial.print(", ");
    Serial.print(TVOC);
    Serial.print(", ");
    Serial.print(H2);
    Serial.print(", ");
    Serial.print(ethanol);
    Serial.print(", ");
    Serial.println(alcohol);
  }
}
