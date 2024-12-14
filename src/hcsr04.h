#ifndef HCSR04_H
#define HCSR04_H

extern bool sensorRunning;

void beginDistanceMeasurment();
float getDistance();  // Returns distance in centimeters

#endif