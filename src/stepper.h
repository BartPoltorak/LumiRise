#ifndef STEPPER_H
#define STEPPER_H

#include <AccelStepper.h>

// Initialize the stepper motor
void initStepper();
// Start the motor with a specified speed
void stepper_on(int speed);
// Stop the motor
void stepper_off();
// Update the motor movement
void updateStepper();

extern bool motorRunning;

#endif
