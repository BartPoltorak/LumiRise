#ifndef LEDS_H
#define LEDS_H

// Function declarations
void led_initialize();  // Initialize the LED pin
void leds_on();         // Turn speaker_on the LED
void leds_off();        // Turn off the LED

extern bool ledRunning;

#endif // LEDS_H
