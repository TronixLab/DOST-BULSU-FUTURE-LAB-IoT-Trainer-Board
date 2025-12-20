#define DEBUG 1
#if DEBUG == 1
#define debug(x) Serial.print(x);
#define debugln(x) Serial.println(x);
#else
#define debug(x)
#define debugln(x)
#endif

#define SSR_PIN 15  // GPIO connected to relay module input

void setup() {
  Serial.begin(9600);
  pinMode(SSR_PIN, OUTPUT);
  // Relay OFF by default
  debugln(F("[debug] Solid State Relay Initialized."));
  digitalWrite(SSR_PIN, LOW);
}

void loop() {
  debugln(F("[debug] Relay ON."));
  digitalWrite(SSR_PIN, HIGH);  // Activate relay
  delay(2000);

  debugln(F("[debug] Relay OFF."));
  digitalWrite(SSR_PIN, LOW);  // Deactivate relay
  delay(2000);

  debugln(F("[debug] Relay fade control..."));
  for (int fadeValue = 0; fadeValue <= 255; fadeValue += 5) {
    analogWrite(SSR_PIN, fadeValue);
    delay(30);
  }
  for (int fadeValue = 255; fadeValue >= 0; fadeValue -= 5) {
    analogWrite(SSR_PIN, fadeValue);
    delay(30);
  }
  delay(2000);
}
