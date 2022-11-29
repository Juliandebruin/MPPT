#include "States/RunningState.h"
#include "MpptCommunication.h"
#include "StateMachine.h"

#include <Arduino.h>

RunningState::RunningState() :
	_sensors(ReadSensors()),
	_coms(MpptCommunication()),
	_display_data(DisplayRegisterData())
{

}

RunningState::~RunningState() {
	
}

void RunningState::enter(){
	Serial.println("Entering RunningState");

	Serial.print("Temp1: ");
  	Serial.println(_sensors.get_temperature(0));

	Serial.print("Temp2: ");
  	Serial.println(_sensors.get_temperature(1));

	StateMachine::instance().change_state(EState::CHARGING);
}

void RunningState::update(){
	Serial.println("Updating RunningState");
}

void RunningState::exit(){
	Serial.println("Exiting RunningState");
}