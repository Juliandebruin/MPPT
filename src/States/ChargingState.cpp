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

	SWriteRegInfo chargeWrite = {
		name		   	: "CTRL_CHRG_EN", 
		i2cAddress	   	: 0x10, 
		registerAddress	: 0x23
	};

	_fan.set_fan_speed(1);
	_coms.send_data(chargeWrite, 0x01);
}

void ChargingState::update(){
	Serial.println("Updating ChargingState");

	SReadRegInfo teleRead = {
		name		   	: "TELE_VIN", 
		size		   	: EDataSize::WORD, 
		devisionSize   	: 100, 
		i2cAddress	   	: 0x10,
		registerAddress	: 0x0E
	};

	float vin = _coms.get_register_data(teleRead);
	_display_data.display_register_as_float(teleRead, vin);

	std::string message = _display_data.float_to_string(vin) + "V";
	Serial.println(message.c_str());

	_can_coms.send_message(0x08, message);

	std::pair<long, std::string> package = _can_coms.receive_message();
	Serial.print("ID: 0x");
	Serial.print(package.first, HEX);
	Serial.print(" Message: ");
	Serial.println(package.second.c_str());
}

void ChargingState::exit(){
	Serial.println("Exiting ChargingState");
}