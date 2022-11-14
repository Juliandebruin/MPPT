#include "States/InitializationState.h"

#include <Arduino.h>

InitialisationState::InitialisationState() {

}

InitialisationState::~InitialisationState() {

}

void InitialisationState::enter(){
	Serial.println("Entering InitialisationState");
}

void InitialisationState::update(){
	Serial.println("Updating InitialisationState");
}

void InitialisationState::exit(){
	Serial.println("Exiting InitialisationState");
}