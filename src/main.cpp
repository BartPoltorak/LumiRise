#include <Arduino.h>
#include "stepper.h"
#include "BluetoothHandler.h"
#include "leds.h"
#include "speaker.h"
#include "hcsr04.h"

bool alarmTurnedOff = false;
float distance = 999.9;

void setup() {
  Serial.begin(9600);

  setupBluetooth(); // Call the function to set up Bluetooth
  initStepper();  // Initialize the stepper motor
  led_initialize();  // Initialize the LED pin
  speaker_initialize(); // Intialize the Speaker pin

  // output pins: 17, 2, 21, 22, 32, 33, 25, 26, 27
}

void loop() {
  // Timer mechanism (decrement every second )
  if (wakeTimer > 0){ // Wait for a value to be set
    // Check if one second has passed
    static unsigned long previousMillis = 0; // Keeps track of time
    unsigned long currentMillis = millis();
    if (currentMillis - previousMillis >= 1000) {
        previousMillis = currentMillis; // Reset the timer

        // Decrement wakeTimer if greater than 0
        if (wakeTimer >= 1) {
        wakeTimer--;
        Serial.print("wakeTimer: ");
        Serial.println(wakeTimer);
        }
    }
  }

  // Turn on the motor when wakeTimer = 60
  if (wakeTimer == 60 && !motorRunning) {
    Serial.println("Turning on the motor...");
    stepper_on(500); // Set motor speed to 500 steps/second
  }

  // turn LED on when wakeTimer = 20
  if (wakeTimer == 20 && !ledRunning) {
    Serial.println("Turning on the LED...");
    leds_on();
  }

  // turn speaker on when wakeTimer = 0
  if (wakeTimer == 0 && !musicRunning) {
    Serial.println("Turning on the speaker...");
    play_pause();
  }

  if (wakeTimer == 0) {
    Serial.println("Waiting for hand wave...");
    if (!sensorRunning) {
      beginDistanceMeasurment();
    }
    // speaker_off();
    // leds_off();
    // stepper_off();
    wakeTimer = -1;
  }

  if (sensorRunning) {
    distance = getDistance();
  }

  if (sensorRunning && !alarmTurnedOff && distance < 10 && distance > 1) {
    Serial.println("Turning off the alarm...");
    Serial.print("Distance value: ");
    Serial.println(distance);

    alarmTurnedOff = true;
    stepper_off();
    leds_off();
    play_pause();
  }

  updateStepper();
}
