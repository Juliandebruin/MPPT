#include "States/RunningState.h"
#include "DisplayRegisterData.h"
#include "MpptCommunication.h"

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

	SRegister reg = {name: "CFG_RSENSE1_R", size: EDataSize::WORD, devisionSize: 100, i2cAddress: 0x10, registerAddress: 0x28};

	MpptCommunication coms;
	float registerData = coms.get_register_data(reg);

	DisplayRegisterData display;
	display.display_register_as_float(reg, registerData);
}

void RunningState::exit(){
	Serial.println("Exiting RunningState");
}