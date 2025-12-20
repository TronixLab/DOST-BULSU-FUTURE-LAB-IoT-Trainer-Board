#define DEBUG 1

#if DEBUG == 1
#define debug(x) Serial.print(x);
#define debugln(x) Serial.println(x);
#else
#define debug(x)
#define debugln(x)
#endif

#define A_PIN 4
#define B_PIN 2
#define C_PIN 15
#define D_PIN 13

// BCD pins connected to CD4511 A, B, C, D respectively
const int bcdPins[4] = { A_PIN, B_PIN, C_PIN, D_PIN };

void setup() {
  Serial.begin(9600);
  // Initialized GPIO pins
  for (int i = 0; i < 4; i++) {
    pinMode(bcdPins[i], OUTPUT);
  }
}

void loop() {
  // show digit 0–9 every one second
  for (int i = 0; i < 10; i++) {
    displayDigit(i);
    debug(F("[debug] Seven Segment Display: "));
    debug(i);
    debugln();
    delay(1000);
  }
}

void displayDigit(int num) {
  debug(F("[debug] Binary: "));
  for (int i = 4; i >= 0; i--) {
    digitalWrite(bcdPins[i], bitRead(num, i));
    debug(bitRead(num, i));
  }
  debugln();
}