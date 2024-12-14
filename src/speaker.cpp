#include "speaker.h"

// Define the pin connected to the speaker
const int SPEAKER_PIN = 33;

bool speakerRunning = false;

void speaker_initialize() {
  pinMode(SPEAKER_PIN, OUTPUT);  // Set the speaker pin as an output
}

void speaker_on() {
  digitalWrite(SPEAKER_PIN, HIGH);  // Turn speaker_on the speaker
  speakerRunning = true;
}

void speaker_off() {
  digitalWrite(SPEAKER_PIN, LOW);   // Turn off the speaker
  speakerRunning = false;
}
