#include "DisplayRegisterData.h"

#include <sstream>

DisplayRegisterData::DisplayRegisterData() {

}

DisplayRegisterData::~DisplayRegisterData() {

}

void DisplayRegisterData::display_register_as_float(SReadRegInfo reg, float value) {
    std::string printString = "Register: " + reg.name + " value: " + float_to_string(value) + "\n";
	Serial.print(printString.c_str());
}

std::string DisplayRegisterData::float_to_string(float value) {
    std::ostringstream ss;
	ss << value;
	std::string str(ss.str());

	return str;
}