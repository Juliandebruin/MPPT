#include "States/ErrorState.h"

#include <Arduino.h>

ErrorState::ErrorState() {

}

ErrorState::~ErrorState() {

}

void ErrorState::enter(){
	Serial.println("Entering ErrorState");
}

void ErrorState::update(){
	Serial.println("Updating ErrorState");
}

void ErrorState::exit(){
	Serial.println("Exiting ErrorState");
}