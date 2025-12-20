#define DEBUG 1

#if DEBUG == 1
#define debug(x) Serial.print(x);
#define debugln(x) Serial.println(x);
#else
#define debug(x)
#define debugln(x)
#endif

#define SOIL_PIN 36  // Use GPIO36 pin

// Timing parameters
const uint32_t READ_INTERVAL = 1000;  // Measurement interval (ms)
uint32_t lastReadTime = 0;            // Last measurement timestamp

void setup() {
  Serial.begin(9600);        // Initialize serial at 9600 baud
  analogReadResolution(12);  // Configure ADC to 12-bit resolution (0-4095)
}

void loop() {
  uint32_t currentTime = millis();  // Get current time

  // Execute at fixed intervals without blocking
  if (currentTime - lastReadTime >= READ_INTERVAL) {
    lastReadTime = currentTime;  // Update timing reference

    // Read raw ADC value (0-4095)
    uint16_t rawValue = analogRead(SOIL_PIN);

    // Convert ADC value to milli-voltage (0-3.3V)
    uint16_t voltage = analogReadMilliVolts(SOIL_PIN);

    // Map sensor value...
    // in case the sensor value is outside the range seen during calibration
    rawValue = constrain(rawValue, 1000, 2500);
    int soilMoisturePercent = map(rawValue, 2500, 1000, 0, 100);

    // Print formatted data to serial monitor
    debug(F("ADC value:"));
    debug(rawValue);
    debug(F("   ADC voltage:"));
    debug(voltage);
    debug(F("mV   Percent Moisture:"));
    debug(soilMoisturePercent);
    debugln(F("%"));
  }
}
