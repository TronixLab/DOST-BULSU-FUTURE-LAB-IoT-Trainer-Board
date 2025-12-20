#define TRIG_PIN 15  // Digital pin connected to the Trig pin of the sensor
#define ECHO_PIN 2   // Digital pin connected to the Echo pin of the sensor

#define DEBUG 1
#if DEBUG == 1
#define debug(x) Serial.print(x);
#define debugln(x) Serial.println(x);
#else
#define debug(x)
#define debugln(x)
#endif

unsigned long int duration_us;  // Stores the time it takes for the sound wave to travel
int distance_cm;                // Stores the calculated distance_cm

void setup() {
  Serial.begin(9600);         // Starts serial communication for debugging
  pinMode(TRIG_PIN, OUTPUT);  // Sets the TRIG_PIN as an OUTPUT
  pinMode(ECHO_PIN, INPUT);   // Sets the ECHO_PIN as an INPUT
}

void loop() {
  // Clears the TRIG_PIN by setting it LOW for a short duration_us
  digitalWrite(TRIG_PIN, LOW);
  delayMicroseconds(2);

  // Sends a 10µs HIGH pulse to trigger the sensor
  digitalWrite(TRIG_PIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG_PIN, LOW);

  // Reads the ECHO_PIN, returns the sound wave travel time in microseconds
  duration_us = pulseIn(ECHO_PIN, HIGH);

  // Calculates the distance_cm (round trip time / 2 * speed of sound)
  // Speed of sound = 343 m/s or 0.0343 cm/µs
  distance_cm = (duration_us * 0.0343) / 2;
  
  debug(F("[debug] Measured Distance: "));
  debug(distance_cm);
  debugln(F(" cm"));
  delay(1000);
}
