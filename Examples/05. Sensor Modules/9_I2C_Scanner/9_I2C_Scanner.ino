#include "Wire.h"

#define DEBUG 1
#if DEBUG == 1
#define debug(x) Serial.print(x);
#define debugln(x) Serial.println(x);
#else
#define debug(x)
#define debugln(x)
#endif

void setup() {
  Serial.begin(9600);
  Wire.begin();
}

void loop() {
  byte error, address;
  int nDevices = 0;

  debugln(F("[debug] Scanning for I2C devices ..."));
  for (address = 0x01; address < 0x7f; address++) {
    Wire.beginTransmission(address);
    error = Wire.endTransmission();
    if (error == 0) {
      debug(F("[debug] I2C device found at address 0x"));
      debugln(address);
      nDevices++;
    } else if (error != 2) {
      debug(F("[debug] Error"));
      debug(error);
      debug(F("at address 0x\n"));
      debug(address);
    }
  }
  if (nDevices == 0) {
    debugln(F("[debug] No I2C devices found"));
  }
  delay(5000);
}
