#include "States/ChargingState.h"

#include <Arduino.h>

ChargingState::ChargingState() {

}

ChargingState::~ChargingState() {

}

void ChargingState::enter(){
	Serial.println("Entering ChargingState");
}

void ChargingState::update(){
	Serial.println("Updating ChargingState");
}

void ChargingState::exit(){
	Serial.println("Exiting ChargingState");
}