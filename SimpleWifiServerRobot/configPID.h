#ifndef CONFIGPID__H
#define CONFIGPID__H

#include <Arduino.h>

// PID VALUES FOR MOTOR PID
float Kp = 5;
float Ki = 1.7;
float Kd = 0;

volatile uint8_t readyToPID = 0;
volatile int16_t countsLeft = 0;
volatile int16_t countsRight = 0;

float targetLeft = 0;   //target speed for the left tread
float targetRight = 0;  //target speed for the right tred

const float DEFAULT_DRIVE_SPEED = 20;

void driveForward(){
  targetLeft = DEFAULT_DRIVE_SPEED;
  targetRight = DEFAULT_DRIVE_SPEED;
}

void driveBackward(){
  targetLeft = -DEFAULT_DRIVE_SPEED;
  targetRight = -DEFAULT_DRIVE_SPEED;
}

void driveTurnLeft(){
  targetLeft = -DEFAULT_DRIVE_SPEED;
  targetRight = DEFAULT_DRIVE_SPEED;
}

void driveTurnRight(){
  targetLeft = DEFAULT_DRIVE_SPEED;
  targetRight = -DEFAULT_DRIVE_SPEED;
}

void driveStop(){
  targetLeft = 0;
  targetRight = 0;
}
#endif
