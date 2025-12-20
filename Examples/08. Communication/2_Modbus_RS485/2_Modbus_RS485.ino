/********************************************************************************************
  Wiring of Sensor, ESP32, and MAX485 TTL to RS485 Converter:
  ___________________________________________________________________________________________
  | Sensor (SHT20)   |   MAX485 TTL to RS485 Converter
  |   A (Yellow)     |        A (Terminal block)
  |   B (White)      |        B (Terminal block)
  | GND (Black)      |      GND (External Supply)
  |  Vs (Red)        |    5-30V (External Supply)
  ___________________________________________________________________________________________
  | MAX485 TTL to RS485 Converter  |  ESP32  (Hardware Serial)   
  |     TXD (Reciever Output)      |        IO13 (RX1)                    
  |     RXD (Driver Input)         |        IO15 (TX1)                   
  ___________________________________________________________________________________________
  Reference: https://github.com/TronixLab/ModBus-RTU-Temperature-Humidity-SHT20-Sensor
  Arduino Library
- ModbusMaster
- v2.0.1
- Authors: Doc Walker
- Reference: https://github.com/4-20ma/ModbusMaster
*********************************************************************************************/
#include <ModbusMaster.h>

#define DEBUG 1
#if DEBUG == 1
#define debug(x) Serial.print(x);
#define debugln(x) Serial.println(x);
#else
#define debug(x)
#define debugln(x)
#endif

#define TXD 13
#define RXD 15

ModbusMaster modebusRS485;

void setup() {
  // Initialize control pins
  pinMode(MAX485_RE_NEG, OUTPUT);
  pinMode(MAX485_DE, OUTPUT);
  digitalWrite(MAX485_RE_NEG, 0);
  digitalWrite(MAX485_DE, 0);

  // Modbus communication runs at 9600 baud
  Serial.begin(9600);
  Serial1.begin(9600, SERIAL_8N1, TXD, RXD);

  // Modbus slave ID 1
  modebusRS485.begin(1, Serial1);
}

void loop() {
  // Request 2 registers starting at 0x0001
  uint8_t result = modebusRS485.readInputRegisters(0x0001, 2);
  debugln(F("[debug] Requesting sensor data..."));

  if (result == modebusRS485.ku8MBSuccess) {
    // Get response data from sensor
    debug(F("[debug] Temperature: "));
    debug(float(modebusRS485.getResponseBuffer(0) / 10.00F));
    debug("°C,   Humidity: ");
    debug(float(modebusRS485.getResponseBuffer(1) / 10.00F));
    debugln(F("%"));
  }
  delay(1000);
}