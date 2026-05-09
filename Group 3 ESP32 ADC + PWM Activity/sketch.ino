// Embedded Systems
// FAct2 - PWM
// Group Number: 3
// Leader :Barcellano, Rolhimark
// Members:Micky Almazora
// Eugene Peley
// Joshua Nuevo
// Charle Laysico
// Section: BSCPE LADDERIZED

#include <math.h>

// --- Pin Definitions ---
const int potPin = 34;    
const int ldrPin = 35;    
const int ntcPin = 32;    
const int ledPin = 5;     

// --- PWM Settings ---
const int freq = 5000;
const int resolution = 8; 

// --- NTC Constants ---
const float BETA = 3950; 

void setup() {
  Serial.begin(115200);
  ledcAttach(ledPin, freq, resolution);
  Serial.println("--- System Active: Status Monitor ---");
}

void loop() {
  // 1. Read Raw Values
  int ldrValue = analogRead(ldrPin);
  int potValue = analogRead(potPin);
  int ntcRaw = analogRead(ntcPin);

  // 2. Temperature Calculation
  float celsius = 1 / (log(1 / (4095.0 / ntcRaw - 1)) / BETA + 1.0 / 298.15) - 273.15;

  // 3. Status Output
  Serial.print("Temp: ");
  Serial.print(celsius, 1);
  Serial.print("°C | LDR: ");
  Serial.print(ldrValue);

  if (ldrValue < 1500) {
    // DARK MODE: Potentiometer controls brightness
    int brightnessPercent = map(potValue, 0, 4095, 0, 100);
    int pwmValue = map(brightnessPercent, 0, 100, 0, 255);
    ledcWrite(ledPin, pwmValue);
    
    Serial.print(" | LED: ");
    Serial.print(brightnessPercent);
    Serial.println("%");
  } 
  else {
    // BRIGHT MODE: LED forced OFF
    ledcWrite(ledPin, 0);
    Serial.println(" | LED: OFF");
  }

  delay(250); 
}