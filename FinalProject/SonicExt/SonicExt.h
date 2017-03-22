// SonicExt.h - Library for an ultrasonic sensor

#ifndef SonicExt_h
#define SonicExt_h

// Anything over 400 cm (23200 us pulse) is "out of range"
const unsigned int MAX_DIST = 23200;

// Pins
const int TRIG_PIN = 5;
const int ECHO_PIN = 6;

// Sets up the ultrasonic sensor
void sonicSetup ();

// Gets the distance to the closest object ahead
float getDistanceInCentimeters ();

#endif
