/************************************************
Arduino Library
- DFRobot_BMP280
- v1.0.1
- Authors: DFRobot
- Reference: https://github.com/DFRobot/DFRobot_BMP280
************************************************/
#include <DFRobot_BMP280.h>
#include <Wire.h>

#define DEBUG 1
#if DEBUG == 1
#define debug(x) Serial.print(x);
#define debugln(x) Serial.println(x);
#else
#define debug(x)
#define debugln(x)
#endif

typedef DFRobot_BMP280_IIC BMP;
BMP bmp280(&Wire, BMP::eSdoLow);

#define SEA_LEVEL_PRESSURE_hPa 1013.25f

void setup() {
  Serial.begin(9600);

  bmp280.reset();
  while (bmp280.begin() != BMP::eStatusOK) {
    debug(F("[debug] BMP280 initialization failed!"));
    printLastOperateStatus(bmp280.lastOperateStatus);
    delay(2000);
  }
  debug(F("[debug] BMP280 initialization success."));
  delay(100);
}

void loop() {
  float temp = bmp280.getTemperature();
  uint32_t press = bmp280.getPressure();
  float alti = bmp280.calAltitude(SEA_LEVEL_PRESSURE_hPa, press);

  debug(F("[debug] Temperature: "));
  debug(temp);
  debug(F("°C   Pressure: "));
  debug(press);
  debug(F("Pa   Altitude: "));
  debug(alti);
  debugln(F("m"));
  delay(1000);
}

void printLastOperateStatus(BMP::eStatus_t eStatus) {
  switch (eStatus) {
    case BMP::eStatusOK: Serial.println("everything ok"); break;
    case BMP::eStatusErr: Serial.println("unknow error"); break;
    case BMP::eStatusErrDeviceNotDetected: Serial.println("device not detected"); break;
    case BMP::eStatusErrParameter: Serial.println("parameter error"); break;
    default: Serial.println("unknow status"); break;
  }
}