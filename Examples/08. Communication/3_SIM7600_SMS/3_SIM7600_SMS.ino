/************************************************
Arduino Library
- Waveshare_SIM7600
- vx.x.x
- Authors: Waveshare
- Reference: https://www.waveshare.com/wiki/SIM7600G-H_4G_Module
************************************************/
#include <Waveshare_SIM7600.h>

/************************************************
UART pins definition
RX - IO15
TD - IO13
SIM7600G-H | ESP32 GPIO
    TXD    | RX (IO15)
    RXD    | TX (IO13)
UART pins are modified inside library
************************************************/

#define DEBUG 1
#if DEBUG == 1
#define debug(x) Serial.print(x);
#define debugln(x) Serial.println(x);
#else
#define debug(x)
#define debugln(x)
#endif

// Pin definition
int POWERKEY = 4;
char phone_number[] = "+639*********";
char text_message[] = "Hello World!";

void setup() {
  sim7600.PowerOn(POWERKEY);
  debugln(F("Sending Short Message Test:"));
  sim7600.SendingShortMessage(phone_number, text_message);

  debugln(F("Receiving Short Message Test:"));
  debug(F("Please send message to phone number:"));
  debugln(phone_number);
  sim7600.ReceivingShortMessage();
}

void loop() {
  // Nothing happens here...
}