#include "BluetoothSerial.h"

#if !defined(CONFIG_BT_ENABLED) || !defined(CONFIG_BLUEDROID_ENABLED)
#error Bluetooth is not enabled! Please run `make menuconfig` to and enable it
#endif

#if !defined(CONFIG_BT_SPP_ENABLED)
#error Serial Bluetooth not available or not enabled. It is only available for the ESP32 chip.
#endif

// Create object for Bluetooth classic
BluetoothSerial SerialBT;

// Create string variables
String device_name = "MyBT-ESP32";
String rcvData;

void setup() {
  Serial.begin(115200);
  // Create Bluetooth device name
  // If not set; default is ESP32
  SerialBT.begin(device_name);

  // Initialize digital pin LED_BUILTIN as an output.
  pinMode(LED_BUILTIN, OUTPUT);

  Serial.println("The device started, you can now pair it with Bluetooth.");
}

void loop() {
  // Check if Bluetooth serial data is available
  while (SerialBT.available()) {
    // Receive character data from Bluetooth Serial
    char rcvChar = SerialBT.read();

    // Print ASCII code character map
    Serial.write(rcvChar);
    Serial.print(", DEC: ");
    Serial.print(rcvChar, DEC);
    Serial.print(", HEX: ");
    Serial.print(rcvChar, HEX);
    Serial.print(", OCT: ");
    Serial.print(rcvChar, OCT);
    Serial.print(", BIN: ");
    Serial.print(rcvChar, BIN);
    Serial.print('\n');
    Serial.println("------------------------------------------------");

    // Convert character array data into String format
    rcvData += rcvChar;
  }

  if (rcvData.length() > 0) {
    // Print data on Serial Monitor
    Serial.print("Received BT data: ");
    Serial.print(rcvData);
    Serial.print(", number of characters: ");
    Serial.println(rcvData.length());

    // Convert valid string value to an integer
    int ledState = rcvData.toInt();

    // Control the built-in LED using '1' or '0' values
    if (ledState == 1) {
      digitalWrite(LED_BUILTIN, HIGH);
    }
    if (ledState == 0) {
      digitalWrite(LED_BUILTIN, LOW);
    }

    // Control the built-in LED using "ON" or "OFF" values
    if (rcvData.equals("ON\r\n")) {
      digitalWrite(LED_BUILTIN, HIGH);
    }
    if (rcvData.equals("OFF\r\n")) {
      digitalWrite(LED_BUILTIN, LOW);
    }

    // Clear the previous string data for new readings
    rcvData = "";
  }
  delay(10);
}
