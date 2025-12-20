/************************************************
Arduino Library
- AGS10
- vx.x.x
- Authors: Gina Seth
- Reference: https://github.com/gina-seth/AGS10_sensor
************************************************/
#include <AGS10.h>
#include <Wire.h>

#define DEBUG 1
#if DEBUG == 1
#define debug(x) Serial.print(x);
#define debugln(x) Serial.println(x);
#else
#define debug(x)
#define debugln(x)
#endif

AGS10 ags = AGS10();

void setup() {
  Serial.begin(9600);
  // Initialize AGS10 sensor
  ags.begin();
  // Factory calibrate AGS10 sensor
  ags.calibrateFact();
}

void loop() {
  // Read TVOC values
  int tvoc = ags.readTVOC();

  debug(F("[debug] TVOC: "));
  debug(tvoc);
  debug(F(" ppb - "));

  if (tvoc < 220) {
    debugln(F("Good Air Quality."));
  } else if (tvoc >= 220 && tvoc < 660) {
    debugln(F("Moderate Air Quality."));
  } else if (tvoc >= 660 && tvoc < 2200) {
    debugln(F("Poor Air Quality."));
  } else if (tvoc >= 2200) {
    debugln(F("Very Poor Air Quality!!!"));
  }

  // Delay every 2 seconds, according to datasheet, max speed is 1.5 seconds/reading
  delay(2000);
}