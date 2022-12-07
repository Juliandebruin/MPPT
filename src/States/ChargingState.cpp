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
	// _coms.send_data(chargeWrite, 0x01);
}

void ChargingState::update(){
	Serial.println("Updating ChargingState");

	// SReadRegInfo readReg = {"TELE_POUT", EDataSize::WORD, 100, I2C_ADDRESS, 0x02};
	// float value = _coms.get_register_data(readReg);
	// _display_data.display_register_value(readReg, value);

	for (int i = 0; i < _coms._read_registers.size(); i++) {
		// SReadRegInfo reg = _coms._read_registers.find(i)->second;
		// float value = _coms.get_register_data(reg);
		// _display_data.display_register_value(reg, value);
		// delay(300);
	}
}

void ChargingState::exit(){
	Serial.println("Exiting ChargingState");
}