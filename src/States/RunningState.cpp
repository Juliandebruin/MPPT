#include "States/RunningState.h"
#include "MpptCommunication.h"
#include "StateMachine.h"

#include <Arduino.h>

RunningState::RunningState() :
	_sensors(ReadSensors()),
	_can_coms(CanComs()),
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
}

void RunningState::update(){
	Serial.println("Updating RunningState");

	StateMachine::instance().change_state(EState::CHARGING);

	// std::pair<long, std::string> package = _can_coms.receive_message();
	// Serial.print("ID: 0x");
	// Serial.print(package.first, HEX);
	// Serial.print(" Message: ");
	// Serial.println(package.second.c_str());
}

void RunningState::exit(){
	Serial.println("Exiting RunningState");
}