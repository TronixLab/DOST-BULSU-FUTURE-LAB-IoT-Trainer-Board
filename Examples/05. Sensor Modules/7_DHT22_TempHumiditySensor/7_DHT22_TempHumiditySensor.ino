/************************************************
Arduino Library
- DHT sensor library for ESP32
- v1.19
- Authors: beegee_tokyo
- Reference: https://github.com/beegee-tokyo/DHTesp
************************************************/
#include <DHTesp.h>

#define DEBUG 1
#if DEBUG == 1
#define debug(x) Serial.print(x);
#define debugln(x) Serial.println(x);
#else
#define debug(x)
#define debugln(x)
#endif
#define DATA_PIN 4

DHTesp dht;
ComfortState cf;

void setup() {
  Serial.begin(9600);
  dht.setup(DATA_PIN, DHTesp::AM2302);
}

void loop() {
  TempAndHumidity newValues = dht.getTempAndHumidity();
  // Check if any reads failed and exit early (to try again).
  if (dht.getStatus() != 0) {
    debug(F("[debug] DHT22 error status: "));
    debugln(String(dht.getStatusString()));
    return;
  }

  float tempC = newValues.temperature;
  float humid = newValues.humidity;
  float heatIndex = dht.computeHeatIndex(newValues.temperature, newValues.humidity);
  float dewPoint = dht.computeDewPoint(newValues.temperature, newValues.humidity);
  float comportRatio = dht.getComfortRatio(cf, newValues.temperature, newValues.humidity);

  String comfortStatus;
  switch (cf) {
    case Comfort_OK:
      comfortStatus = "Comfortable";
      break;
    case Comfort_TooHot:
      comfortStatus = "Hot";
      break;
    case Comfort_TooCold:
      comfortStatus = "Cold";
      break;
    case Comfort_TooDry:
      comfortStatus = "Dry";
      break;
    case Comfort_TooHumid:
      comfortStatus = "Humid";
      break;
    case Comfort_HotAndHumid:
      comfortStatus = "Hot and Humid";
      break;
    case Comfort_HotAndDry:
      comfortStatus = "Hot and Dry";
      break;
    case Comfort_ColdAndHumid:
      comfortStatus = "Cold and Humid";
      break;
    case Comfort_ColdAndDry:
      comfortStatus = "Cold and Dry";
      break;
    default:
      comfortStatus = "Unknown";
      break;
  };

  debug(F("[debug] Temperature: "));
  debug(tempC);
  debug(F("°C,   Humidity: "));
  debug(humid);
  debug(F("%,   Heat Index: "));
  debug(heatIndex);
  debug(F("°C,   Dew Point: "));
  debug(dewPoint);
  debug(F("°C,   Comfort Ratio: "));
  debug(comportRatio);
  debug(F(",   Comfort Status: "));
  debugln(comfortStatus);
  delay(5000);
}