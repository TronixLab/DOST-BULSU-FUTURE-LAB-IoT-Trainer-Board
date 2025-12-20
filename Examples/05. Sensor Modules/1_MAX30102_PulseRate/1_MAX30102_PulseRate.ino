/************************************************
Arduino Library
- SparkFun MAX3010x Pulse and Proximity Sensor
- v1.1.2
- Authors: SparkFun
- Reference: https://github.com/sparkfun/SparkFun_MAX3010x_Sensor_Library
************************************************/
#include <Wire.h>
#include "MAX30105.h"
#include "heartRate.h"

#define DEBUG 1

#if DEBUG == 1
#define debug(x) Serial.print(x);
#define debugln(x) Serial.println(x);
#else
#define debug(x)
#define debugln(x)
#endif

MAX30105 MAX30102;

// Declaration of variables
const byte RATE_SIZE = 4;
byte rates[RATE_SIZE];
byte rateSpot = 0;
long lastBeat = 0;
float beatsPerMinute;
int beatAvg;

void setup() {
  Serial.begin(9600);

  // Initialize sensor
  if (!MAX30102.begin(Wire, I2C_SPEED_FAST)) {
    debugln(F("MAX30102 was not found. Please check wiring/power."));
    while (1)
      ;
  }

  debugln(F("Place your index finger on the sensor with steady pressure."));
  MAX30102.setup();                     // Configure sensor with default settings
  MAX30102.setPulseAmplitudeRed(0x0A);  // Turn Red LED to low to indicate sensor is running
  MAX30102.setPulseAmplitudeGreen(0);   // Turn off Green LED
}

void loop() {
  long irValue = MAX30102.getIR();

  if (checkForBeat(irValue) == true) {
    long delta = millis() - lastBeat;
    lastBeat = millis();
    beatsPerMinute = 60 / (delta / 1000.0);
    if (beatsPerMinute < 255 && beatsPerMinute > 20) {
      rates[rateSpot++] = (byte)beatsPerMinute;
      rateSpot %= RATE_SIZE;

      // Take average of readings
      beatAvg = 0;
      for (byte x = 0; x < RATE_SIZE; x++)
        beatAvg += rates[x];
      beatAvg /= RATE_SIZE;
    }
  }

  debug(F("[debug] IR="));
  debug(irValue);
  debug(F(", BPM="));
  debug(beatsPerMinute);
  debug(F(", Avg BPM="));
  debugln(beatAvg);

  if (irValue < 50000) debugln(F("[debug] No finger is detected."));
  debugln();
}