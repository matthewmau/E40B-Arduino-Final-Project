/*  E40B Final Project Extensions
 *  Matthew Mau
 *  mmau
 *  
 *  This file contains the main code for my final project.
 *  Unfortunately, Arduino makes it difficult to organize
 *  libraries, modify, and update libraries in separate
 *  directories. One can move all .cpp and .h files to
 *  a single directory or add them to the Arduino library
 *  which will create a copy elsewhere.
 */

#include <BleExt.h>
#include <LEDExt.h>
#include <RGBExt.h>
#include <ServoExt.h>
#include <SonicExt.h>
#include <SoundExt.h>

/******* PINS *******
 *  
 *  ******* DIGITAL *******
 *  LED_BUILTIN   // Pin for the built-in LED
 *  0             // USB
 *  1             // USB
 *  2             // Free
 *  3             // Free
 *  4             // Free
 *  5             // Ultrasonic Trig
 *  6             // Ultrasonic Echo
 *  7             // Sound
 *  8             // Bluetooth CTS
 *  9             // Bluetooth TXD
 *  10            // Bluetooth RXI
 *  11            // Left servo
 *  12            // Right servo
 *  13            // Free
 *  
 *  ******* ANALOG *******
 *  0             // Free
 *  1             // Free
 *  2             // Free
 *  3             // Free
 *  4             // RGB
 *  5             // RGB
 */

// These indices are for reading the Bluetooth packet
#define BUTTON_NUM_INDEX 2
#define BUTTON_PRESSED_INDEX 3

// These define the button inputs and modes
#define NO_INPUT      0
#define DEFAULT_MODE  1
#define NANNY_MODE    2
#define PARADE_MODE   3
#define CALIBRATION_MODE    4
#define FORWARD       5
#define REVERSE       6
#define LEFT          7
#define RIGHT         8

// Prevents the user from crashing using the ultrasonic sensor
// Measure in cm, NANNY_MODE only
#define TOO_CLOSE     7

// The speed at which the parade moves, too fast drowns out sound
#define PARADE_FACTOR 15

// How much to calibrate the speed on each side
#define CALIBRATION_FACTOR 10
#define CALIBRATION_MIN 15

extern uint8_t packetbuffer[];  // Buffer for Bluetooth control packets
uint8_t Mode = DEFAULT_MODE;    // Default mode, no restrictions on user
bool greenLight = true;         // True if a green light was detected, false if red. 
uint8_t left = MAX_SPEED;        // Speed for left servo
uint8_t right = MAX_SPEED;      // Speed for right servo

/******* MAIN CODE *******/

void setup () {
  while (!Serial);  // required for Flora & Micro
  delay(500);

  Serial.begin(9600);

   playStartMelody ();
  
  bleSetup();   // Bluetooth setup
  LEDSetup();   // LED setup
  rgbSetup();   // RGB setup
  servoSetup(); // Servo setup
  sonicSetup(); // Ultrasonic setup
}

void loop () {
  if (Mode == NANNY_MODE) {
    checkColors ();
    checkDistance ();
  }

  if (bleGetInput ()) {
    uint8_t buttonNumber = packetbuffer[BUTTON_NUM_INDEX] - '0';
    bool buttonPressed = packetbuffer[BUTTON_PRESSED_INDEX] - '0';
    respondToInput (buttonNumber, buttonPressed);
  }

  if (Mode == PARADE_MODE) {
    Serial.println(F("Stars and Stripes Forever by John Philip Sousa"));
    moveRobotForward(left / PARADE_FACTOR, right / PARADE_FACTOR);
    playStarsAndStripes();
    blinkLED(BLINK_MAX);
    Mode = DEFAULT_MODE;
    Serial.println(F("Back to DEFAULT_MODE"));
  }
}

// Check to see if the robot has been stopped by something red
void checkColors () {
  getRGBInput();
  if(redAhead()){
    greenLight = false;
    turnLEDOn();
    stopRobot();
  }

  if(greenAhead()) {
    greenLight = true;
    turnLEDOff ();
  }
}

void checkDistance () {
  float distanceInFront = getDistanceInCentimeters();
  // This measurement takes 100 ms.
  if (distanceInFront < TOO_CLOSE) {
    Serial.println(F("Nanny thinks you'll crash."));
    moveRobotBackward(MAX_SPEED, MAX_SPEED);
    delay(500);
    stopRobot();
  }
}

// Respond to Bluetooth input
void respondToInput (uint8_t buttonNumber, bool buttonPressed) {
  if (buttonPressed) {
    Serial.print ("Button "); Serial.print(buttonNumber);
    Serial.print(" pressed");
    Serial.println();
    
      switch (buttonNumber) {
        case DEFAULT_MODE:
          setRobotMode(DEFAULT_MODE);
          return;
          
        case NANNY_MODE:
          setRobotMode(NANNY_MODE);
          return;
          
        case PARADE_MODE:
          setRobotMode(PARADE_MODE);
          return;
          
        case CALIBRATION_MODE:
          setRobotMode(CALIBRATION_MODE);
          return;

        case FORWARD:
          if (Mode == DEFAULT_MODE || 
              nannyLetsMeMove() ||
              Mode == CALIBRATION_MODE) {
            moveRobotForward (left, right);
          }
          return;
              
        case REVERSE:
          if (Mode == DEFAULT_MODE || 
              nannyLetsMeMove() ||
              Mode == CALIBRATION_MODE) {
            moveRobotBackward (left, right);
          }
          return;
              
        case LEFT:
          if (Mode == DEFAULT_MODE || nannyLetsMeMove()) {
           moveRobotLeft(left, right);
          }
          if (Mode == CALIBRATION_MODE) {
            left -= CALIBRATION_FACTOR;
            if (left <= CALIBRATION_MIN) {
              left = MAX_SPEED;
            }
            playHighBeep();
          }
          return;
              
        case RIGHT:
          if (Mode == DEFAULT_MODE || nannyLetsMeMove()) {
           moveRobotRight (left, right);
          }
          if (Mode == CALIBRATION_MODE) {
            right -= CALIBRATION_FACTOR;
            if (right <= CALIBRATION_MIN) {
              right = MAX_SPEED;
            }
            playHighBeep();
          }
          return;
          
        default:
          Serial.println(F("Error: Unidentified button"));
          stopRobot();
          break;
      }
    } else {
      stopRobot();
    } 
}

// Set the robot mode
void setRobotMode (uint8_t mode) {
  Serial.print(F("Robot mode set: "));
  Serial.print(mode); Serial.println();
  Mode = mode;
  blinkLED(BLINK_MAX);
}

// True if nanny is kind, false otherwise
bool nannyLetsMeMove () {
  if (Mode != NANNY_MODE) return false;
  if (greenLight) {
    Serial.println(F("Nanny says, 'Green, go.'"));
    return true;
  } else {
    Serial.println(F("Nanny says, 'Red, stop.'"));
    playLowBeep();
    return false;
  }
}
