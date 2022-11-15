#include "MpptCommunication.h"

#include <Arduino.h>

#define SDA_PIN 21
#define SDL_PIN 22
#define I2C_CLOCK_SPEED 100000

MpptCommunication::MpptCommunication() : 
	_wire(new TwoWire(0)) 
{
	pinMode(SDA_PIN, OUTPUT);
	pinMode(SDL_PIN, OUTPUT);
	_wire->begin(SDA_PIN, SDL_PIN, I2C_CLOCK_SPEED);
}

MpptCommunication::~MpptCommunication() {
	delete _wire;
}

void MpptCommunication::send_data(uint16_t adress, const uint8_t *data, unsigned size) {

}

float MpptCommunication::uint8ToFloat(uint8_t* buffer, size_t size, unsigned divisionValue) {									
	float value = 0;

	if (size == 1) {																		
		value = float(buffer[0]);															
	}																						
	if (size == 2) {																		
		value = float((buffer[1] << 8) + buffer[0]); 										
	} else if (size == 4) {																	
		value = float((buffer[3] << 24) + (buffer[2] << 16) + (buffer[1] << 8) + buffer[0]); 
	} 				

	return value / divisionValue; 															
}

float MpptCommunication::get_register_data(SRegister reg) {
	uint8_t* buffer = new uint8_t[reg.size];
	recieve_bytes(buffer, reg.i2cAddress, reg.registerAddress, reg.size);
	float value = uint8ToFloat(buffer, reg.size, 100);
	free(buffer);
	return value;
}

void MpptCommunication::recieve_bytes(uint8_t* buffer, uint16_t i2cAddress, uint16_t registerAddress, size_t size) {
	_wire->beginTransmission(i2cAddress);
	_wire->write(registerAddress);
	_wire->endTransmission();
	_wire->requestFrom(i2cAddress, size);

	if (_wire->available()){
		_wire->readBytes(buffer, size);
	}
}