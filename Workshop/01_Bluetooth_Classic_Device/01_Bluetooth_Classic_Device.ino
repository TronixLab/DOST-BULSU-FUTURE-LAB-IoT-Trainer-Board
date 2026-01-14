#include "BluetoothSerial.h"

// Check if Bluetooth is available
#if !defined(CONFIG_BT_ENABLED) || !defined(CONFIG_BLUEDROID_ENABLED)
#error Bluetooth is not enabled! Please run `make menuconfig` to and enable it
#endif

// Check Serial Port Profile
#if !defined(CONFIG_BT_SPP_ENABLED)
#error Serial Port Profile for Bluetooth is not available or not enabled. It is only available for the ESP32 chip.
#endif

BluetoothSerial SerialBT;

// Define global variables
const String DEVICE_NAME = "ESP32 Bluetooth Serial";  // Device name
String rcvString;                                     // Hold receive string from Bluetooth App
bool recordString = false;                            // Record receive string flag status
bool SerialBTWasConnected = false;                    // Serial Bluetooth flag status

// Serial Bluetooth callback function
void SerialBTStatusCallBacks(esp_spp_cb_event_t event, esp_spp_cb_param_t* param) {
  if (event == ESP_SPP_SRV_OPEN_EVT) {
    Serial.println("[SerialBT callback] Client Connected.");
    SerialBTWasConnected = false;
  } else if (event == ESP_SPP_CLOSE_EVT) {
    Serial.println("[SerialBT callback] Client Disconnected!");
    SerialBTWasConnected = true;
  }
}

void setup() {
  Serial.begin(115200);

  // Register Serial Bluetooth callback function
  SerialBT.register_callback(SerialBTStatusCallBacks);

  // Initialize Serial Bluetooth Device
  SerialBT.begin(DEVICE_NAME);
  Serial.printf("[esp] \"%s\" is started.\nNow you can connect it with Bluetooth App.\n", DEVICE_NAME.c_str());
}

void loop() {
  // Write Serial packet from Arduino serial monitor to Bluetooth App
  if (Serial.available()) {
    SerialBT.write(Serial.read());
  }

  while (SerialBT.available()) {
    // Receive character data from Bluetooth Serial
    char rcvChar = (char)SerialBT.read();

    // Check if the current character is our start marker
    if (rcvChar == '*') {
      recordString = true;
      continue;
    }

    // Append characters to create a String
    if (recordString) {
      rcvString += rcvChar;
    }
  }

  if (rcvString.length() > 0) {
    // Print data on Serial Monitor
    Serial.print("[esp] Received Serial BT string: ");
    Serial.print(rcvString);
    Serial.print(", number of characters: ");
    Serial.println(rcvString.length());

    // Check if App's button control is pressed
    if (rcvString.equals("B1")) {
      Serial.println("[app] Button B1 was pressed.");
    } else if (rcvString.equals("B2")) {
      Serial.println("[app] Button B2 was pressed.");
    } else if (rcvString.equals("B3")) {
      Serial.println("[app] Button B3 was pressed.");
    } else if (rcvString.equals("B4")) {
      Serial.println("[app] Button B4 was pressed.");
    } else if (rcvString.equals("B5")) {
      Serial.println("[app] Button B5 was pressed.");
    } else if (rcvString.equals("B6")) {
      Serial.println("[app] Button B6 was pressed.");
    }

    // Check if App's switch control is toggled
    if (rcvString.equals("SW1-1")) {
      Serial.println("[app] Switch SW1 toggled to TRUE.");
    } else if (rcvString.equals("SW1-0")) {
      Serial.println("[app] Switch SW1 toggled to FALSE.");
    } else if (rcvString.equals("SW2-1")) {
      Serial.println("[app] Switch SW2 toggled to TRUE.");
    } else if (rcvString.equals("SW2-0")) {
      Serial.println("[app] Switch SW2 toggled to FALSE.");
    } else if (rcvString.equals("SW3-1")) {
      Serial.println("[app] Switch SW3 toggled to TRUE.");
    } else if (rcvString.equals("SW3-0")) {
      Serial.println("[app] Switch SW3 toggled to FALSE.");
    } else if (rcvString.equals("SW4-1")) {
      Serial.println("[app] Switch SW4 toggled to TRUE.");
    } else if (rcvString.equals("SW4-0")) {
      Serial.println("[app] Switch SW4 toggled to FALSE.");
    }

    // Clear the previous string data for new readings
    rcvString = "";
  }

  if (SerialBTWasConnected) {
    // After a disconnect, we cannot reconnect to any device.
    // Crude solution: Manually restart the BT functionality upon a disconnection.
    SerialBT.end();
    delay(500);

    // Re-register Serial Bluetooth callback function
    SerialBT.register_callback(SerialBTStatusCallBacks);

    // Re-initialize Serial Bluetooth Device
    SerialBT.begin(DEVICE_NAME);
    Serial.printf("[esp] \"%s\" is restarted.\nNow you can reconnect it with Bluetooth App.\n", DEVICE_NAME.c_str());

    // Reset Serial Bluetooth connection flag value
    SerialBTWasConnected = false;
  }
}