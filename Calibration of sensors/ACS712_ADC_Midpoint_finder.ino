void setup() {
  // Initialize serial communication at 115200 bits per second:
  Serial.begin(115200);
}

void loop() {
  // Read the input on analog pin 0:
  int sensorValue = analogRead(A0);
  
  // Print out the value you read:
  Serial.print("Analog Value: ");
  Serial.println(sensorValue);
  
  // Delay a bit for readability
  delay(100);        
}