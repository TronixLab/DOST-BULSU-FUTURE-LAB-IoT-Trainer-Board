#define DEBUG 1

#if DEBUG == 1
#define debug(x) Serial.print(x);
#define debugln(x) Serial.println(x);
#else
#define debug(x)
#define debugln(x)
#endif

/*************************
Push Buttons without Resistor
Buttons  | Header Pins
BUTTON 1 | BTN1
BUTTON 2 | BTN2
**************************/
#define BTN1_PIN 4
#define LED1_PIN 25

void setup() {
  Serial.begin(9600);
  // Configure pin 4 as an input and enable the internal pull-up resistor
  pinMode(BTN1_PIN, INPUT_PULLUP);
  pinMode(LED1_PIN, OUTPUT);
}

void loop() {
  // Read the pushbutton value into a variable
  int bottonVal = digitalRead(BTN1_PIN);
  debug(F("Button Status: "));
  debugln(bottonVal);

  // Keep in mind the pull-up means the pushbutton's logic is inverted. It goes
  // HIGH when it's open, and LOW when it's pressed. Turn on pin 13 when the
  // button's pressed, and off when it's not:
  if (bottonVal == HIGH) {
    digitalWrite(LED1_PIN, LOW);
    debugln(F("The push button is pressed. Turn LED off."));
  } else {
    digitalWrite(LED1_PIN, HIGH);
    debugln(F("The push button is not pressed. Turn LED on."));
  }
}