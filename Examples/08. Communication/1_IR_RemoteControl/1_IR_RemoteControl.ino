/************************************************
Arduino Library
- Keypad
- v4.5.0
- Authors: shirriff, z3t0, ArminJo
- Reference: https://github.com/Arduino-IRremote/Arduino-IRremote
************************************************/
#include <IRremote.h>

#define DEBUG 1
#if DEBUG == 1
#define debug(x) Serial.print(x);
#define debugln(x) Serial.println(x);
#else
#define debug(x)
#define debugln(x)
#endif

#define IR_PIN 4

void setup() {
  Serial.begin(9600);
  IrReceiver.begin(IR_PIN, ENABLE_LED_FEEDBACK);
}

void loop() {
  if (IrReceiver.decode()) {
    uint16_t command = IrReceiver.decodedIRData.command;
    switch (command) {
      case 69:
        debugln(F("1"));
        break;
      case 70:
        debugln(F("2"));
        break;
      case 71:
        debugln(F("3"));
        break;
      case 68:
        debugln(F("4"));
        break;
      case 64:
        debugln(F("5"));
        break;
      case 67:
        debugln(F("6"));
        break;
      case 7:
        debugln(F("7"));
        break;
      case 21:
        debugln(F("8"));
        break;
      case 9:
        debugln(F("9"));
        break;
      case 22:
        debugln(F("*"));
        break;
      case 25:
        debugln(F("0"));
        break;
      case 13:
        debugln(F("#"));
        break;
      case 24:
        debugln(F("UP"));
        break;
      case 8:
        debugln(F("LEFT"));
        break;
      case 28:
        debugln(F("OK"));
        break;
      case 90:
        debugln(F("RIGHT"));
        break;
      case 82:
        debugln(F("DOWN"));
        break;
      default:
        debugln(F("Unknown Command!"));
        break;
    }
    IrReceiver.resume();
  }
  delay(100);
}