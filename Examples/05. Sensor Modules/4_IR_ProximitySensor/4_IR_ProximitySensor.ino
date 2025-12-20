#define VOUT_PIN 4

#define DEBUG 1
#if DEBUG == 1
#define debug(x) Serial.print(x);
#define debugln(x) Serial.println(x);
#else
#define debug(x)
#define debugln(x)
#endif

void setup() {
  Serial.begin(9600);
  pinMode(VOUT_PIN, INPUT);
}

void loop() {
  int irValue = digitalRead(VOUT_PIN);

  if (irValue == LOW) {
    debugln(F("Object Detected!"));
  } else {
    debugln(F("No Object."));
  }
  delay(100);
}
