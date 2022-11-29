#include "States/RunningState.h"
#include "MpptCommunication.h"
#include "StateMachine.h"

#include <Arduino.h>

RunningState::RunningState() :
	_coms(MpptCommunication()),
	_displayData(DisplayRegisterData())
{

}

RunningState::~RunningState() {

}

void RunningState::enter(){
	Serial.println("Entering RunningState");

	StateMachine::instance().change_state(EState::CHARGING);
}

void RunningState::update(){
	Serial.println("Updating RunningState");
}

void RunningState::exit(){
	Serial.println("Exiting RunningState");
}