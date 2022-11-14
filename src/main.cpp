#include "MpptCommunication.h"
#include "StateMachine.h"
#include "State.h"

#include <string>
#include <sstream>
#include <iostream>
#include <Arduino.h>

#define INT_TO_FLOAT(value, divisionValue) (float(value)/divisionValue)
#define UINT8P_TO_UINT16(buf) ((buf[1] << 8) + buf[0])
#define UINT8P_TO_UINT32(buf) ((buf[3] << 24) + (buf[2] << 16) + (buf[1] << 8) + buf[0])

struct option {
	std::string name;
	size_t size;
	uint16_t i2cAddress;
	uint16_t registerAddress;
};

std::string toString(float value) {
	std::ostringstream ss;
	ss << value;
	std::string str(ss.str());

	return str;
}

void setup() {
	Serial.begin(9600);
	Serial.print("\n\n");

	StateMachine::instance().start();
}

void loop() {
	StateMachine::instance().update();

	uint8_t* buffer_rsense1 = nullptr;
	option opt = {name: "CFG_RSENSE1_R", size: 2, i2cAddress: 0x10, registerAddress: 0x28};
	
	MpptCommunication *coms = new MpptCommunication;
	buffer_rsense1 = coms->recieve_data(opt.i2cAddress, opt.registerAddress, opt.size);

	uint16_t rsense1 = UINT8P_TO_UINT16(buffer_rsense1);
	float CFG_RSENSE1_R = INT_TO_FLOAT(rsense1, 1000);

	std::string str = "Buffer: " + opt.name + ": " + toString(CFG_RSENSE1_R);
	Serial.print(str.c_str());

	delay(5000);
}
