#define SIG_PIN 4       // PIR sensor output connected to GPIO 19
#define LED_BUILTIN 25  // Define LED pin

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
  pinMode(SIG_PIN, INPUT);
  pinMode(LED_BUILTIN, OUTPUT);
}

void loop() {
  int motion = digitalRead(SIG_PIN);

  if (motion == HIGH) {
    debugln(F("Motion Detected!"));
    digitalWrite(LED_BUILTIN, HIGH);  
  } else {
    debugln(F("No Motion."));
    digitalWrite(LED_BUILTIN, LOW); 
  }
  delay(100);  // Wait before next reading
}
