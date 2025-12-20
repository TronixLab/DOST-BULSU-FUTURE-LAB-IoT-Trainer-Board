#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <LiquidCrystal_I2C.h>
#include "Picopixel.h"

// OLED configuration
#define OLED_SDA 21       // OLED SDA pin (ESP32 default)
#define OLED_SCL 22       // OLED SCL pin (ESP32 default)
#define OLED_RST -1       // Reset pin (-1 = unused)
#define SCREEN_WIDTH 128  // OLED width in pixels
#define SCREEN_HEIGHT 64  // OLED height in pixels

Adafruit_SSD1306 oled(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RST);

// Timer variables
unsigned long lastTime = 0;
unsigned long timerDelay = 5000;

// Variables to hold sensor readings
unsigned long epochTime;
float tempC;
float humidity;
float heatIndexC;

void setup() {
  Serial.begin(9600);  // Start serial communication at 9600 baud

  // Configure I2C communication for OLED
  Wire.begin(OLED_SDA, OLED_SCL);

  // Initialize OLED display
  if (!oled.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
    Serial.println(F("SSD1306 allocation failed"));
    while (true)
      ;  // Halt execution if display fails
  }

  // Display boot-up configuration
  oled.setTextColor(WHITE);
}

void loop() {
  if ((millis() - lastTime) > timerDelay) {
    lastTime = millis();

    tempC = random(2000.00, 5000.00) / 100.00;
    humidity = random(8000.00, 10000.00) / 100.00;
    heatIndexC = random(2700, 3200) / 100.00;

    String sensorData = String(tempC) + "," + String(humidity) + "," + String(heatIndexC) + "\r\n";
    Serial.print("Saving data: ");
    Serial.print(sensorData);

    // OLED Display Routine
    oled.clearDisplay();
    oled.setTextSize(1);
    oled.drawBitmap(-3, -2, image_download_bits, 71, 64, 1);
    oled.setTextColor(1);
    oled.setTextWrap(false);
    oled.setFont(&Picopixel);
    oled.setCursor(73, 50);
    oled.print("HUMIDITY");
    oled.setCursor(73, 29);
    oled.print("HEAT INDEX");
    oled.drawBitmap(73, 2, image_Layer_5_bits, 45, 5, 1);
    oled.setCursor(73, 19);
    oled.setTextSize(2);
    oled.print(tempC);
    oled.setCursor(73, 41);
    oled.print(heatIndexC);
    oled.setCursor(73, 62);
    oled.print(humidity);
    oled.println(F("%"));
    oled.display();
  }
}
