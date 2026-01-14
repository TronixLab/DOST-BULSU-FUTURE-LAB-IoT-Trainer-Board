#include <ArduinoJson.h>

// Create JSON object named doc
JsonDocument doc;

void setup() {
  Serial.begin(115200);
}

void loop() {
  // Create Key-Value pairs inside the JSON object
  doc["Device ID"] = "1089664092";
  doc["Device Name"] = "ESP-EnviSense_001";
  doc["Location"] = "Greenhouse";
  doc["Description"] = "Monitoring temperature and humidity";
  doc["Sensors"]["Timestamp"] = "2024-07-9 18:04:07";
  doc["Sensors"]["Temperature"] = 27.81;
  doc["Sensors"]["Humidity"] = 83;

  // Generate simple JSON data structure
  String simpleJSON;
  serializeJson(doc, simpleJSON);
  Serial.println("Simple JSON Format: \n" + simpleJSON);

  // Generate prettified JSON data structure
  String prettyJSON;
  serializeJsonPretty(doc, prettyJSON);
  Serial.println("Pretty JSON Format: \n" + prettyJSON);

  delay(5000);
}
