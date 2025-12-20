#define DEBUG 1

#if DEBUG == 1
#define debug(x) Serial.print(x);
#define debugln(x) Serial.println(x);
#else
#define debug(x)
#define debugln(x)
#endif

#define POT1_PIN 36  // GPIO 36 is ADC1 channel 0 on ESP32

void setup() {
  Serial.begin(9600);

  // Set the resolution to 12 bits (0-4095)
  analogReadResolution(12);
}

void loop() {
  // Read the raw analog value for pin 36 / ADC1 channel 0
  int analogValue = analogRead(POT1_PIN);
  // Read the millivolts value for pin 36 / ADC1 channel 0
  int analogVolts = analogReadMilliVolts(POT1_PIN);

  // Print out the values you read:
  debug(F("ADC analog value = "));
  debugln(analogValue);

  debug(F("ADC millivolts value ="));
  debugln(analogVolts);

  delay(100);
}