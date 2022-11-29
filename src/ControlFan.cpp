#include "ControlFan.h"

#include <Arduino.h>

#define CHANNEL 0
#define FAN_PIN 18
#define FAN_FREQUENCY 500
#define RESOLUTION_BITS 8

ControlFan::ControlFan() {
    ledcSetup(CHANNEL, FAN_FREQUENCY, RESOLUTION_BITS);
    ledcAttachPin(FAN_PIN, CHANNEL);
}

ControlFan::~ControlFan() {

}

void ControlFan::setFanSpeed(int speed) {
    ledcWrite(CHANNEL, speed);
}