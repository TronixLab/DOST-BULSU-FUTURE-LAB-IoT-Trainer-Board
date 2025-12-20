#define DEBUG 1

#if DEBUG == 1
#define debug(x) Serial.print(x);
#define debugln(x) Serial.println(x);
#else
#define debug(x)
#define debugln(x)
#endif

/*************************
Touch Pins   | GPIO Pins
TOUCH0 (T0)  | IO04
TOUCH1 (T1)  | IO00
TOUCH2 (T2)  | IO02
TOUCH3 (T3)  | IO15
TOUCH4 (T4)  | IO13
TOUCH5 (T5)  | IO12
TOUCH6 (T6)  | IO14
**************************/
#define TP1_PIN T0           // GPIO 4
#define TOUCH_THRESHOLD 150  // Adjust threshold as needed

void setup() {
  Serial.begin(9600);
}

void loop() {
  // Read touch pin value
  uint16_t touchValue = touchRead(TP1_PIN);
  debug(F("[debug] Touch Pad 1 Value: "));
  debugln(touchValue);

  // Check if your finger is detected in the touch pad
  if (touchValue < TOUCH_THRESHOLD) {
    debugln(F("[debug] Touch Pad TP1: touch detected!"));
  }
  delay(200);
}