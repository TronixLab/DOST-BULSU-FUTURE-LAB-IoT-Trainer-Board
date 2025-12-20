#define RED_PIN 13
#define GREEN_PIN 12
#define BLUE_PIN 14

const boolean invert = true;  // set true if common anode, false if common cathode

uint8_t color = 0;         // a value from 0 to 255 representing the hue
uint32_t R, G, B;          // the Red Green and Blue color components
uint8_t brightness = 255;  // 255 is maximum brightness, but can be changed.  Might need 256 for common anode to fully turn off.

void setup() {
  Serial.begin(9600);
  // Initialize pins as LEDC channels
  // Resolution 1-16 bits, freq limits depend on resolution, channel is automatically selected
  ledcAttach(RED_PIN, 12000, 8);  // 12 kHz PWM, 8-bit resolution
  ledcAttach(GREEN_PIN, 12000, 8);
  ledcAttach(BLUE_PIN, 12000, 8);
}

void loop() {
  // If your RGB LED turns off instead of on here you should check if the LED is common anode or cathode.
  // If it doesn't fully turn off and is common anode try using 256.
  ledcWrite(RED_PIN, 255);
  ledcWrite(GREEN_PIN, 255);
  ledcWrite(BLUE_PIN, 255);
  delay(2000);

  ledcWrite(RED_PIN, 0);
  ledcWrite(GREEN_PIN, 0);
  ledcWrite(BLUE_PIN, 0);
  delay(2000);

  for (color = 0; color < 255; color++) {  // Slew through the color spectrum
    hueToRGB(color, brightness);           // call function to convert hue to RGB

    // Write the RGB values to the pins
    ledcWrite(RED_PIN, R);
    ledcWrite(GREEN_PIN, G);
    ledcWrite(BLUE_PIN, B);
    // Full cycle of rgb over 256 colors takes 26 seconds
    delay(100);
  }
}

void hueToRGB(uint8_t hue, uint8_t brightness) {
  uint16_t scaledHue = (hue * 6);
  uint8_t segment = scaledHue / 256;                     // Segment 0 to 5 around the color wheel
  uint16_t segmentOffset = scaledHue - (segment * 256);  // Position within the segment
  uint8_t complement = 0;
  uint16_t prev = (brightness * (255 - segmentOffset)) / 256;
  uint16_t next = (brightness * segmentOffset) / 256;

  if (invert) {
    brightness = 255 - brightness;
    complement = 255;
    prev = 255 - prev;
    next = 255 - next;
  }

  switch (segment) {
    case 0:
      R = brightness;
      G = next;
      B = complement;
      break;
    case 1:
      R = prev;
      G = brightness;
      B = complement;
      break;
    case 2:
      R = complement;
      G = brightness;
      B = next;
      break;
    case 3:
      R = complement;
      G = prev;
      B = brightness;
      break;
    case 4:
      R = next;
      G = complement;
      B = brightness;
      break;
    case 5:
    default:
      R = brightness;
      G = complement;
      B = prev;
      break;
  }
}
