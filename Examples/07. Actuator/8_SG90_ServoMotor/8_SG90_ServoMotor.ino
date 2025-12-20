#include <ESP32Servo.h>

// Define the servo and the pin it is connected to
Servo SG90;
#define CTRL_PIN 4

// Define the minimum and maximum pulse widths for the servo
#define MIN_PW_US 500
#define MAX_PW_US 2500

void setup() {
  // Attach the servo to the specified pin and set its pulse width range
  SG90.attach(CTRL_PIN, MIN_PW_US, MAX_PW_US);

  // Set the PWM frequency for the servo
  SG90.setPeriodHertz(50);  // Standard 50Hz servo

  SG90.write(0);    // Move the servo to 0 degrees
  delay(1000);      // Wait 1 second
  SG90.write(90);   // Move the servo to 90 degrees
  delay(1000);      // Wait 1 second
  SG90.write(180);  // Move the servo to 180 degrees
  delay(1000);      // Wait 1 second
}

void loop() {
  // Rotate the servo from 0 to 180 degrees
  for (int angle = 0; angle <= 180; angle++) {
    int pulseWidth = map(angle, 0, 180, MIN_PW_US, MAX_PW_US);
    SG90.writeMicroseconds(pulseWidth);
    delay(15);
  }

  // Rotate the servo from 180 to 0 degrees
  for (int angle = 180; angle >= 0; angle--) {
    int pulseWidth = map(angle, 0, 180, MIN_PW_US, MAX_PW_US);
    SG90.writeMicroseconds(pulseWidth);
    delay(15);
  }

  for (int pos = 0; pos <= 180; pos += 1) {
    SG90.write(pos);  // in steps of 1 degree
    delay(15);        // waits 15ms to reach the position
  }

  // rotates from 180 degrees to 0 degrees
  for (int pos = 180; pos >= 0; pos -= 1) {
    SG90.write(pos);  // in steps of 1 degree
    delay(15);        // waits 15ms to reach the position
  }
}