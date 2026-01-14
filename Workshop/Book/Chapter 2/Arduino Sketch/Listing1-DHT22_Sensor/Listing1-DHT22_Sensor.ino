#include <DHT.h>               // DHT sensor library
#include <Wire.h>              // I²C communication
#include <Adafruit_GFX.h>      // Core graphics library
#include <Adafruit_SSD1306.h>  // OLED display driver

// Hardware configuration
#define OLED_SDA 21    // OLED SDA pin (ESP32 default)
#define OLED_SCL 22    // OLED SCL pin (ESP32 default)
#define OLED_RST -1    // Reset pin (-1 = unused)
#define DHTPIN 4       // DHT sensor data pin
#define DHTTYPE DHT22  // Sensor type (DHT22/AM2302)

// OLED display parameters
#define SCREEN_WIDTH 128  // OLED width in pixels
#define SCREEN_HEIGHT 64  // OLED height in pixels

// Initialize hardware objects
Adafruit_SSD1306 oled(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RST);
DHT dht(DHTPIN, DHTTYPE);

void setup() {
  Serial.begin(115200);  // Start serial communication at 115200 baud
  dht.begin();           // Initialize DHT sensor

  // Configure I²C communication for OLED
  Wire.begin(OLED_SDA, OLED_SCL);

  // Initialize OLED display
  if (!oled.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {  // 0x3C = I²C address
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
  // Read sensor data (250ms sampling time required)
  float humidity = dht.readHumidity();  // Relative humidity (%)
  float tempC = dht.readTemperature();  // Temperature in °C
                                        
  // Validate sensor readings
  if (isnan(humidity) || isnan(tempC)) {
    Serial.println(F("DHT read error!"));
    return;  // Skip failed cycle
  }

  // Calculate heat index (perceived temperature)
  float heatIndexC = dht.computeHeatIndex(tempC, humidity, false);

  // Serial Monitor Output
  Serial.print(F("Temp: "));
  Serial.print(tempC);
  Serial.print(F("°C "));
  Serial.print(F("HeatIdx: "));
  Serial.print(heatIndexC);
  Serial.print(F("°C "));
  Serial.print(F("Humidity: "));
  Serial.print(humidity);
  Serial.println(F("%"));

  // OLED Display Routine
  oled.clearDisplay();
  oled.setCursor(0, 0);

  // Display formatted data
  oled.print(F("Temp: "));
  oled.print(tempC);
  oled.write(247);
  oled.println(F("C"));
  oled.print(F("HeatIdx: "));
  oled.print(heatIndexC);
  oled.write(247);
  oled.println(F("C"));
  oled.print(F("Humidity: "));
  oled.print(humidity);
  oled.println(F("%"));
  oled.display();

  delay(2000);  // Sampling interval (match sensor limitations)
}