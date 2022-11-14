#include "States/RunningState.h"

#include <Arduino.h>

RunningState::RunningState() {

}

RunningState::~RunningState() {

}

void RunningState::enter(){
	Serial.println("Entering RunningState");
}

void RunningState::update(){
	Serial.println("Updating RunningState");
}

void RunningState::exit(){
	Serial.println("Exiting RunningState");
}