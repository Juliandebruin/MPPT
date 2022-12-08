#include "States/ChargingState.h"

#include <Arduino.h>
#include <utility>

ChargingState::ChargingState() :
	_fan(ControlFan()),
	_can_coms(CanComs()),
	_coms(MpptCommunication()),
	_display_data(DisplayRegisterData()) 
{

}

ChargingState::~ChargingState() {

}

void ChargingState::enter(){
	Serial.println("Entering ChargingState");

	SRegisterInfo chargeWrite = {
		name		   	: "CTRL_CHRG_EN", 
		settings	   	: EReadWrite::WRITE,
		size		   	: EDataSize::BYTE,
		devisionSize	: 1,
		i2cAddress	   	: 0x10, 
		registerAddress	: 0x23
	};

	_fan.set_fan_speed(100);
	_coms.send_data(chargeWrite, 0x01);
}

void ChargingState::update(){
	Serial.println("Updating ChargingState");

	for (int i = 0; i < _coms._read_registers.size(); i++) {
		SRegisterInfo reg = _coms._read_registers.find(i)->second;
		if (reg.settings == EReadWrite::READ) {
			float value = _coms.get_register_data(reg);
			_display_data.display_register_value(reg, value);
		}
	}
}

void ChargingState::exit(){
	Serial.println("Exiting ChargingState");
}