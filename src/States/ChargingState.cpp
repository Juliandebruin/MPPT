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
	//Serial.println("Entering ChargingState");

	SWriteRegInfo chargeWrite = {
		name		   	: "CTRL_CHRG_EN", 
		i2cAddress	   	: 0x10, 
		registerAddress	: 0x23
	};

	_fan.set_fan_speed(100);
	_coms.send_data(chargeWrite, 0x01);
}

void ChargingState::update(){
	// Serial.println("Updating ChargingState");

	SReadRegInfo TELE_VINR = {
		name		   	: "TELE_VINR", 
		size		   	: EDataSize::WORD, 
		devisionSize   	: 100, 
		i2cAddress	   	: 0x10,
		registerAddress	: 0x10
	};
	
	SReadRegInfo TELE_VBAT = {
		name		   	: "TELE_VBAT", 
		size		   	: EDataSize::WORD, 
		devisionSize   	: 100, 
		i2cAddress	   	: 0x10,
		registerAddress	: 0x0C
	};

	SReadRegInfo TELE_IIN = {
		name		   	: "TELE_IIN", 
		size		   	: EDataSize::WORD, 
		devisionSize   	: 1000, 
		i2cAddress	   	: 0x10,
		registerAddress	: 0x0A
	};

	SReadRegInfo TELE_IOUT = {
		name		   	: "TELE_IOUT", 
		size		   	: EDataSize::WORD, 
		devisionSize   	: 1000, 
		i2cAddress	   	: 0x10,
		registerAddress	: 0x08
	};

	float vinr = _coms.get_register_data(TELE_VINR);
	float vbat = _coms.get_register_data(TELE_VBAT);
	float iin  = _coms.get_register_data(TELE_IIN );
	float iout = _coms.get_register_data(TELE_IOUT);
	
	float pin  = vinr * iin;
	float pout = vbat * iout;
	float eff  = (pout / pin) * 100;
	float ploss = pin - pout;
	

	std::string printTelem = 
	"VINR: "   + _display_data.float_to_string(vinr ) + "V" +
	" IIN: "   + _display_data.float_to_string(iin  ) + "A" +
	" PIN: "   + _display_data.float_to_string(pin  ) + "W" +
	" VBAT: "  + _display_data.float_to_string(vbat ) + "V" +
	" IOUT: "  + _display_data.float_to_string(iout ) + "A" +
	" POUT: "  + _display_data.float_to_string(pout ) + "W" +
	" EFF: "   + _display_data.float_to_string(eff  ) + "%" +
	" PLOSS: " + _display_data.float_to_string(ploss) + "W";

	Serial.println(printTelem.c_str());
 
	// _can_coms.send_message(0x08, eff);

	// std::pair<long, std::string> package = _can_coms.receive_message();
	// Serial.print("ID: 0x");
	// Serial.print(package.first, HEX);
	// Serial.print(" Message: ");
	// Serial.println(package.second.c_str());
}

void ChargingState::exit(){
	Serial.println("Exiting ChargingState");
}