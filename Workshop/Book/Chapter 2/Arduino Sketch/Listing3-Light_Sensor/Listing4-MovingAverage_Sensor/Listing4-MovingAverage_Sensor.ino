#define numReadings 20  // Value to determine the size of the readings array
#define ADC_Res_bit 12  // Set the resolution to 9-12 bits (default is 12 bits)

int readings[numReadings];  // The readings from the analog input
int readIndex = 0;          // The index of the current reading
int total = 0;              // The running total
int average = 0;            // The average value

void setup() {
  // Initialize serial communication with computer
  Serial.begin(115200);

  // Configure ADC to 12-bit resolution (0-4095)
  analogReadResolution(ADC_Res_bit);

  // Initialize the pseudo-random number generator
  randomSeed(10);

  // Initialize all the readings to 0
  for (int thisReading = 0; thisReading < numReadings; thisReading++) {
    readings[thisReading] = 0;
  }
}

void loop() {
  // Subtract the last reading
  total = total - readings[readIndex];
  // Read from the sensor
  readings[readIndex] = 10 + random(-5, 5);

  // Add the reading to the total
  total = total + readings[readIndex];

  // Calculate the average value
  average = total / numReadings;

  // Send it to the Arduino Serial plotter
  Serial.print("Raw:");
  Serial.print(readings[readIndex]);
  Serial.print(",");
  Serial.print("Average:");
  Serial.println(average);

  // Advance to the next position in the array
  readIndex = readIndex + 1;

  // if we're at the end of the array...
  if (readIndex >= numReadings) {
    // ...wrap around to the beginning
    readIndex = 0;
  }

  // Delay in between reads for stability
  delay(30);
}