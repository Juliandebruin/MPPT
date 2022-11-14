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

}

void MpptCommunication::send_data(uint16_t adress, const uint8_t *data, unsigned size) {

}

uint8_t* MpptCommunication::recieve_data(const uint16_t i2cAddress, const uint16_t registerAddress, size_t size) {
	uint8_t *buffer = nullptr;

	Wire.beginTransmission(i2cAddress);
	Wire.write(registerAddress);
	Wire.endTransmission();
	Wire.requestFrom(i2cAddress, size);

	if (Wire.available()){
		Wire.readBytes(buffer, size);
	}

	return buffer;
}