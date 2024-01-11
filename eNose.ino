#include "SparkFun_SGP30_Arduino_Library.h"  // Air quality sensor library
#include <Wire.h>

const int MQ3Pin = A0;  // Alcohol sensor pin
SGP30 AQSensor; // Air quality sensor object
long t1, t2; // For timing

long CO2, TVOC, H2, ethanol, alcohol;

void setup() {
  Serial.begin(9600);
  Wire.begin();
  Wire.setClock(400000);

  if (AQSensor.begin() == false) {
    Serial.println(F("SGP30 not detected. Check connections. Freezing..."));
    while (1)
      ;  // Do nothing more
  }

  mySensor.initAirQuality();
  t1 = millis();
}

void loop() {
  t2 = millis();
  if (t2 >= t1 + 1000) {
    t1 = t2;
    // Get air quality sensor data
    AQSensor.measureAirQuality();
    CO2 = AQSensor.CO2; // in ppm
    TVOC = AQSensor.TVOC; // in ppb

    AQSensor.measureRawSignals();
    H2 = AQSensor.H2;
    ethanol = AQSensor.ethanol;

    alcohol = analogRead(MQ3Pin); // Read alcohol sensor value

    
    // Output readings in csv format
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
