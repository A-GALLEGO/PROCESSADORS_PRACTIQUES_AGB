#include <Arduino.h>

int led = 1;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(1, OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  digitalWrite(1, HIGH);      // Turn the LED on (HIGH is the voltage)
  delay(500);                // Wait for a second
  Serial.println("OFF");
  digitalWrite(1, LOW);       // Turn the LED off by making the voltage
  delay(500);                // Wait for a second
  Serial.println("ON");
}