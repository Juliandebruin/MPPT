#include "States/ChargingState.h"
#include "CanSender.h"

#include <Arduino.h>

ChargingState::ChargingState() :
	_coms(MpptCommunication()),
	_displayData(DisplayRegisterData()) 
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
	_displayData.display_register_as_float(teleRead, vin);

	std::string message = _displayData.float_to_string(vin) + "V";
	Serial.println(message.c_str());

	CanSender sender;
	sender.send_message(0x08, message);
}

void ChargingState::exit(){
	Serial.println("Exiting ChargingState");
}