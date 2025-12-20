#define DEBUG 1

#if DEBUG == 1
#define debug(x) Serial.print(x);
#define debugln(x) Serial.println(x);
#else
#define debug(x)
#define debugln(x)
#endif

// These constants should match the photoresistor's "gamma" and "RL10" attributes
#define GAMMA 0.65
#define RL10 10.00

#define SENSOR_PIN 36  // Use GPIO36 pin

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

    // Convert ADC value to voltage (0-3.3V)
    double voltage = analogReadMilliVolts(SENSOR_PIN) / 1000.00;

    // Calculate equivalent photoresistor resistance using voltage divider
    double resistance = (voltage * 10000.00) / (5.00 - voltage);

    // Compute for lux level
    double lux = pow(RL10 * 1e3 * pow(10, GAMMA) / resistance, (1 / GAMMA)) * 10.00;

    if (isfinite(lux)) {
      // Print formatted data to serial monitor
      debug(F("[debug] LDR voltage:"));
      debug(voltage);
      debug(F("V   Resistance:"));
      debug(resistance);
      debug(F("Ω   Lux level:"));
      debug(lux);
      debugln(F("lx"));
    } else {
      debugln(F("[debug] Illuminance cannot be measured!"));
    }
  }
}