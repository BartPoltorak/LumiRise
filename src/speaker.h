#ifndef SPEAKER_H
#define SPEAKER_H

#include <Arduino.h>

// Function prototypes
void speaker_initialize(); // Initialize the speaker pin
void speaker_on();         // Turn the speaker speaker_on
void speaker_off();        // Turn the speaker off

extern bool speakerRunning;

#endif // SPEAKER_H