#include "hcsr04.h"
#include <Arduino.h>

int trigPin = 12;
int echoPin = 13;
unsigned long timeout = 24000;
bool sensorRunning = false;


void beginDistanceMeasurment() {
    pinMode(trigPin, OUTPUT);
    pinMode(echoPin, INPUT);
    digitalWrite(trigPin, LOW);
    sensorRunning = true;
}

float getDistance() {
    // Trigger pulse
    digitalWrite(trigPin, HIGH);
    delayMicroseconds(10);
    digitalWrite(trigPin, LOW);
    
    // Measure echo
    unsigned long duration = pulseIn(echoPin, HIGH, timeout);
    
    // Convert to distance (cm)
    // Speed of sound = 343m/s = 34300cm/s
    // Distance = (Time × Speed) ÷ 2
    // 34300 / 2 / 1000000 = 0.01715
    return duration * 0.01715;
}