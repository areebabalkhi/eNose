#include "SparkFun_SGP30_Arduino_Library.h"  // Air quality sensor library
#include <Wire.h>

const int MQ3Pin = A5;  // Alcohol sensor pin
SGP30 mySensor;
long t1, t2;

void setup() {
  // put your setup code here, to run once:

  Serial.begin(9600);
  Wire.begin();
  Wire.setClock(400000);

  if (mySensor.begin() == false) {
    Serial.println(F("SGP30 not detected. Check connections. Freezing..."));
    while (1)
      ;  // Do nothing more
  }

  mySensor.initAirQuality();
  t1 = millis();
}

void loop() {
  // put your main code here, to run repeatedly:
  t2 = millis();
  if (t2 >= t1 + 1000) {
    t1 = t2;
    mySensor.measureAirQuality();
    Serial.print("CO2: ");
    Serial.print(mySensor.CO2);
    Serial.print(" ppm\tTVOC: ");
    Serial.print(mySensor.TVOC);
    Serial.println(" ppb");
    //get raw values for H2 and Ethanol
    mySensor.measureRawSignals();
    Serial.print("Raw H2: ");
    Serial.print(mySensor.H2);
    Serial.print(" \tRaw Ethanol: ");
    Serial.println(mySensor.ethanol);

    float alcRead = analogRead(MQ3Pin);
    Serial.print("Alc: ");
    Serial.println(alcRead);
  }
}
