#define DEBUG 1

#if DEBUG == 1
#define debug(x) Serial.print(x);
#define debugln(x) Serial.println(x);
#else
#define debug(x)
#define debugln(x)
#endif

#define X_AXIS_PIN 36  // Analog input for X-axis
#define Y_AXIS_PIN 39  // Analog input for Y-axis
#define SWITCH_PIN 14  // Digital input for switch

void setup() {
  Serial.begin(9600);
  analogReadResolution(12);
  pinMode(SWITCH_PIN, INPUT_PULLUP);
}

void loop() {
  int xVal = analogRead(X_AXIS_PIN);
  int yVal = analogRead(Y_AXIS_PIN);
  bool buttonPressed = digitalRead(SWITCH_PIN);

  debug(F("X: "));
  debug(xVal);
  debug(F("\tY: "));
  debug(yVal);
  debug(F("\tButton: "));
  debugln(buttonPressed ? "Released" : "PRESSED");
  delay(200);
}
