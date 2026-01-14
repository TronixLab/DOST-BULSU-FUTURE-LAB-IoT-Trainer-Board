#include <ArduinoJson.h>

// Create JSON object named doc
JsonDocument doc;

void setup() {
  Serial.begin(115200);
}

void loop() {
  // Input JSON string
  const char* jsondoc = "{\"Device ID\":\"1089664092\",\"Device Name\":\"ESP-EnviSense_001\",\"Location\":\"Greenhouse\",\"Description\":\"Monitoring temperature and humidity\",\"Sensors\":{\"Timestamp\":\"2024-07-9 18:04:07\",\"Temperature\":27.81,\"Humidity\":83}}";

  // Deserialize the JSON document
  DeserializationError error = deserializeJson(doc, jsondoc);

  // Test if parsing succeeds
  if (error) {
    Serial.print(F("deserializeJson() failed: "));
    Serial.println(error.f_str());
    return;
  }

  // Extracting values
  unsigned long int deviceId = doc["Device ID"].as<unsigned long int>();
  auto deviceName = doc["Device Name"].as<const char*>();
  auto location = doc["Location"].as<const char*>();
  auto description = doc["Description"].as<const char*>();
  auto timeStamp = doc["Sensors"]["Timestamp"].as<const char*>();
  float temperature = doc["Sensors"]["Temperature"].as<float>();
  int humidity = doc["Sensors"]["Humidity"].as<int>();

  // Print values.
  Serial.printf("Device ID: %lu, Device Name: %s, Location: %s, Description: %s, Timestamp: %s, Temperature: %.2f, Humidity: %d \n", deviceId, deviceName, location, description, timeStamp, temperature, humidity);

  delay(5000);
}