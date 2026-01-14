#include <WiFi.h>
#include <PubSubClient.h>
#include <WiFiClientSecure.h>

// Wi-Fi network credentials
const char* wifi_ssid = "REPLACE_WITH_WIFI_SSID";
const char* wifi_auth = "REPLACE_WITH_WIFI_PASSWORD";

// Mosquito MQTT connection settings
#define mqtt_name "AdafruitIO"
#define mqtt_host "io.adafruit.com"
#define mqtt_port 8883
#define mqtt_username "ray_aray57"
#define mqtt_password "aio_imnp25KWG1LUWbaJlLMsg3I3Pngx"
#define mqtt_topic "ray_aray57/f/kitchen-temperature"
#define mqtt_QoS 0
#define mqtt_retain true
#define mqtt_timeout 10000

// Create WiFi and MQTT client objects
WiFiClientSecure wifi_client;
PubSubClient mqtt_client(wifi_client);

// Timer for tracking the last connection attempt
unsigned long int mqtt_last_connection_time_ms = 0;

// MQTT callback function that executes upon receiving a subscribed message
void mqtt_client_cb(char* topic, byte* payload, unsigned int length) {
  Serial.print("[MQTT] Subscribe message: [ topic: ");
  Serial.print(topic);
  Serial.print(", payload: ");
  for (int i = 0; i < length; i++) {
    Serial.print((char)payload[i]);
  }
  Serial.print(", size: ");
  Serial.print(length);
  Serial.println(" ]");
}

// Function to print the connection status to MQTT broker
void mqtt_connection_status() {
  switch (mqtt_client.state()) {
    case -4:
      // the server didn't respond within the keepalive time
      Serial.println("[MQTT] MQTT_CONNECTION_TIMEOUT");
      break;
    case -3:
      // the network connection was broken
      Serial.println("[MQTT] MQTT_CONNECTION_LOST");
      break;
    case -2:
      // the network connection failed
      Serial.println("[MQTT] MQTT_CONNECT_FAILED");
      break;
    case -1:
      // the client is disconnected cleanly
      Serial.println("[MQTT] MQTT_DISCONNECTED");
      break;
    case 0:
      // the client is connected
      Serial.println("[MQTT] MQTT_CONNECTED");
      break;
    case 1:
      // the server doesn't support the requested version of MQTT
      Serial.println("[MQTT] MQTT_CONNECT_BAD_PROTOCOL");
      break;
    case 2:
      // the server rejected the client identifier
      Serial.println("[MQTT] MQTT_CONNECT_BAD_CLIENT_ID");
      break;
    case 3:
      // the server was unable to accept the connection
      Serial.println("[MQTT] MQTT_CONNECT_UNAVAILABLE");
      break;
    case 4:
      // the username/password were rejected
      Serial.println("MQTT_CONNECT_BAD_CREDENTIALS");
      break;
    case 5:
      // the client was not authorized to connect
      Serial.println("[MQTT] MQTT_CONNECT_UNAUTHORIZED");
      break;
  }
}

void setup() {
  // Initialize serial monitor with baud rate 115200
  Serial.begin(115200);

  // Set ESP32 WiFi to station mode
  WiFi.mode(WIFI_STA);

  // Initiate the Wi-Fi connection
  WiFi.begin(wifi_ssid, wifi_auth);
  Serial.println("[WIFI] Connecting to WiFi Network...");

  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(100);
  }

  Serial.println("");
  Serial.print("[WIFI] Connected to the Wi-Fi network with local IP: ");
  Serial.println(WiFi.localIP());

  // Allows for 'insecure' connections. It turns off CA certificate checking
  wifi_client.setInsecure();

  // Configure MQTT server and callback function
  mqtt_client.setServer(mqtt_host, mqtt_port);
  mqtt_client.setCallback(mqtt_client_cb);

  // Check MQTT broker connection status
  while (!mqtt_client.connected()) {
    // Connect to MQTT broker
    Serial.print("[MQTT] Connecting to MQTT broker...");
    if (mqtt_client.connect(mqtt_name, mqtt_username, mqtt_password)) {
      Serial.println("connection succeeded.");
    } else {
      Serial.println("connection failed!");
    }
    // Print MQTT connection status
    mqtt_connection_status();
  }
  // Subscribe to the topic only once
  mqtt_client.subscribe(mqtt_topic, mqtt_QoS);
}

void loop() {
  // Check MQTT connection status
  if (!mqtt_client.connected()) {
    if (millis() - mqtt_last_connection_time_ms > mqtt_timeout) {
      mqtt_last_connection_time_ms = millis();
      // Print MQTT connection status
      mqtt_connection_status();
      // Attempt to reconnect
      Serial.print("[MQTT] Reconnecting to MQTT broker...");
      if (mqtt_client.connect(mqtt_name, mqtt_username, mqtt_password)) {
        Serial.println("connection succeeded.");
        // Reset timer after successful reconnection
        mqtt_last_connection_time_ms = 0;
        // Re-subscribe to a topic upon reconnection
        mqtt_client.subscribe(mqtt_topic, mqtt_QoS);
      } else {
        Serial.println("connection failed!");
      }
      // Print MQTT connection status
      mqtt_connection_status();
    }
  } else {
    // Publish temperature data every 10 seconds
    static unsigned long int timer = millis();
    if (millis() - timer >= 10000) {
      timer = millis();

      // Simulate random temperature readings ranges from 20°C - 40°C
      float temperature = random(2000, 4000) / 100.00;

      // Buffer the temperature data as message in JSON format
      const int payload_size = 50;
      char mqtt_payload[payload_size];
      snprintf(mqtt_payload, payload_size, "{\"value\": %.2f}", temperature);

      // Publish message to topic
      mqtt_client.publish(mqtt_topic, mqtt_payload, mqtt_retain);

      // Print the message / payload
      Serial.printf("[MQTT] Publish message: %s \n", mqtt_payload);
    }
    // Handle MQTT client tasks like receiving messages
    mqtt_client.loop();
  }
}
