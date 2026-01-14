#include "esp_sleep.h"
#include "driver/touch_sens.h"
#include "driver/gpio.h"
#include "driver/rtc_io.h"

// Define type of wake-up source (TIMER_WAKEUP | TOUCH_WAKEUP | GPIO_WAKEUP)
#define TIMER_WAKEUP

// Define RTC memory variable to store data
RTC_DATA_ATTR int bootCount = 0;

// Define touch sensor pin object
touch_pad_t touchPin;

void setup() {
  // Initialize serial at 115200 baud
  Serial.begin(115200);

#if defined(TIMER_WAKEUP)
// Time in seconds the ESP32 will go to sleep
#define TIME_TO_SLEEP 10
  // Enable internal timer as wake-up source
  esp_sleep_enable_timer_wakeup(TIME_TO_SLEEP * 1000000ULL);
#elif defined(TOUCH_WAKEUP)
// Touchpad sensitivity threshold
#define TOUCH_THRESHOLD 40
  // Enable touch sensor 5 (GPIO 13) as an external wake-up source
  touchSleepWakeUpEnable(T5, TOUCH_THRESHOLD);
#elif defined(GPIO_WAKEUP)
  // Enable GPIO 33 as the external wake-up source when triggering HIGH
  esp_sleep_enable_ext0_wakeup(GPIO_NUM_15, 1);
#endif

  // Increment the boot number and print it every reboot
  ++bootCount;
  Serial.println("Boot count: " + String(bootCount));

  // Print the wakeup reason for ESP32 and touchpad
  Serial.println("********************************");
  print_wakeup_reason();
  print_wakeup_touchpad();
  Serial.println("********************************");

  Serial.println("Entering sleep...");
  // Uncomment one of the following lines based on the sleep mode you want to use
  //esp_light_sleep_start();
  //esp_deep_sleep_start();
  esp_hibernate_start();
}

void loop() {
  // This will never be reached
}

void esp_hibernate_start() {
  // RTC peripherals power domain set to auto
  esp_sleep_pd_config(ESP_PD_DOMAIN_RTC_PERIPH, ESP_PD_OPTION_AUTO);
  esp_sleep_pd_config(ESP_PD_DOMAIN_RTC_SLOW_MEM, ESP_PD_OPTION_AUTO);
  esp_sleep_pd_config(ESP_PD_DOMAIN_RTC_FAST_MEM, ESP_PD_OPTION_AUTO);

  // Turn off ESP32 main power domain
  esp_sleep_pd_config(ESP_PD_DOMAIN_MAX, ESP_PD_OPTION_OFF);

  // Isolate all GPIO before entering sleep mode
  esp_sleep_config_gpio_isolate();

  // Isolate all RTC GPIO to reduce current leakage
  rtc_gpio_isolate(GPIO_NUM_0);
  rtc_gpio_isolate(GPIO_NUM_2);
  rtc_gpio_isolate(GPIO_NUM_4);
  rtc_gpio_isolate(GPIO_NUM_12);
  rtc_gpio_isolate(GPIO_NUM_13);
  rtc_gpio_isolate(GPIO_NUM_14);
  rtc_gpio_isolate(GPIO_NUM_15);
  rtc_gpio_isolate(GPIO_NUM_25);
  rtc_gpio_isolate(GPIO_NUM_26);
  rtc_gpio_isolate(GPIO_NUM_27);
  rtc_gpio_isolate(GPIO_NUM_32);
  rtc_gpio_isolate(GPIO_NUM_33);
  rtc_gpio_isolate(GPIO_NUM_34);
  rtc_gpio_isolate(GPIO_NUM_35);
  rtc_gpio_isolate(GPIO_NUM_36);
  rtc_gpio_isolate(GPIO_NUM_37);
  rtc_gpio_isolate(GPIO_NUM_38);
  rtc_gpio_isolate(GPIO_NUM_39);

  // Enter sleep mode
  esp_deep_sleep_start();
}

// Method to print the reason by which ESP32 has been awaken from sleep
void print_wakeup_reason() {
  esp_sleep_wakeup_cause_t wakeup_reason;

  wakeup_reason = esp_sleep_get_wakeup_cause();

  switch (wakeup_reason) {
    case ESP_SLEEP_WAKEUP_EXT0: Serial.println("Wakeup caused by external signal using RTC_IO"); break;
    case ESP_SLEEP_WAKEUP_EXT1: Serial.println("Wakeup caused by external signal using RTC_CNTL"); break;
    case ESP_SLEEP_WAKEUP_TIMER: Serial.println("Wakeup caused by timer"); break;
    case ESP_SLEEP_WAKEUP_TOUCHPAD: Serial.println("Wakeup caused by touchpad"); break;
    case ESP_SLEEP_WAKEUP_ULP: Serial.println("Wakeup caused by ULP program"); break;
    default: Serial.printf("Wakeup was not caused by deep sleep: %d\n", wakeup_reason); break;
  }
}

// Method to print the touchpad by which ESP32 has been awaken from sleep
void print_wakeup_touchpad() {
  touchPin = (touch_pad_t)esp_sleep_get_touchpad_wakeup_status();

#if CONFIG_IDF_TARGET_ESP32
  switch (touchPin) {
    case 0: Serial.println("Touch detected on GPIO 4"); break;
    case 1: Serial.println("Touch detected on GPIO 0"); break;
    case 2: Serial.println("Touch detected on GPIO 2"); break;
    case 3: Serial.println("Touch detected on GPIO 15"); break;
    case 4: Serial.println("Touch detected on GPIO 13"); break;
    case 5: Serial.println("Touch detected on GPIO 12"); break;
    case 6: Serial.println("Touch detected on GPIO 14"); break;
    case 7: Serial.println("Touch detected on GPIO 27"); break;
    case 8: Serial.println("Touch detected on GPIO 33"); break;
    case 9: Serial.println("Touch detected on GPIO 32"); break;
    default: Serial.println("Wakeup not by touchpad"); break;
  }
#else
  if (touchPin < TOUCH_PAD_MAX) {
    Serial.printf("Touch detected on GPIO %d\n", touchPin);
  } else {
    Serial.println("Wakeup not by touchpad");
  }
#endif
}