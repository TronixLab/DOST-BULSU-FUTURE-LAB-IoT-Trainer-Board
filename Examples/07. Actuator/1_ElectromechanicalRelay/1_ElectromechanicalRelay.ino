#define DEBUG 1
#if DEBUG == 1
#define debug(x) Serial.print(x);
#define debugln(x) Serial.println(x);
#else
#define debug(x)
#define debugln(x)
#endif

#define EMR_PIN 15  // GPIO connected to relay module input

void setup() {
  Serial.begin(9600);
  pinMode(EMR_PIN, OUTPUT);
  // Relay OFF by default
  debugln(F("[debug] Electromechanical Relay Initialized."));
  digitalWrite(EMR_PIN, LOW);
}

void loop() {
  debugln(F("[debug] Relay ON."));
  digitalWrite(EMR_PIN, HIGH);
  delay(2000);

  debugln(F("[debug] Relay OFF."));
  digitalWrite(EMR_PIN, LOW);
  delay(2000);
}
