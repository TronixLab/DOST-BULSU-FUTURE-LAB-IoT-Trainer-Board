#define DEBUG 1

#if DEBUG == 1
#define debug(x) Serial.print(x);
#define debugln(x) Serial.println(x);
#else
#define debug(x)
#define debugln(x)
#endif

#define SEGA_PIN 25
#define SEGB_PIN 4
#define SEGC_PIN 2
#define SEGD_PIN 15
#define SEGE_PIN 13
#define SEGF_PIN 12
#define SEGG_PIN 14

// I/O pins in an array variable
const int segPins[7] = {
  SEGA_PIN,  // A
  SEGB_PIN,  // B
  SEGC_PIN,  // C
  SEGD_PIN,  // D
  SEGE_PIN,  // E
  SEGF_PIN,  // F
  SEGG_PIN   // G
};

// LEDs patterns represented in nested array
const byte digits[10][7] = {
  { 1, 1, 1, 1, 1, 1, 0 },  // 0
  { 0, 1, 1, 0, 0, 0, 0 },  // 1
  { 1, 1, 0, 1, 1, 0, 1 },  // 2
  { 1, 1, 1, 1, 0, 0, 1 },  // 3
  { 0, 1, 1, 0, 0, 1, 1 },  // 4
  { 1, 0, 1, 1, 0, 1, 1 },  // 5
  { 1, 0, 1, 1, 1, 1, 1 },  // 6
  { 1, 1, 1, 0, 0, 0, 0 },  // 7
  { 1, 1, 1, 1, 1, 1, 1 },  // 8
  { 1, 1, 1, 1, 0, 1, 1 }   // 9
};

void setup() {
  Serial.begin(9600);
  // Initials I/O pins
  for (int i = 0; i < 7; i++) {
    pinMode(segPins[i], OUTPUT);
  }
}

void loop() {
  // Show digit 0–9 every one second
  for (int i = 0; i < 10; i++) {
    displayDigit(i);
    debug(F("[debug] Displaying digit: "));
    debugln(i);
    delay(1000);
  }
}

void displayDigit(int num) {
  for (int i = 0; i < 7; i++) {
    digitalWrite(segPins[i], digits[num][i]);
  }
}