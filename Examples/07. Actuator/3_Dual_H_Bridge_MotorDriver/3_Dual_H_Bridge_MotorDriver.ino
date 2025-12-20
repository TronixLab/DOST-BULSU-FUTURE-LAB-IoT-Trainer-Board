#define DEBUG 1
#if DEBUG == 1
#define debug(x) Serial.print(x);
#define debugln(x) Serial.println(x);
#else
#define debug(x)
#define debugln(x)
#endif

#define IN1_PIN 12
#define IN2_PIN 13
#define ENA_PIN 14

void setup() {
  Serial.begin(9600);
  pinMode(ENA_PIN, OUTPUT);
  pinMode(IN1_PIN, OUTPUT);
  pinMode(IN2_PIN, OUTPUT);
  debugln(F("[debug] Enter 's' (stop), 'f' (forward) or 'r' (reverse) followed by Duty Cycle (0 - 255)."));
  debugln(F("[debug] Example: f200."));
}

void loop() {
  if (Serial.available()) {
    char motor_rotation = Serial.read();
    if (motor_rotation == 's') {
      stop();
      return;
    }
    int PWM = Serial.parseInt();
    if (motor_rotation == 'f') {
      forward(PWM);
    } else if (motor_rotation == 'r') {
      reverse(PWM);
    }
  }
}

void forward(int PWM) {
  digitalWrite(IN1_PIN, HIGH);
  digitalWrite(IN2_PIN, LOW);
  analogWrite(ENA_PIN, PWM);
  debug(F("[debug] Forward - PWM: "));
  debugln(PWM);
}

void reverse(int PWM) {
  digitalWrite(IN1_PIN, LOW);
  digitalWrite(IN2_PIN, HIGH);
  analogWrite(ENA_PIN, PWM);
  debug(F("[debug] Reverse - PWM: "));
  debugln(PWM);
}

void stop() {
  digitalWrite(IN1_PIN, LOW);
  digitalWrite(IN2_PIN, LOW);
  analogWrite(ENA_PIN, 0);
  debugln(F("[debug] Stop!"));
}