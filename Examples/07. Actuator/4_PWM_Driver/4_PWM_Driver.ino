#define PWM_PIN 4

void setup() {
  // Nothing happens in setup
}

void loop() {
  // On-Off DC motor control
  analogWrite(PWM_PIN, 255);
  delay(2000);
  analogWrite(PWM_PIN, 0);
  delay(2000);
  analogWrite(PWM_PIN, 255);
  delay(2000);
  analogWrite(PWM_PIN, 0);
  delay(2000);

  // Fade in from min to max in increments of 5 points:
  for (int speedValue = 0; speedValue <= 255; speedValue += 5) {
    analogWrite(PWM_PIN, speedValue);
    delay(30);
  }

  // Fade out from max to min in increments of 5 points:
  for (int speedValue = 255; speedValue >= 0; speedValue -= 5) {
    analogWrite(PWM_PIN, speedValue);
    delay(30);
  }
  delay(2000);

  // Fade in from min to max in increments of 5 points:
  for (int speedValue = 0; speedValue <= 255; speedValue += 5) {
    analogWrite(PWM_PIN, speedValue);
    delay(30);
  }

  // Fade out from max to min in increments of 5 points:
  for (int speedValue = 255; speedValue >= 0; speedValue -= 5) {
    analogWrite(PWM_PIN, speedValue);
    delay(30);
  }
  delay(2000);
}
