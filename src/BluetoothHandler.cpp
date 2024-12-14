#include "BluetoothHandler.h"
#include <Arduino.h>

#define SERVICE_UUID "4fafc201-1fb5-459e-8fcc-c5c9c331914b"
#define CHARACTERISTIC_UUID "beb5483e-36e1-4688-b7f5-ea07361b26a8"

int wakeTimer = -1;
bool musicRunning = false;

// Added global variables for HID
BLEHIDDevice *hidDevice;
BLECharacteristic *inputCharacteristic;

void MyCallbacks::onWrite(BLECharacteristic *pCharacteristic) {
  std::string value = pCharacteristic->getValue();

  if (value.length() > 0) {
    Serial.println("*********");
    Serial.print("New value: ");
    for (int i = 0; i < value.length(); i++)
      Serial.print(value[i]);

    Serial.println();
    Serial.println("*********");

    wakeTimer = String(value.c_str()).toInt(); // string to integer
  }
}

// Added play_pause function
void play_pause() {
  if (musicRunning) {
    musicRunning = false;
  }
  else {
    musicRunning = true;
  }
  
  uint8_t key = 0xCD; // Media play/pause usage ID
  inputCharacteristic->setValue((uint8_t *)&key, 1);
  inputCharacteristic->notify();

  delay(10); // Short delay to simulate key press
  key = 0;   // Release key
  inputCharacteristic->setValue((uint8_t *)&key, 1);
  inputCharacteristic->notify();

  Serial.println("Play/Pause command sent!");
}

void setupBluetooth() {
  BLEDevice::init("LumiRise-0.3");
  BLEServer *pServer = BLEDevice::createServer();
  BLEService *pService = pServer->createService(SERVICE_UUID);
  BLECharacteristic *pCharacteristic = pService->createCharacteristic(
                                        CHARACTERISTIC_UUID,
                                        BLECharacteristic::PROPERTY_READ |
                                        BLECharacteristic::PROPERTY_WRITE
                                      );

  pCharacteristic->setCallbacks(new MyCallbacks());

  pCharacteristic->setValue("initial bluetooth value");
  pService->start();

  BLEAdvertising *pAdvertising = pServer->getAdvertising();
  pAdvertising->start();

  // Added HID setup
  hidDevice = new BLEHIDDevice(pServer);
  inputCharacteristic = hidDevice->inputReport(1); // Report ID 1

  hidDevice->manufacturer()->setValue("LumiRise");
  hidDevice->pnp(0x02, 0xe502, 0xa111, 0x0210);
  hidDevice->hidInfo(0x00, 0x01);

  // Media control descriptor
  const uint8_t mediaReportMap[] = {
      0x05, 0x0C,  // Usage Page (Consumer Devices)
      0x09, 0x01,  // Usage (Consumer Control)
      0xA1, 0x01,  // Collection (Application)
      0x85, 0x01,  // Report ID (1)
      0x15, 0x00,  // Logical Minimum (0)
      0x25, 0x01,  // Logical Maximum (1)
      0x09, 0xCD,  // Usage (Play/Pause)
      0x75, 0x01,  // Report Size (1)
      0x95, 0x01,  // Report Count (1)
      0x81, 0x06,  // Input (Data, Var, Rel)
      0xC0         // End Collection
  };

  hidDevice->reportMap((uint8_t *)mediaReportMap, sizeof(mediaReportMap));
  hidDevice->startServices();
}