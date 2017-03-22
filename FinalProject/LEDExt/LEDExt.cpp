/* LEDExt.cpp, library for managing the built-in LED. */

#include <Arduino.h>

#include "LedExt.h"

// Sets up the built-in LED
bool LEDSetup () {
  Serial.println(F("******************************"));
  Serial.println(F("INITIALIZING BUILT-IN LED"));
  Serial.println();
  
  pinMode(LED_BUILTIN, OUTPUT);

  blinkLED (BLINK_MAX);

  Serial.println(F("Finished."));
  Serial.println(F("******************************"));
  Serial.println();
}

// Blinks the LED for the specified time
void blinkLED (uint8_t milliseconds) {
  turnLEDOff ();
  delay(BLINK_DELAY);
  
  turnLEDOn ();
  delay(milliseconds);
  
  turnLEDOff();
}

// Turns the LED on until further instructions
void turnLEDOn () {
  digitalWrite(LED_BUILTIN, HIGH);
}

// Turns the LED off until further instructions
void turnLEDOff () {
  digitalWrite(LED_BUILTIN, LOW);
}

