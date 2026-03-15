#define BLYNK_TEMPLATE_ID "TMPL32L6U6n78" 
#define BLYNK_TEMPLATE_NAME "power analyser"
#define BLYNK_AUTH_TOKEN "jt3r5O7ndP5xQ22ET6Oihn1sDCVQoOvw"

#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>
#include <SoftwareSerial.h>

// --- PIN DEFINITIONS ---
#define GREEN_LED 13 // D7
#define RED_LED   15 // D8
#define CAP1      0  // Changed to D3 (GPIO0)
#define CAP2      2  // Changed to D4 (GPIO2)

SoftwareSerial stmSerial(14, 12); // D5 (RX), D6 (TX)

char ssid[] = "vishnu";
char pass[] = "vishnuprasad";

// --- TIMER VARIABLES ---
unsigned long lowPFStartTime = 0;
bool isWaitingToCorrect = false;
const unsigned long CORRECTION_DELAY = 5000; 

void setup() {
  // --- CRITICAL SOFTWARE LOCK FOR ACTIVE-LOW ---
  // We write HIGH first so the relays stay OFF during boot
  digitalWrite(CAP1, HIGH); 
  digitalWrite(CAP2, HIGH);
  pinMode(CAP1, OUTPUT);
  pinMode(CAP2, OUTPUT);
  digitalWrite(CAP1, HIGH); 
  digitalWrite(CAP2, HIGH);

  pinMode(GREEN_LED, OUTPUT);
  pinMode(RED_LED, OUTPUT);
  digitalWrite(GREEN_LED, LOW);
  digitalWrite(RED_LED, LOW);

  Serial.begin(115200);    
  stmSerial.begin(115200); 

  Serial.println("System Initializing (D3/D4 Active-Low)...");
  Blynk.begin(BLYNK_AUTH_TOKEN, ssid, pass);
}

void loop() {
  Blynk.run();

  if (stmSerial.available() > 0) {
    String rawData = stmSerial.readStringUntil('\n');
    
    Serial.print("Raw Data Received: ");
    Serial.println(rawData);
    
    yield(); 

    int c1 = rawData.indexOf(',');
    int c2 = rawData.indexOf(',', c1 + 1);
    int c3 = rawData.indexOf(',', c2 + 1);
    int c4 = rawData.indexOf(',', c3 + 1);
    int c5 = rawData.indexOf(',', c4 + 1);
    int c6 = rawData.indexOf(',', c5 + 1);
    int c7 = rawData.indexOf(',', c6 + 1);
    int c8 = rawData.indexOf(',', c7 + 1);

    if (c1 != -1) {
      float v    = rawData.substring(0, c1).toFloat();
      float i    = rawData.substring(c1 + 1, c2).toFloat();
      float p    = rawData.substring(c2 + 1, c3).toFloat();
      float s    = rawData.substring(c3 + 1, c4).toFloat();
      float pf   = rawData.substring(c4 + 1, c5).toFloat();
      float vc   = rawData.substring(c5 + 1, c6).toFloat();
      float ic   = rawData.substring(c6 + 1, c7).toFloat();
      float vthd = rawData.substring(c7 + 1, c8).toFloat();
      float ithd = rawData.substring(c8 + 1).toFloat();

      String statusMsg = "System Healthy";

      // --- LED WARNING SYSTEM ---
      if (pf < 0.70) {
        digitalWrite(RED_LED, HIGH);
        digitalWrite(GREEN_LED, LOW);
      } 
      else if (pf > 0.80) {
        digitalWrite(RED_LED, LOW);
        digitalWrite(GREEN_LED, HIGH);
      }

      // --- CORRECTION & RELAY LOGIC (ACTIVE-LOW) ---
      if (v > 10.0 && i > 0.05) { 
        if (pf < 0.95) {
          if (!isWaitingToCorrect) {
            lowPFStartTime = millis();
            isWaitingToCorrect = true;
          }

          unsigned long elapsed = millis() - lowPFStartTime;

          if (elapsed >= CORRECTION_DELAY) {
            float q_req = sqrt(fabs((s * s) - (p * p)));
            float q_cap = (v * v) * 2.0 * 3.14159 * 50.0 * 0.0000025; 
            
            if (q_req > (q_cap * 1.5)) {
              digitalWrite(CAP1, LOW);  // RELAY ON
              digitalWrite(CAP2, LOW);  // RELAY ON
              statusMsg = "Correction Done (2 Caps)";
            } else if (q_req > (q_cap * 0.5)) {
              digitalWrite(CAP1, LOW);  // RELAY ON
              digitalWrite(CAP2, HIGH); // RELAY OFF
              statusMsg = "Correction Done (1 Cap)";
            } else {
              digitalWrite(CAP1, HIGH); // RELAY OFF
              digitalWrite(CAP2, HIGH); // RELAY OFF
              statusMsg = "Low PF - No Cap Needed";
            }
          } else {
            int remaining = (CORRECTION_DELAY - elapsed) / 1000;
            statusMsg = "Low PF! Fixing in " + String(remaining) + "s";
          }
        } else {
          isWaitingToCorrect = false;
          digitalWrite(CAP1, HIGH); // RELAY OFF
          digitalWrite(CAP2, HIGH); // RELAY OFF
          statusMsg = "System Healthy";
        }
      } else {
        // --- NO LOAD: KEEP RELAYS OFF (HIGH) ---
        isWaitingToCorrect = false;
        digitalWrite(CAP1, HIGH);     // RELAY OFF
        digitalWrite(CAP2, HIGH);     // RELAY OFF
        digitalWrite(RED_LED, LOW);   
        digitalWrite(GREEN_LED, LOW); 
        statusMsg = "No Load Detected";
      }

      // --- BLYNK DASHBOARD UPDATES ---
      Blynk.virtualWrite(V0, v);   
      Blynk.virtualWrite(V1, i);   
      Blynk.virtualWrite(V2, p);   
      Blynk.virtualWrite(V3, s);   
      Blynk.virtualWrite(V4, pf);  
      Blynk.virtualWrite(V5, vc);  
      Blynk.virtualWrite(V6, ic);  
      Blynk.virtualWrite(V7, vthd); 
      Blynk.virtualWrite(V8, ithd);
      Blynk.virtualWrite(V9, statusMsg); 
      
      Serial.println("PF: " + String(pf) + " | Status: " + statusMsg);
    } else {
      Serial.println("Error: Data parsing failed. Check STM32 string format.");
    }
  }
}