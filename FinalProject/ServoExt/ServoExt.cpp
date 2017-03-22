/* Blank.cpp, a starter file for creating your own C++ class. */

#include <Arduino.h>
#include <Servo.h>
#include "ServoExt.h"

#define LEFT_NAME "LEFT"
#define RIGHT_NAME "RIGHT"
#define SERVO_STOP 90
#define LEFT_MAX_FWD 180
#define RIGHT_MAX_FWD 0
#define LEFT_MAX_RVS 0
#define RIGHT_MAX_RVS 180

Servo leftServo;
Servo rightServo;

// Set the servo speeds
void setServos (int leftSetting, int rightSetting) {
  leftServo.write (leftSetting);
  rightServo.write (rightSetting);
}

// Move the robot forward
void moveRobotForward (uint8_t left, uint8_t right){
 left = map (left, MIN_SPEED, MAX_SPEED, SERVO_STOP, LEFT_MAX_FWD);
 right = map (right, MIN_SPEED, MAX_SPEED, SERVO_STOP, RIGHT_MAX_FWD);
 setServos (left, right);
}

// Move the robot backward
void moveRobotBackward (uint8_t left, uint8_t right){
  left = map (left, MIN_SPEED, MAX_SPEED, SERVO_STOP, LEFT_MAX_RVS);
  right = map (right, MIN_SPEED, MAX_SPEED, SERVO_STOP, RIGHT_MAX_RVS);
  setServos (left, right);
}

// Move the robot left
void moveRobotLeft (uint8_t left, uint8_t right){
  left = map (left, MIN_SPEED, MAX_SPEED, SERVO_STOP, LEFT_MAX_RVS);
  right = map (right, MIN_SPEED, MAX_SPEED, SERVO_STOP, RIGHT_MAX_FWD);
  setServos (left, right);
}

// Move the robot right
void moveRobotRight (uint8_t left, uint8_t right){
  left = map (left, MIN_SPEED, MAX_SPEED, SERVO_STOP, LEFT_MAX_FWD);
  right = map (right, MIN_SPEED, MAX_SPEED, SERVO_STOP, RIGHT_MAX_RVS);
  setServos (left, right);
}

// Stop the robot
void stopRobot (void){
  setServos (SERVO_STOP, SERVO_STOP);
}

// Attaches a servo to a specified pin
void attachServo (Servo servo, String servoName, int servoPin) {
  servo.attach(servoPin);

  Serial.println();
  Serial.print(servoName);
  Serial.print(" servo attached to pin: ");
  Serial.print(servoPin);
  Serial.println();
}

// Sets up the servos
bool servoSetup () {
  Serial.println(F("******************************"));
  Serial.println(F("INITIALIZING SERVOS"));
  Serial.println(F("******************************"));
  Serial.println();
  Serial.println(F("Initializing servo positions..."));

  stopRobot();

  Serial.print("Servos set to: ");
  Serial.print(SERVO_STOP);
  Serial.println();

  attachServo (leftServo, LEFT_NAME, LEFT_PIN);
  attachServo (rightServo, RIGHT_NAME, RIGHT_PIN);

  Serial.println(F("******************************"));
  Serial.println();
  return true;
}
