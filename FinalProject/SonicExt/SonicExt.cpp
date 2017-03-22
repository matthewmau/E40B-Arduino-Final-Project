/* SonicExt.cpp - Library for an ultrasonic sensor */

#include <Arduino.h>
#include "SonicExt.h"

// Sets up the ultrasonic sensor
void sonicSetup() {
  Serial.println(F("******************************"));
  Serial.println(F("INITIALIZING ULTRASONIC SENSOR"));
  Serial.println();

  digitalWrite(TRIG_PIN, LOW);
  pinMode(TRIG_PIN, OUTPUT);  

  Serial.println(F("Finished."));
  Serial.println(F("******************************"));
  Serial.println();
}

// Gets the distance to the closest object ahead
float getDistanceInCentimeters() {
  unsigned long t1;
  unsigned long t2;
  unsigned long pulse_width;
  float cm;
  float inches;

  // Hold the trigger pin high for at least 10 us
  digitalWrite(TRIG_PIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG_PIN, LOW);

  // Wait for pulse on echo pin
  while ( digitalRead(ECHO_PIN) == 0 );

  // Measure how long the echo pin was held high (pulse width)
  // Note: the micros() counter will overflow after ~70 min
  t1 = micros();
  while ( digitalRead(ECHO_PIN) == 1);
  t2 = micros();
  pulse_width = t2 - t1;

  cm = pulse_width / 58.0;

  // Print out results
  if ( pulse_width > MAX_DIST ) {
    Serial.println(F("Out of range"));
  } else {
    Serial.print(cm);
    Serial.print(F(" cm \t"));
  }

  // Wait at least 60 ms before the next measurement
  delay(100);
  return cm;
}
