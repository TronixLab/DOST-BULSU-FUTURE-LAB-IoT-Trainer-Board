#include <WiFi.h>
#include <WiFiClientSecure.h>
#include <ArduinoJson.h>
#include <time.h>
#include <esp_sntp.h>

// Create Wi-Fi client secure object for Firebase GET/PATCH HTTP request
WiFiClientSecure FirebaseGetRequest;
WiFiClientSecure FirebasePatchRequest;

// Create JSON object named doc
JsonDocument doc;

// Wi-Fi credentials
const char* SSID = "REPLACE_WITH_WIFI_SSID";
const char* PASSWORD = "REPLACE_WITH_WIFI_PASSWORD";

// Firebase Database Credentials
const int SSL_PORT = 443;
const char* FIREBASE_HOST = "<your-database-project-name>.<database-server>.firebasedatabase.app";
const String FIREBASE_AUTH = "<your-firebase-database-secret-key>";
const String FIREBASE_PATH = "/";

// Define the NTP servers and parameters settings
#define NTP_SERVER_1 "pool.ntp.org"
#define NTP_SERVER_2 "asia.pool.ntp.org"
#define TIME_ZONE "PHT"
#define GMT_OFFSET_S 28800ULL
#define DAYLIGHT_OFFSET_S 0ULL

// Define variable that store local time info
struct tm timeinfo;

void setup() {
  Serial.begin(115200);

  // Initialize network time protocol (NTP) configurations
  sntp_set_time_sync_notification_cb(timeavailable);
  sntp_servermode_dhcp(1);
  configTime(GMT_OFFSET_S, DAYLIGHT_OFFSET_S, NTP_SERVER_1, NTP_SERVER_2);

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

  // Allows for 'insecure' connections. It turns off CA certificate checking
  FirebaseGetRequest.setInsecure();
  FirebasePatchRequest.setInsecure();

  // Initialize HTTP GET request once
  FirebaseGetRequestBegin(FIREBASE_PATH);

  // Loop until the current local time is obtained
  Serial.print("[NTP] Waiting for time synchronization...");
  while (!getLocalTime(&timeinfo)) {
    Serial.print(".");
  }
}

void loop() {
  // Get the payload form Firebase Database
  FirebaseGetPayload();

  // Create Key-Value pairs inside the JSON object
  doc["Sensors"]["Timestamp"] = getLocalTime();
  doc["Sensors"]["Temperature"] = random(2000, 3000) / 100.00;
  doc["Sensors"]["Humidity"] = random(70, 100);

  // Generate simple JSON data structure
  String firebasePayload;
  serializeJson(doc, firebasePayload);

  // Updata data to Firebase Database
  FirebaseUpdateDB(firebasePayload);
}

void FirebaseGetRequestBegin(String url_path) {
  // Create TLS (Transport Layer Security) connections
  if (!FirebaseGetRequest.connect(FIREBASE_HOST, SSL_PORT)) {
    return;
  }

  // Create HTTPS URL
  String HTTP_PARAM_URL = url_path + ".json?auth=" + FIREBASE_AUTH;

  // Send HTTP request header
  FirebaseGetRequest.println("GET " + HTTP_PARAM_URL + " HTTP/1.1");
  FirebaseGetRequest.println("Host: " + String(FIREBASE_HOST));
  FirebaseGetRequest.println("Accept: text/event-stream");
  FirebaseGetRequest.println("Connection: close");
  FirebaseGetRequest.println();
}

String FirebaseGetPayload() {
  String response;
  // Read response from server and print them to Serial monitor
  while (FirebaseGetRequest.available()) {
    response = FirebaseGetRequest.readStringUntil('\r');
    Serial.print(response);
  }
  return response;
}

void FirebaseUpdateDB(String body_content) {
  // Create TLS (Transport Layer Security) connections
  if (!FirebasePatchRequest.connect(FIREBASE_HOST, SSL_PORT)) {
    return;
  }

  // Create HTTPS URL
  String HTTP_PARAM_URL = FIREBASE_PATH + ".json?auth=" + FIREBASE_AUTH;

  // Create HTTP body in JSON (JavaScript Object Notation) format
  String HTTP_BODY = body_content;

  // Send HTTP request header
  FirebasePatchRequest.println("PATCH " + HTTP_PARAM_URL + " HTTP/1.1");
  FirebasePatchRequest.println("Host: " + String(FIREBASE_HOST));
  FirebasePatchRequest.println("Content-Type: application/json");
  FirebasePatchRequest.println("Content-Length: " + String(HTTP_BODY.length()));
  FirebasePatchRequest.println("Connection: close");
  FirebasePatchRequest.println();
  FirebasePatchRequest.println(HTTP_BODY);

  // Disconnect to Firebase before to reconnect it for new request
  FirebasePatchRequest.stop();
}

String getLocalTime() {
  // Format timestamp as yyyy-MM-dd HH:mm:ss
  String timestamp;
  if (getLocalTime(&timeinfo)) {
    timestamp = String(timeinfo.tm_year + 1900) + "-" + String(timeinfo.tm_mon + 1) + "-" + String(timeinfo.tm_mday) + "  " + String(timeinfo.tm_hour) + ":" + String(timeinfo.tm_min) + ":" + String(timeinfo.tm_sec);
  }
  return timestamp;
}

void timeavailable(struct timeval* t) {
  // Print debug time synchronization message to Serial Monitor
  Serial.println("got time adjustment from NTP!");
  getLocalTime();
}