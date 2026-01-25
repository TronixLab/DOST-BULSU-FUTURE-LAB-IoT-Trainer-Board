/************************************************
Arduino Library
- Keypad
- v3.1.1
- Authors: Mark Stanley, Alexander Brevig
- Reference: https://github.com/Chris--A/Keypad
************************************************/
#include <Keypad.h>

#define DEBUG 1

#if DEBUG == 1
#define debug(x) Serial.print(x);
#define debugln(x) Serial.println(x);
#else
#define debug(x)
#define debugln(x)
#endif

// Define key layout
char keys[4][4] = {
  { '1', '2', '3', 'A' },
  { '4', '5', '6', 'B' },
  { '7', '8', '9', 'C' },
  { '*', '0', '#', 'D' }
};

// Safe GPIOs only
#define ROW1_PIN 2
#define ROW2_PIN 13
#define ROW3_PIN 12
#define ROW4_PIN 14
#define COL1_PIN 26
#define COL2_PIN 25
#define COL3_PIN 0
#define COL4_PIN 23

byte rowPins[4] = { ROW1_PIN, ROW2_PIN, ROW3_PIN, ROW4_PIN };
byte colPins[4] = { COL1_PIN, COL2_PIN, COL3_PIN, COL4_PIN };

Keypad keypad = Keypad(makeKeymap(keys), rowPins, colPins, 4, 4);

void setup() {
  Serial.begin(9600);
  debugln(F("[debug] 4x4 Keypad example using safe GPIOs"));
}

void loop() {
  char key = keypad.getKey();
  if (key) {
    debug(F("[debug] Key Pressed: "));
    debugln(key);
  }
}
