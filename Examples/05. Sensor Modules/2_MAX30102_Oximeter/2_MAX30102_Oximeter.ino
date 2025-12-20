/************************************************
Arduino Library
- DFRobot_MAX30102 Heart-rate & Oximeter Sensor
- v0.1
- Authors: DFRobot
- Reference: https://github.com/DFRobot/DFRobot_MAX30102
************************************************/
#include <DFRobot_MAX30102.h>

#define DEBUG 1
#if DEBUG == 1
#define debug(...) Serial.print(__VA_ARGS__);
#define debugln(...) Serial.println(__VA_ARGS__);
#else
#define debug(...)
#define debugln(...)
#endif

DFRobot_MAX30102 MAX10302;

/*****************************************************************************
Macro definition options in sensor configuration
sampleAverage: SAMPLEAVG_1 SAMPLEAVG_2 SAMPLEAVG_4
               SAMPLEAVG_8 SAMPLEAVG_16 SAMPLEAVG_32
ledMode:       MODE_REDONLY  MODE_RED_IR  MODE_MULTILED
sampleRate:    PULSEWIDTH_69 PULSEWIDTH_118 PULSEWIDTH_215 PULSEWIDTH_411
pulseWidth:    SAMPLERATE_50 SAMPLERATE_100 SAMPLERATE_200 SAMPLERATE_400
               SAMPLERATE_800 SAMPLERATE_1000 SAMPLERATE_1600 SAMPLERATE_3200
adcRange:      ADCRANGE_2048 ADCRANGE_4096 ADCRANGE_8192 ADCRANGE_16384
*****************************************************************************/

int32_t SPO2;           // SPO2
int8_t SPO2Valid;       // Flag to display if SPO2 calculation is valid
int32_t heartRate;      // Heart-rate
int8_t heartRateValid;  // Flag to display if heart-rate calculation is valid

void setup() {
  Serial.begin(9600);

  while (!MAX10302.begin()) {
    debug(F("[debug] MAX30102 was not found"));
  }

  /*!
   *@brief Use macro definition to configure sensor 
   *@param ledBrightness LED brightness, default value: 0x1F（6.4mA), Range: 0~255（0=Off, 255=50mA）
   *@param sampleAverage Average multiple samples then draw once, reduce data throughput, default 4 samples average
   *@param ledMode LED mode, default to use red light and IR at the same time 
   *@param sampleRate Sampling rate, default 400 samples every second 
   *@param pulseWidth Pulse width: the longer the pulse width, the wider the detection range. Default to be Max range
   *@param adcRange ADC Measurement Range, default 4096 (nA), 15.63(pA) per LSB
   */
  MAX10302.sensorConfiguration(255,             // ledBrightness
                               SAMPLEAVG_4,     // sampleAverage
                               MODE_MULTILED,   // ledMode
                               SAMPLERATE_100,  // sampleRate
                               PULSEWIDTH_411,  // pulseWidth
                               ADCRANGE_4096    // adcRange
  );
}

void loop() {
  MAX10302.heartrateAndOxygenSaturation(&SPO2, &SPO2Valid, &heartRate, &heartRateValid);

  if (heartRateValid == 0 && SPO2Valid == 0) {
    debug(F("[debug] Reading pulse oximeter values..."));
  } else if (heartRateValid == 1 && SPO2Valid == 1) {
    debug(F("Heart Rate: "));
    debug(heartRate, DEC);
    debug(F(" bpm, SPO2: "));
    debug(SPO2, DEC);
    debugln(F(" %"));
  } else {
    debugln(F("[debug] Please, put your finger. Wait about four (4) seconds to read values."));
  }
}
