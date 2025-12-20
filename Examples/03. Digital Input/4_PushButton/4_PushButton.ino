#define DEBUG 1

#if DEBUG == 1
#define debug(x) Serial.print(x);
#define debugln(x) Serial.println(x);
#else
#define debug(x)
#define debugln(x)
#endif

/*************************
Configurable Push Buttons
Buttons  | Header Pins
BUTTON 3 | BTN3
BUTTON 4 | BTN4
BUTTON 5 | BTN5
BUTTON 6 | BTN6
**************************/

#define BTN3_PIN 4
#define LED1_PIN 25

void setup() {
  Serial.begin(9600);
  // Initialize the LED pin as an output:
  pinMode(LED1_PIN, OUTPUT);
  // Initialize the pushbutton pin as an input:
  pinMode(BTN3_PIN, INPUT);
}

void loop() {
  // Read the state of the pushbutton value:
  int buttonState = digitalRead(BTN3_PIN);

  // Check if the pushbutton is pressed. If it is, the buttonState is HIGH:
  if (buttonState == HIGH) {
    digitalWrite(LED1_PIN, HIGH);
    debugln(F("The push button is pressed. Turn LED on."));
  } else {
    digitalWrite(LED1_PIN, LOW);
    debugln(F("The push button is not pressed. Turn LED off."));
  }
}