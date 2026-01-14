#include <BLEDevice.h>
#include <BLEUtils.h>
#include <BLEServer.h>
#include <BLE2902.h>

// Define BLE device name
#define BLE_DEVICE_NAME "ESP32_SIMPLE_BLE_DEVICE"

// See the following for generating UUIDs:
// https://www.uuidgenerator.net/
// Assigned GATT Profile UUID
#define SERVICE_UUID "4fafc201-1fb5-459e-8fcc-c5c9c331914b"
#define CHARACTERISTIC_TX_UUID "beb5483e-36e1-4688-b7f5-ea07361b26a8"
#define CHARACTERISTIC_RX_UUID "d9b09f58-e17e-4f3b-9d90-06b2e9c05fd8"

// Declare BLE GATT profile object as global variable
BLEServer *pServer;
BLEService *pService;
BLECharacteristic *pRxCharacteristic;
BLECharacteristic *pTxCharacteristic;

// Connection status flag variables
bool deviceConnected = false;
bool oldDeviceConnected = false;

// BLE callback functions
class MyServerCallbacks : public BLEServerCallbacks {
  void onConnect(BLEServer *pServer) {
    deviceConnected = true;
    Serial.println("*****************************************");
    Serial.println("[ble] Connection Status: Device Connected.");
    Serial.println("*****************************************");
  };

  void onDisconnect(BLEServer *pServer) {
    deviceConnected = false;
    Serial.println("*****************************************");
    Serial.println("[ble] Connection Status: Device Disconnected!!!");
    Serial.println("*****************************************");
  }
};

class MyCharacteristicCallbacks : public BLECharacteristicCallbacks {
  void onWrite(BLECharacteristic *pCharacteristic) {
    String value = pCharacteristic->getValue();
    if (value.length() > 0) {
      Serial.println("*****************************************");
      Serial.print("[ble] Received value: ");
      for (int i = 0; i < value.length() - 1; i++) {
        Serial.print(value[i]);
      }
      Serial.println();
      Serial.println("*****************************************");
    }
  }
};

void setup() {
  Serial.begin(115200);

  // Initiate BLE device and creat user custom name
  BLEDevice::init(BLE_DEVICE_NAME);

  // Create BLE server object
  BLEServer *pServer = BLEDevice::createServer();

  // Add service profile to server
  BLEService *pService = pServer->createService(SERVICE_UUID);

  // Add characteristic to service profile
  pRxCharacteristic = pService->createCharacteristic(
    CHARACTERISTIC_RX_UUID,
    BLECharacteristic::PROPERTY_READ | BLECharacteristic::PROPERTY_NOTIFY | BLECharacteristic::PROPERTY_INDICATE);

  pTxCharacteristic = pService->createCharacteristic(
    CHARACTERISTIC_TX_UUID,
    BLECharacteristic::PROPERTY_READ | BLECharacteristic::PROPERTY_WRITE);

  // Add Callback functions
  pServer->setCallbacks(new MyServerCallbacks());
  pTxCharacteristic->setCallbacks(new MyCharacteristicCallbacks());

  // Add BLE descriptor
  pRxCharacteristic->addDescriptor(new BLE2902());

  // Start GATT service to discover by Client device
  pService->start();

  // Start Advertising to scan by Client device
  BLEAdvertising *pAdvertising = pServer->getAdvertising();
  pAdvertising->start();
  Serial.println("[esp] Start advertising........");
}

void loop() {
  static unsigned long timer = millis();
  // Notify changed value
  if (deviceConnected) {
    // Assigned random values
    int randIntVal = random(120, 130);

    // Update GATT characteristic value every 5 seconds
    if (millis() - timer > 5000) {
      timer = millis();
      // Update GATT characteristic value
      pRxCharacteristic->setValue(String(randIntVal).c_str());
      pRxCharacteristic->notify();
    }
  }

  // Disconnecting
  if (!deviceConnected && oldDeviceConnected) {
    delay(500);
    pServer->startAdvertising();
    Serial.println("[esp] Start advertising........");
    oldDeviceConnected = deviceConnected;
  }

  // Connecting
  if (deviceConnected && !oldDeviceConnected) {
    oldDeviceConnected = deviceConnected;
  }
}