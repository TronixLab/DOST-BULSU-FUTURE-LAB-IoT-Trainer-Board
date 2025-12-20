#define DEBUG 1

#if DEBUG == 1
#define debug(x) Serial.print(x);
#define debugln(x) Serial.println(x);
#else
#define debug(x)
#define debugln(x)
#endif

// Define GPIO pins for LEDs
#define STOP_PIN 14
#define WAIT_PIN 13
#define GO_PIN 12

void setup() {
  // Initialize serial communication for debugging
  Serial.begin(9600);
  debugln(F("[debug] Traffic Light Demo"));

  // Configure LED pins as outputs
  pinMode(STOP_PIN, OUTPUT);
  pinMode(WAIT_PIN, OUTPUT);
  pinMode(GO_PIN, OUTPUT);

  // Ensure all LEDs are off initially
  digitalWrite(STOP_PIN, LOW);
  digitalWrite(WAIT_PIN, LOW);
  digitalWrite(GO_PIN, LOW);
}

void loop() {
  // Red Light Phase
  digitalWrite(STOP_PIN, HIGH);
  digitalWrite(WAIT_PIN, LOW);
  digitalWrite(GO_PIN, LOW);
  debugln(F("[debug] Traffic Light State: STOP! (RED)"));
  delay(5000);

  // Orange Light Phase
  digitalWrite(STOP_PIN, LOW);
  digitalWrite(WAIT_PIN, HIGH);
  digitalWrite(GO_PIN, LOW);
  debugln(F("[debug] Traffic Light State: Warning! (ORANGE)"));
  delay(5000);

  // Green Light Phase
  digitalWrite(STOP_PIN, LOW);
  digitalWrite(WAIT_PIN, LOW);
  digitalWrite(GO_PIN, HIGH);
  debugln(F("[debug] Traffic Light State: Go. (GREEN)"));
  delay(5000);
}
