#include "States/RunningState.h"
#include "MpptCommunication.h"
#include "StateMachine.h"
#include "ControlFan.h"

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

	// StateMachine::instance().change_state(EState::CHARGING);
}

void RunningState::update(){
	Serial.println("Updating RunningState");

	ControlFan fan;
	for (int i = 200; i < 255; i++) {
		fan.setFanSpeed(i);
		delay(90);
	}
}

void RunningState::exit(){
	Serial.println("Exiting RunningState");
}