#define DEBUG 1

#if DEBUG == 1
#define debug(x) Serial.print(x);
#define debugln(x) Serial.println(x);
#else
#define debug(x)
#define debugln(x)
#endif

// Define the analog pin, the TMP36's Vout pin is connected to
#define TMP_PIN 36

void setup() {
  // Begin serial communication at 9600 baud rate
  Serial.begin(9600);
}

void loop() {
  // Get the voltage reading from the TMP36
  float voltage = analogReadMilliVolts(TMP_PIN);
  // Convert the voltage into the temperature in Celsius
  float temperatureC = (voltage - 500.00) / 10.00;

  // Print the temperature in Celsius
  debug(F("[debug] Temperature: "));
  debug(temperatureC);
  debug(F("°C  |  "));

  // Print the temperature in Fahrenheit
  float temperatureF = (temperatureC * 9.0 / 5.0) + 32.0;
  debug(temperatureF);
  debugln(F("°F"));

  delay(1000);  // Wait a second between readings
}