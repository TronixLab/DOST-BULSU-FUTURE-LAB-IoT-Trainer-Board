String rcvString = "88,23.74,358.41,93.64\r\n";
int idx_1, idx_2, idx_3;

void setup() {
  Serial.begin(115200);
  idx_1 = rcvString.indexOf(',');
  idx_2 = rcvString.indexOf(',', idx_1 + 1);
  idx_3 = rcvString.indexOf(',', idx_2 + 1);
}

void loop() {
  String firstValue = rcvString.substring(0, idx_1);
  String secondValue = rcvString.substring(idx_1 + 1, idx_2);
  String thirdValue = rcvString.substring(idx_2 + 1, idx_3);
  String fourthValue = rcvString.substring(idx_3 + 1);

  Serial.print("Humidity: ");
  Serial.println(firstValue);
  Serial.print("Temperature: ");
  Serial.println(secondValue);
  Serial.print("Light: ");
  Serial.println(thirdValue);
  Serial.print("Soil Moisture: ");
  Serial.println(fourthValue);
  delay(1000);
}
