/* Blank.cpp, a starter file for creating your own C++ class. */
//i can simplify this further

#include <Arduino.h>
#include <Wire.h>
#include "Adafruit_TCS34725.h"
#include "RGBExt.h"

// our RGB -> eye-recognized gamma color
byte gammatable[256];

float RedTotal = 0; // The total of the current red values.
float GrnTotal = 0; // The total of the current green values.

float RedValues[ARRAY_SIZE]; // Array of the current red values.
float GrnValues[ARRAY_SIZE]; // Array of the current green values.

uint8_t oldestValueIndex = 0; // Index of the oldest color value.

Adafruit_TCS34725 tcs = Adafruit_TCS34725(TCS34725_INTEGRATIONTIME_50MS, TCS34725_GAIN_4X);

// Sets up the RGB sensor
void rgbSetup() {
  Serial.println(F("******************************"));
  Serial.println(F("INITIALIZING RGB SENSOR"));
  Serial.println();

  if (tcs.begin()) {
    Serial.println("Sensor found.");
  } else {
    Serial.println("No TCS34725 found ... check your connections");
    while (1); // halt!
  }
  
  // Thanks PhilB for the gamma table.
  for (int i=0; i<256; i++) {
    float x = i;
    x /= 255;
    x = pow(x, 2.5);
    x *= 255;
      
    if (commonAnode) {
      gammatable[i] = 255 - x;
    } else {
      gammatable[i] = x;      
    }
  }

  Serial.println(F("Finished."));
  Serial.println(F("******************************"));
  Serial.println();
}

// True if too much of the color is detected
bool tooMuchColor (float total) {
  return (total / ARRAY_SIZE) > SATURATED;
}

// True if too much red is detected
bool redAhead () {
 return tooMuchColor (RedTotal);
}

// True if too much green is detected
bool greenAhead() {
  return tooMuchColor (GrnTotal);
}

// Sets the average given the next value, the past values, and the current total
void setMovingAverage (float nextValue, float pastValues[], float *runningTotal) {
  *runningTotal -= pastValues[oldestValueIndex];
  pastValues[oldestValueIndex] = nextValue;
  *runningTotal += nextValue;
}

// Gets the RGB input from the sensor and records the values
void getRGBInput() {
  uint16_t clear, red, green, blue;

  tcs.setInterrupt(false);      // turn on LED
  delay(60);  // takes 50ms to read 
  tcs.getRawData(&red, &green, &blue, &clear);
  tcs.setInterrupt(true);  // turn off LED

  // Figure out some basic hex code for visualization
  uint32_t sum = clear;

  float r, g, b;
  
  r = red; r /= sum;
  g = green; g /= sum;
  b = blue; b /= sum;
  r *= 256; g *= 256; b *= 256;

  float rgbSum = r + g + b;
  setMovingAverage ( r / rgbSum, RedValues, &RedTotal);
  setMovingAverage ( g / rgbSum, GrnValues, &GrnTotal);

  // Set the next index
  oldestValueIndex = (oldestValueIndex + 1) % ARRAY_SIZE;
}
