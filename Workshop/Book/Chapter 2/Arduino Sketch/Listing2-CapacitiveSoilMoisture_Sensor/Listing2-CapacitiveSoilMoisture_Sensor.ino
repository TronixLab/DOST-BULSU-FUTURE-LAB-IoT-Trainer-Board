#include <Wire.h>              // I2C communication
#include <Adafruit_GFX.h>      // Core graphics library
#include <Adafruit_SSD1306.h>  // OLED display driver

// Hardware configuration
#define SENSOR_PIN 36   // Use GPIO36 pin
#define ADC_Res_bit 12  // Set the resolution to 9-12 bits (default is 12 bits)
#define OLED_SDA 21     // OLED SDA pin (ESP32 default)
#define OLED_SCL 22     // OLED SCL pin (ESP32 default)
#define OLED_RST -1     // Reset pin (-1 = unused)

// OLED display parameters
#define SCREEN_WIDTH 128  // OLED width in pixels
#define SCREEN_HEIGHT 64  // OLED height in pixels

// Initialize hardware objects
Adafruit_SSD1306 oled(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RST);

// Timing parameters
const uint32_t READ_INTERVAL = 1000;  // Measurement interval (ms)
uint32_t lastReadTime = 0;            // Last measurement timestamp

void setup() {
  Serial.begin(115200);  // Initialize serial at 115200 baud

  analogReadResolution(ADC_Res_bit);  // Configure ADC to 12-bit resolution (0-4095)

  // Initialize OLED display
  if (!oled.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {  // 0x3C = I2C address
    Serial.println(F("SSD1306 allocation failed"));
    while (true)
      ;  // Halt execution if display fails
  }

  // Display boot-up configuration
  oled.setTextSize(1);
  oled.setTextColor(WHITE);
  oled.display();
}

void loop() {
  uint32_t currentTime = millis();  // Get current time

  // Execute at fixed intervals without blocking
  if (currentTime - lastReadTime >= READ_INTERVAL) {
    lastReadTime = currentTime;  // Update timing reference

    // Read raw ADC value (0-4095)
    uint16_t rawValue = analogRead(SENSOR_PIN);

    // Convert ADC value to milli-voltage (0-3.3V)
    uint16_t voltage = analogReadMilliVolts(SENSOR_PIN);

    // Print formatted data to serial monitor
    Serial.print("ADC value:");
    Serial.print(rawValue);  // Raw ADC value (0-4095)
    Serial.print("\t ADC voltage:");
    Serial.print(voltage);  // Input voltage in milli-volts
    Serial.println("mV");

    // OLED Display Routine
    oled.clearDisplay();
    oled.setCursor(0, 0);

    // Display formatted data
    oled.print(F("ADC value: "));
    oled.println(rawValue);
    oled.print(F("ADC voltage: "));
    oled.print(voltage);
    oled.println(F("mV"));
    oled.display();
  }
}
