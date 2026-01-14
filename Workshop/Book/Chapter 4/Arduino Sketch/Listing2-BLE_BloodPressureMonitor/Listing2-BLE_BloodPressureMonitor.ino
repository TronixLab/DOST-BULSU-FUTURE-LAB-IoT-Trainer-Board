#include <BLEDevice.h>
#include <BLEUtils.h>
#include <BLEServer.h>
#include <BLE2902.h>

// Define BLE device name
#define BLE_DEVICE_NAME "SMART BLOOD PRESSURE MONITOR"

// Assigned official 16-bit GATT Profile UUID
#define BLOOD_PRESSURE_SERVICE_UUID BLEUUID((uint16_t)0x1810)
#define BLOOD_PRESSURE_MEAS_CHARACTERISTIC_UUID "0000dfb1-0000-1000-8000-00805f9b34fb" // BLEUUID((uint16_t)0x2A35)
#define CUFF_PRESSURE_MEAS_CHARACTERISTIC_UUID BLEUUID((uint16_t)0x2A36)

// Declare BLE GATT profile object as global variable
BLEServer *pServer;
BLEService *pBloodPressureService;
BLECharacteristic *pBloodPressureMeasCharacteristic;
BLECharacteristic *pCuffPressureMeasCharacteristic;

// Connection status flag
bool deviceConnected = false;
bool oldDeviceConnected = false;

class MyServerCallbacks : public BLEServerCallbacks {
  void onConnect(BLEServer *pServer) {
    deviceConnected = true;
  };

  void onDisconnect(BLEServer *pServer) {
    deviceConnected = false;
  }
};

void setup() {
  // Initiate BLE device and creat user custom name
  BLEDevice::init(BLE_DEVICE_NAME);

  // Create BLE server object
  pServer = BLEDevice::createServer();
  pServer->setCallbacks(new MyServerCallbacks());

  // Add blood pressure service to server
  pBloodPressureService = pServer->createService(BLOOD_PRESSURE_SERVICE_UUID);

  // Add characteristics to blood pressure service
  pBloodPressureMeasCharacteristic = pBloodPressureService->createCharacteristic(
    BLOOD_PRESSURE_MEAS_CHARACTERISTIC_UUID,
    BLECharacteristic::PROPERTY_READ | BLECharacteristic::PROPERTY_NOTIFY | BLECharacteristic::PROPERTY_INDICATE);

  pCuffPressureMeasCharacteristic = pBloodPressureService->createCharacteristic(
    CUFF_PRESSURE_MEAS_CHARACTERISTIC_UUID,
    BLECharacteristic::PROPERTY_READ | BLECharacteristic::PROPERTY_NOTIFY | BLECharacteristic::PROPERTY_INDICATE);

  // Add BLE descriptor
  pBloodPressureMeasCharacteristic->addDescriptor(new BLE2902());
  pCuffPressureMeasCharacteristic->addDescriptor(new BLE2902());

  // Start GATT service to discover by Client device
  pBloodPressureService->start();

  // Start Advertising to scan by Client device
  BLEAdvertising *pAdvertising = BLEDevice::getAdvertising();
  pAdvertising->addServiceUUID(BLOOD_PRESSURE_SERVICE_UUID);
  pAdvertising->setScanResponse(false);
  pAdvertising->setMinPreferred(0x0);
  BLEDevice::startAdvertising();
}

void loop() {
  // notify changed value
  if (deviceConnected) {
    // Assigned random values for systolic blood pressure measurement
    int SBP = random(120, 130);

    // Assigned random values for endotracheal tube cuff pressure measurement
    int ETCP = random(20, 30);

    // Update characteristic value
    pBloodPressureMeasCharacteristic->setValue(String(SBP).c_str());
    pBloodPressureMeasCharacteristic->notify();

    pCuffPressureMeasCharacteristic->setValue(String(ETCP).c_str());
    pCuffPressureMeasCharacteristic->notify();
    delay(500);
  }
  // disconnecting
  if (!deviceConnected && oldDeviceConnected) {
    delay(500);                   // give the bluetooth stack the chance to get things ready
    pServer->startAdvertising();  // restart advertising
    Serial.println("start advertising");
    oldDeviceConnected = deviceConnected;
  }
  // connecting
  if (deviceConnected && !oldDeviceConnected) {
    // do stuff here on connecting
    oldDeviceConnected = deviceConnected;
  }
}
