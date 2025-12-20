#define LED_BUILTIN 25  // Define LED pin

void setup() {
  Serial.begin(9600);            // Initialize Serial Communication
  pinMode(LED_BUILTIN, OUTPUT);  // Configure onboard LED (IO25)
}

void loop() {
  digitalWrite(LED_BUILTIN, HIGH);    // Onboard LED ON
  Serial.println("LED State: HIGH");  // Print LED status to Arduino Serial Monitor
  delay(500);                         // delay for 500ms
  digitalWrite(LED_BUILTIN, LOW);     // Onboard LED OFF
  Serial.println("LED State: LOW");   // Print LED status to Arduino Serial Monitor
  delay(500);                         // delay for 500ms
}
