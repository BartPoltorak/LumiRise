#include <Arduino.h>
#include "leds.h"

// Define the pin connected to the LED
const int LED_PIN = 15;

bool ledRunning = false;

void led_initialize() {
  pinMode(LED_PIN, OUTPUT);  // Set the LED pin as an output
}

void leds_on() {
  digitalWrite(LED_PIN, HIGH);  // Turn speaker_on the LED
  ledRunning = true;
}

void leds_off() {
  digitalWrite(LED_PIN, LOW);   // Turn off the LED
  ledRunning = false;
}
