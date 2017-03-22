// ServoExt.h - Library for servos attached to wheels

#ifndef ServoExt_h
#define ServoExt_h

#define LEFT_PIN 11
#define RIGHT_PIN 12

#define MIN_SPEED 0
#define MAX_SPEED 255 // Max speed for any movement
#define SERVO_ARRAY_SIZE 3  // Array size for running average

// Sets up the servos
bool servoSetup ();

// Stops the robot
void stopRobot();

// Accelerates forward to reach the speed
void moveRobotForward(uint8_t left, uint8_t right);

// Accelerates backward to reach the speed
void moveRobotBackward(uint8_t left, uint8_t right);

// Accelerates left to reach the speed
void moveRobotLeft(uint8_t left, uint8_t right);

// Accelerates right to reach the speed
void moveRobotRight(uint8_t left, uint8_t right);

#endif
