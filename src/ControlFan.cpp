#include "ControlFan.h"

#include <Arduino.h>

#define CHANNEL 0
#define FAN_PIN 18
#define FAN_FREQUENCY 25000
#define RESOLUTION_BITS 8

ControlFan::ControlFan() :
    _fan_running(true) 
{
    ledcSetup(CHANNEL, FAN_FREQUENCY, RESOLUTION_BITS);
    ledcAttachPin(FAN_PIN, CHANNEL);
}

ControlFan::~ControlFan() {

}

void ControlFan::set_fan_speed(int speedPercentage) {
    if (!_fan_running) {
        ledcWrite(CHANNEL, 255);
        delay(50);
        _fan_running = true;
    }

    int speed = ((speedPercentage * 155) / 100) + 100;

    if (speedPercentage == 0) {
        _fan_running = false;
        speed = 0;
    }
    
    ledcWrite(CHANNEL, speed);    
}