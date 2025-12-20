#define DEBUG 1

#if DEBUG == 1
#define debug(x) Serial.print(x);
#define debugln(x) Serial.println(x);
#else
#define debug(x)
#define debugln(x)
#endif

// Rotary Encoder Inputs
#define OUTA_PIN 13
#define OUTB_PIN 12
#define SWITCH_PIN 14

int counter = 0;
int currentStateCLK;
int lastStateCLK;
String currentDir = "";
unsigned long lastButtonPress = 0;

void setup() {
  Serial.begin(9600);

  // Set encoder pins as inputs
  pinMode(OUTB_PIN, INPUT);
  pinMode(OUTA_PIN, INPUT);
  pinMode(SWITCH_PIN, INPUT_PULLUP);
  // Read the initial state of OUTB_PIN
  lastStateCLK = digitalRead(OUTB_PIN);
}

void loop() {

  // Read the current state of OUTB_PIN
  currentStateCLK = digitalRead(OUTB_PIN);

  // If last and current state of OUTB_PIN are different, then pulse occurred
  // React to only 1 state change to avoid double count
  if (currentStateCLK != lastStateCLK && currentStateCLK == 1) {

    // If the OUTA_PIN state is different than the OUTB_PIN state then
    // the encoder is rotating CCW so decrement
    if (digitalRead(OUTA_PIN) != currentStateCLK) {
      counter--;
      currentDir = "CCW";
    } else {
      // Encoder is rotating CW so increment
      counter++;
      currentDir = "CW";
    }

    debug(F("[debug] Direction: "));
    debug(currentDir);
    debug(F(" | Counter: "));
    debugln(counter);
  }

  // Remember last OUTB_PIN state
  lastStateCLK = currentStateCLK;

  // Read the button state
  int btnState = digitalRead(SWITCH_PIN);

  // If we detect LOW signal, button is pressed
  if (btnState == LOW) {
    // If 50ms have passed since last LOW pulse, it means that the
    // button has been pressed, released and pressed again
    if (millis() - lastButtonPress > 50) {
      debugln(F("[debug] Button pressed!"));
    }

    // Remember last button press event
    lastButtonPress = millis();
  }

  // Put in a slight delay to help debounce the reading
  delay(1);
}