#include "stepper.h"

// Define stepper motor pins
#define IN1 33
#define IN2 25
#define IN3 26
#define IN4 27


// Create an AccelStepper object
AccelStepper stepper(AccelStepper::HALF4WIRE, IN1, IN3, IN2, IN4);

// Initialize variables
bool motorRunning = false;
int maxSpeed = 5000;

// Initialize the stepper motor with default speed
void initStepper() {
    stepper.setMaxSpeed(maxSpeed);    // Set a high max speed (steps per second)
    stepper.setAcceleration(3000);
    motorRunning = false;
}

// Turn speaker_on the motor with a specified speed (steps per second)
void stepper_on(int speed) {
    stepper.setSpeed(speed);     // Set the constant speed (positive for one direction)
    motorRunning = true;
}

// Turn off the motor
void stepper_off() {
    motorRunning = false;
}

// Update the motor movement
void updateStepper() {
    if (motorRunning) {
        stepper.runSpeed();
    }
}
