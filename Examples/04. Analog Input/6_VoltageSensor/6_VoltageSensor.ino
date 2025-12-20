#include "driver/adc.h"
#include "esp_adc_cal.h"

#define DEBUG 1
#if DEBUG == 1
#define debug(x) Serial.print(x);
#define debugln(x) Serial.println(x);
#else
#define debug(x)
#define debugln(x)
#endif

// Create ADC channel 1 characteristic object
static esp_adc_cal_characteristics_t adc1_chars;

/********************************************
Arduino ESP32 core ADC driver API pin map
ADC1_CHANNEL_0 (GPIO 36)
ADC1_CHANNEL_1 (GPIO 37)
ADC1_CHANNEL_2 (GPIO 38)
ADC1_CHANNEL_3 (GPIO 39)
ADC1_CHANNEL_4 (GPIO 32)
ADC1_CHANNEL_5 (GPIO 33)
ADC1_CHANNEL_6 (GPIO 34)
ADC1_CHANNEL_7 (GPIO 35) 
ADC2_CHANNEL_0 (GPIO 4)
ADC2_CHANNEL_1 (GPIO 0)
ADC2_CHANNEL_2 (GPIO 2)
ADC2_CHANNEL_3 (GPIO 15)
ADC2_CHANNEL_4 (GPIO 13)
ADC2_CHANNEL_5 (GPIO 12)
ADC2_CHANNEL_6 (GPIO 14)
ADC2_CHANNEL_7 (GPIO 27)
ADC2_CHANNEL_8 (GPIO 25)
ADC2_CHANNEL_9 (GPIO 26)
********************************************/

#define VOLT_PIN ADC1_CHANNEL_0  // ADC pin IO36
#define R1 100000.00
#define R2 10000.00

// Define global variables to perform moving averaging
const int window = 10;
int readings[window];
int sample = 0;
int total = 0;
int average = 0;

void setup() {
  Serial.begin(9600);
  // Initialize ESP-32 ADC channel
  esp_adc_cal_characterize(ADC_UNIT_1, ADC_ATTEN_DB_11, ADC_WIDTH_BIT_12, adc1_chars.vref, &adc1_chars);
  adc1_config_width(ADC_WIDTH_BIT_12);
  adc1_config_channel_atten(VOLT_PIN, ADC_ATTEN_DB_11);
}

void loop() {
  for (int i = 0; i <= window; i++) {
    // Read the input ADC raw value and voltage in mV
    int adc_value = adc1_get_raw(VOLT_PIN);
    delay(10);
    uint32_t voltage = esp_adc_cal_raw_to_voltage(adc_value, &adc1_chars);
    delay(10);

    // Smooth read voltage (moving averaging)
    total = total - readings[sample];
    readings[sample] = voltage;
    total = total + readings[sample];
    sample = sample + 1;
    if (sample >= window) sample = 0;
    average = total / window;
  }

  // Calculates the battery voltage level
  float batt_volts = (average * ((R1 + R2) / R2)) / 1000.00;

  // Print voltage measurements
  debug(F("Average Voltage: "));
  debug(average);
  debug(F("mV,   Battery Voltage level: "));
  debug(batt_volts);
  debugln(F("V"));
  delay(1000);
}
