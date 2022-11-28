#include "States/RunningState.h"
#include "MpptCommunication.h"

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
}

void RunningState::update(){
	Serial.println("Updating RunningState");

	SReadRegInfo rReg = {
		name		   	: "CFG_RSENSE1_R", 
		size		   	: EDataSize::WORD, 
		devisionSize   	: 100, 
		i2cAddress	   	: 0x10, 
		registerAddress	: 0x28
	};

	SWriteRegInfo wReg = {
		name		   	: "CTRL_UPDATE_TELEM", 
		i2cAddress	   	: 0x26, 
		registerAddress	: 0xAA
	};

	// Read register CFG_RSENSE1_R
	float registerData = _coms.get_register_data(rReg);
	_displayData.display_register_as_float(rReg, registerData);

	// Write register CTRL_UPDATE_TELEM
	_coms.send_data(wReg, 0x0001);
}

void RunningState::exit(){
	Serial.println("Exiting RunningState");
}