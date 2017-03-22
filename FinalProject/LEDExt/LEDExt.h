// LEDExt.h - Library for the built-in LED

#ifndef LEDExt_h
#define LEDExt_h

#define BLINK_DELAY 100 // Delay before blinking
#define BLINK_MAX   255 // Max blinking time

// Sets up the built-in LED
bool LEDSetup ();

// Blinks the LED for the specified time up to 255 milliseconds
void blinkLED (uint8_t milliseconds);

// Turns the LED on until further instructions
void turnLEDOn ();

// Turns the LED off until further instructions 
void turnLEDOff ();
 
#endif
