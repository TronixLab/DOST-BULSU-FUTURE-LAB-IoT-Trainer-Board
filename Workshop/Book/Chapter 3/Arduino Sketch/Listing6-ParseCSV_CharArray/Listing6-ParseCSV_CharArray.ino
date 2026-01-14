const byte charLength = 32;
char csvChar[charLength] = "88,23.74,358.41,93.64\r\n";
char tempChar[charLength];
char *value;

void setup() {
  Serial.begin(115200);
}

void loop() {
  // Copy original data to temporary variable to protect the original data
  strcpy(tempChar, csvChar);

  // Parse CSV character array using strtok() function
  value = strtok(tempChar, ",");
  char *firstValue = value;

  value = strtok(NULL, ",");
  char *secondValue = value;

  value = strtok(NULL, ",");
  char *thirdValue = value;

  value = strtok(NULL, ",");
  char *fourthValue = value;
  
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
