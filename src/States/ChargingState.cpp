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
}

void ChargingState::update(){
	Serial.println("Updating ChargingState");

	SRegisterInfo s_Pin = _coms._read_registers.find(ERegisters::TELE_PIN)->second;
	float f_Pin = _coms.get_register_data(s_Pin);
	_display_data.display_register_value(s_Pin, f_Pin);
	_can_coms.send_message(0x21, _display_data.float_to_string(f_Pin));

	SRegisterInfo s_Pout = _coms._read_registers.find(ERegisters::TELE_POUT)->second;
	float f_Pout = _coms.get_register_data(s_Pout);
	_display_data.display_register_value(s_Pout, f_Pout);
	_can_coms.send_message(0x22, _display_data.float_to_string(f_Pout));
}

void ChargingState::exit(){
	Serial.println("Exiting ChargingState");
}