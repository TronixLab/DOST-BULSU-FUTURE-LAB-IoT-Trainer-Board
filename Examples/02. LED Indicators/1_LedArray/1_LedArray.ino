#define DEBUG 1

#if DEBUG == 1
#define debug(x) Serial.print(x);
#define debugln(x) Serial.println(x);
#else
#define debug(x)
#define debugln(x)
#endif

#define NUM_PATTERNS 17
#define NUM_LEDS 7

const byte LED_patterns[NUM_PATTERNS] = {
  0b1000001,  // Pattern 1
  0b0100010,  // Pattern 2
  0b0010100,  // Pattern 3
  0b0001000,  // Pattern 4
  0b1001001,  // Pattern 5
  0b0101010,  // Pattern 6
  0b0011100,  // Pattern 7
  0b1011101,  // Pattern 8
  0b0111110,  // Pattern 9
  0b1111111,  // Pattern 10
  0b1110111,  // Pattern 11
  0b1100011,  // Pattern 12
  0b1000001,  // Pattern 13
  0b0000000,  // Pattern 14
  0b1111111,  // Pattern 15
  0b0000000,  // Pattern 16
  0b1111111   // Pattern 17
};

#define LED1_PIN 25
#define LED2_PIN 4
#define LED3_PIN 2
#define LED4_PIN 15
#define LED5_PIN 13
#define LED6_PIN 12
#define LED7_PIN 14

const int ledPins[] = { LED1_PIN, LED2_PIN, LED3_PIN, LED4_PIN, LED5_PIN, LED6_PIN, LED7_PIN };

void setup() {
  Serial.begin(9600);
  // Initialized I/O pins
  for (int i = 0; i < NUM_LEDS; i++) {
    pinMode(ledPins[i], OUTPUT);
  }
}

void loop() {
  // Display LEDs patterns for every 100 ms
  for (int i = 0; i < NUM_PATTERNS; i++) {
    debug(F("[debug] Printing LED pattern: "));
    for (int j = 0; j < NUM_LEDS; j++) {
      digitalWrite(ledPins[j], bitRead(LED_patterns[i], j));
    }
    String ledPattern = BinarytoString(LED_patterns[i], 7);
    debugln(ledPattern);
    delay(100);
  }
  debugln();
}

String BinarytoString(int value, int numBits) {
  String result = "";
  for (int i = numBits - 1; i >= 0; i--) {
    // Check if the i-th bit is set and append '1' or '0'
    if ((value >> i) & 1) {
      result += '1';
    } else {
      result += '0';
    }
  }
  return result;
}