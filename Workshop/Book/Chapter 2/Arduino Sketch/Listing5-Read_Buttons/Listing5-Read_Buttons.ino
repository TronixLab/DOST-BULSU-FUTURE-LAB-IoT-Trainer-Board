// Define the pin number for the button
#define BUTTON1_PIN 12  // Button only that uses MCU pull-up resistor
#define BUTTON3_PIN 14  // Configurable resistor push button

void setup() {
  // Initialize serial communication at 115200 baud for debugging
  Serial.begin(115200);

  // Set BUTTON3_PIN as an input to read button state
  pinMode(BUTTON3_PIN, INPUT);

  // Set BUTTON1_PIN as an input to read button state
  // MCU initialize pull-up/pull-down resistor
  // uncomment the line of code  below if using Button 1
  // pinMode(BUTTON1_PIN, mode);   // mode: INPUT_PULLDOWN / INPUT_PULLUP

  // Set the built-in LED pin as an output (indicator)
  pinMode(LED_BUILTIN, OUTPUT);
}

void loop() {
  // Read the state of the button (HIGH if pressed, LOW if not)
  int button3State = digitalRead(BUTTON3_PIN);

  // Uncomment the line of code below if using button 1
  // then comment out the line of code  above
  // int button1State = digitalRead(BUTTON1_PIN);

  // If the button state is HIGH
  // If using button 1, then use button1State variable
  if (button3State == HIGH) {
    Serial.println("Turn on LED");    // Print status to Serial Monitor
    digitalWrite(LED_BUILTIN, HIGH);  // Turn ON the built-in LED
  } else {
    Serial.println("Off LED");       // Print status to Serial Monitor
    digitalWrite(LED_BUILTIN, LOW);  // Turn OFF the built-in LED
  }
}