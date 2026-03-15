#include <math.h>

#define VOLTAGE_PIN PA0
#define ADC_MAX 4095.0
#define VREF 3.3

// Calibration values from your code
float voltageCal = 667.86;
float voltageOffsetValue = 2048.0;

#define FFT_SIZE 256

float Vrms;

void setup() {
  Serial.begin(115200);
  analogReadResolution(12);

  // --- Auto offset calibration ---
  long vSum = 0;
  for (int i = 0; i < 2000; i++) {
    vSum += analogRead(VOLTAGE_PIN);
    delayMicroseconds(100);
  }

  voltageOffsetValue = (float)vSum / 2000.0;

  Serial.println("Voltage Calibration Started");
}

void loop() {

  float sumV2 = 0;

  for (int i = 0; i < FFT_SIZE; i++) {

    float vSample = analogRead(VOLTAGE_PIN);

    float voltage = (vSample - voltageOffsetValue) * VREF / ADC_MAX * voltageCal;

    sumV2 += voltage * voltage;

    delayMicroseconds(500);
  }

  Vrms = sqrt(sumV2 / FFT_SIZE);

  Serial.print("Voltage RMS: ");
  Serial.print(Vrms, 2);
  Serial.println(" V");

  delay(1000);
}