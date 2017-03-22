// RGBExt.h - Library for an RGB sensor

#ifndef RGBExt_h
#define RGBExt_h

#define SATURATED 0.40f    // Threshold for detecting a majority color
#define ARRAY_SIZE 3       // Array size for running average
#define commonAnode true   // set to false if using a common cathode LED

// Sets up the RGB sensor
void rgbSetup (void);

// Gets the RGB input from the sensor
void getRGBInput (void);

// True when red is detected, false otherwise
bool redAhead (void);

// True when green is detected, false otherwise
bool greenAhead (void);

#endif
