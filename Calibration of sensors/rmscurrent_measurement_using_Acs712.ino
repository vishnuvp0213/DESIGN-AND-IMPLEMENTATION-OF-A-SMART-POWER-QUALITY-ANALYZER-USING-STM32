const int sensorPin = A0;
const int offsetValue = 844;      // Your zero-load raw reading
const float sensitivity = 0.066; // 66mV/A for 30A model
const float voltsPerUnit = 3.3 / 1024.0; // ESP8266 ADC math

void setup() {
  Serial.begin(115200);
  Serial.println("ACS712 30A Measurement Started...");
}

void loop() {
  uint32_t period = 40; // Sample over 2 full cycles (50Hz = 20ms per cycle)
  uint32_t startTime = millis();
  
  uint32_t samples = 0;
  float sumSquaredDiff = 0;

  while (millis() - startTime < period) {
    int rawValue = analogRead(sensorPin);
    
    // Calculate how far the current value is from your 542 center
    float diff = (float)rawValue - offsetValue;
    
    // Square the difference to handle AC (makes all values positive)
    sumSquaredDiff += (diff * diff);
    samples++;
    
    // Small yield to keep ESP8266 background tasks (WiFi/WDT) happy
    if (samples % 10 == 0) yield(); 
  }

  // 1. Calculate Mean of Squares
  float meanSquare = sumSquaredDiff / samples;
  
  // 2. Take Square Root to get RMS in "Raw Units"
  float rmsRaw = sqrt(meanSquare);
  
  // 3. Convert Raw Units to Voltage, then to Amperes
  float currentRMS = (rmsRaw * voltsPerUnit) / sensitivity;

  // Print results
  if (currentRMS < 0.10) currentRMS = 0.0; // Simple noise floor

  Serial.print("Samples: "); Serial.print(samples);
  Serial.print(" | RMS Current: "); Serial.print(currentRMS, 3);
  Serial.println(" A");

  delay(500);
}