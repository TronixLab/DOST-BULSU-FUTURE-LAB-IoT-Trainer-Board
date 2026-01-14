#include <WiFi.h>

// Create Wi-Fi client object
WiFiClient client;

// Defines the SSID and password of the Wi-Fi network
const char* SSID = "PipoyT11";
const char* PASSWORD = "data032722";

const int HTTP_PORT = 80;                           // Server port
const char* HTTP_METHOD = "GET ";                   // HTTP request method (e.g., POST)
const char* HOST = "jsonplaceholder.typicode.com";  // Domain of the server
const String URL_PATH = "/posts";                   // Contains content path location from server
const String URL_QUERY = "?userId=1";               // Contains parameters of the content to be request

void setup() {
  Serial.begin(115200);

  // Set ESP32 WiFi to station mode
  WiFi.mode(WIFI_STA);

  // Initiate the Wi-Fi connection
  WiFi.begin(SSID, PASSWORD);

  Serial.print("Connecting...");
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(100);
  }

  // Print some information of the Wi-Fi network
  Serial.print("\nConnected to the ");
  Serial.println((String)WiFi.SSID() + " network");
  Serial.print("[*] RSSI: ");
  Serial.println((String)WiFi.RSSI() + " dB");
  Serial.print("[*] ESP32 IP: ");
  Serial.println(WiFi.localIP());
  Serial.println();
}

void loop() {
  Serial.print("Connecting to ");
  Serial.println(HOST);

  // Create TCP (Transmission Control Protocol) connections
  if (!client.connect(HOST, HTTP_PORT)) {
    Serial.println("Connection failed");
    return;
  }

  // Send HTTP request header
  client.print(HTTP_METHOD + URL_PATH + URL_QUERY + " HTTP/1.1\r\n" + "Host: " + HOST + "\r\n" + "Connection: close\r\n\r\n");

  // Check connection if reach timeout (five seconds)
  unsigned long timeout = millis();
  while (client.available() == 0) {
    if (millis() - timeout > 5000) {
      Serial.println(">>> Client Timeout !");
      client.stop();
      return;
    }
  }

  // Read response from server and print them to Serial monitor
  while (client.available()) {
    char response = client.read();
    Serial.print(response);
  }

  // Wait for 10-seconds for another HTTP GET request
  delay(10000);
}
