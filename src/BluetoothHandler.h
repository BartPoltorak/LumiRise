#ifndef BLUETOOTH_HANDLER_H
#define BLUETOOTH_HANDLER_H

#include <BLEDevice.h>
#include <BLEUtils.h>
#include <BLEServer.h>
#include <BLEHIDDevice.h>
#include <HIDTypes.h>

extern int wakeTimer; // variable used globally
extern bool musicRunning;

void setupBluetooth(); // function to initialize Bluetooth
void play_pause(); // function to send play/pause signal

class MyCallbacks : public BLECharacteristicCallbacks {
  void onWrite(BLECharacteristic *pCharacteristic);
};

#endif