#define DEBUG 1
#if DEBUG == 1
#define debug(x) Serial.print(x);
#define debugln(x) Serial.println(x);
#else
#define debug(x)
#define debugln(x)
#endif

#define BUZZ_PIN 15  // GPIO connected to relay module input

void setup() {
  Serial.begin(9600);
  pinMode(BUZZ_PIN, OUTPUT);
}

void loop() {
  debugln("[debug] Buzzer sound ON.");
  digitalWrite(BUZZ_PIN, HIGH);  
  delay(2000);

  debugln("[debug] Buzzer sound OFF.");
  digitalWrite(BUZZ_PIN, LOW);  
  delay(2000);
}
