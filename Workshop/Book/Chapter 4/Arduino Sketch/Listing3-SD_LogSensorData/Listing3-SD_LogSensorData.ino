// Libraries for SD card
#include "FS.h"
#include "SD.h"
#include "SPI.h"

// Defined SD card SPI pins
#define SD_CS 13
#define SD_MOSI 15
#define SD_MISO 2
#define SD_CLK 14

// Define LoRa SPI chip select pin
#define LoRa_CS 18

// Timer variables
unsigned long lastTime = 0;
unsigned long timerDelay = 5000;

// Variables to hold sensor readings
unsigned long epochTime;
float tempC;
float hum;
float hi;
float light;
String sensorData;

// Initialize SD card
void initSDCard() {
  // Initialize SPI chip select pins
  pinMode(SD_CS, OUTPUT);
  pinMode(LoRa_CS, OUTPUT);

  // Select (LOW) SD card module peripheral
  // Deselect (HIGH) LoRa module
  digitalWrite(LoRa_CS, HIGH);
  digitalWrite(SD_CS, LOW);

  // Initialize SD card module
  SPI.begin(SD_CLK, SD_MISO, SD_MOSI, SD_CS);
  if (!SD.begin()) {
    Serial.println("Card Mount Failed");
    return;
  }

  // Detect card type
  uint8_t cardType = SD.cardType();
  if (cardType == CARD_NONE) {
    Serial.println("No SD card attached");
    return;
  }

  Serial.print("SD Card Type: ");
  if (cardType == CARD_MMC) {
    Serial.println("MMC");
  } else if (cardType == CARD_SD) {
    Serial.println("SDSC");
  } else if (cardType == CARD_SDHC) {
    Serial.println("SDHC");
  } else {
    Serial.println("UNKNOWN");
  }

  // Print card memory status
  uint64_t cardSize = SD.cardSize() / (1024 * 1024);
  Serial.printf("SD Card Size: %lluMB\n", cardSize);
  Serial.printf("Total space: %lluMB\n", SD.totalBytes() / (1024 * 1024));
  Serial.printf("Used space: %lluMB\n", SD.usedBytes() / (1024 * 1024));
}

// Write to the SD card
void writeFile(fs::FS &fs, const char *path, const char *message) {
  Serial.printf("Writing file: %s\n", path);

  File file = fs.open(path, FILE_WRITE);
  if (!file) {
    Serial.println("Failed to open file for writing");
    return;
  }
  if (file.print(message)) {
    Serial.println("File written");
  } else {
    Serial.println("Write failed");
  }
  file.close();
}

// Append data to the SD card
void appendFile(fs::FS &fs, const char *path, const char *message) {
  Serial.printf("Appending to file: %s\n", path);

  File file = fs.open(path, FILE_APPEND);
  if (!file) {
    Serial.println("Failed to open file for appending");
    return;
  }
  if (file.print(message)) {
    Serial.println("Message appended");
  } else {
    Serial.println("Append failed");
  }
  file.close();
}

void setup() {
  Serial.begin(115200);

  // Initialized SD card
  initSDCard();

  // If the data.txt file doesn't exist
  // Create a file on the SD card and write the data labels
  File file = SD.open("/data.txt");
  if (!file) {
    Serial.println("File doesn't exist");
    Serial.println("Creating file...");
    writeFile(SD, "/data.txt", "Epoch Time, Temperature, Humidity, Heat Index, Light \r\n");
  } else {
    Serial.println("File already exists");
  }
  file.close();
}

void loop() {
  if ((millis() - lastTime) > timerDelay) {
    lastTime = millis();

    epochTime = millis() / 1000;
    tempC = random(2000.00, 5000.00) / 100.00;
    hum = random(8000.00, 10000.00) / 100.00;
    hi = random(2700, 3200) / 100.00;
    light = random(32000, 50000) / 100.00;

    sensorData = String(epochTime) + "," + String(tempC) + "," + String(hum) + "," + String(hi) + "," + String(light) + "\r\n";
    Serial.print("Saving data: ");
    Serial.println(sensorData);

    // Append the data to file
    appendFile(SD, "/data.txt", sensorData.c_str());
  }
}
