#include "DisplayRegisterData.h"
#include "MpptCommunication.h"
#include "StateMachine.h"
#include "State.h"

#include <Arduino.h>																						

std::string toString(float value) {
	
}	

void setup() {
	Serial.begin(9600);
	Serial.print("\n\n");

	StateMachine::instance().start();
}

void loop() {
	StateMachine::instance().update();

	SRegister reg = {name: "CFG_RSENSE1_R", size: 2, devisionSize: 100, i2cAddress: 0x10, registerAddress: 0x28};

	MpptCommunication coms;
	float registerData = coms.get_register_data(reg);

	DisplayRegisterData display;
	display.display_register_as_float(reg, registerData);

	delay(500);
}
