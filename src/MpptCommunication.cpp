#include "MpptCommunication.h"

#include <Arduino.h>

#define SDA_PIN 21
#define SDL_PIN 22
#define I2C_CLOCK_SPEED 100000

MpptCommunication::MpptCommunication() : 
	_wire(&Wire),
	_typeToSize {
		{EDataSize::BYTE	, 1},
		{EDataSize::WORD	, 2},
		{EDataSize::LONGWORD, 4}
	},
	_read_registers {
		{EReadRegisters::TELE_TBAT       , {"TELE_TBAT"       , EDataSize::WORD    ,   10, I2C_ADDRESS, 0x00}},
		{EReadRegisters::TELE_POUT       , {"TELE_POUT"       , EDataSize::WORD    ,  100, I2C_ADDRESS, 0x02}},
		{EReadRegisters::TELE_PIN        , {"TELE_PIN"        , EDataSize::WORD    , 1000, I2C_ADDRESS, 0x04}},
		{EReadRegisters::TELE_EFF        , {"TELE_EFF"        , EDataSize::WORD    ,  100, I2C_ADDRESS, 0x06}},
		{EReadRegisters::TELE_IOUT       , {"TELE_IOUT"       , EDataSize::WORD    , 1000, I2C_ADDRESS, 0x08}},
		{EReadRegisters::TELE_IIN        , {"TELE_IIN"        , EDataSize::WORD    , 1000, I2C_ADDRESS, 0x0A}},
		{EReadRegisters::TELE_VBAT       , {"TELE_VBAT"       , EDataSize::WORD    ,  100, I2C_ADDRESS, 0x0C}},
		{EReadRegisters::TELE_VIN        , {"TELE_VIN"        , EDataSize::WORD    ,  100, I2C_ADDRESS, 0x0E}},
		{EReadRegisters::TELE_VINR       , {"TELE_VINR"       , EDataSize::WORD    ,  100, I2C_ADDRESS, 0x10}},
		{EReadRegisters::STAT_CHARGER    , {"STAT_CHARGER"    , EDataSize::BYTE    ,    1, I2C_ADDRESS, 0x12}},
		{EReadRegisters::STAT_SYSTEM     , {"STAT_SYSTEM"     , EDataSize::BYTE    ,    1, I2C_ADDRESS, 0x13}},
		{EReadRegisters::STAT_SUPPLY     , {"STAT_SUPPLY"     , EDataSize::BYTE    ,    1, I2C_ADDRESS, 0x14}},
		{EReadRegisters::STAT_TS0_REMAIN , {"STAT_TS0_REMAIN" , EDataSize::BYTE    ,    1, I2C_ADDRESS, 0x15}},
		{EReadRegisters::STAT_TS1_REMAIN , {"STAT_TS1_REMAIN" , EDataSize::BYTE    ,    1, I2C_ADDRESS, 0x16}},
		{EReadRegisters::STAT_TS2_REMAIN , {"STAT_TS2_REMAIN" , EDataSize::BYTE    ,    1, I2C_ADDRESS, 0x17}},
		{EReadRegisters::STAT_TS3_REMAIN , {"STAT_TS3_REMAIN" , EDataSize::BYTE    ,    1, I2C_ADDRESS, 0x18}},
		{EReadRegisters::STAT_CHRG_FAULTS, {"STAT_CHRG_FAULTS", EDataSize::BYTE    ,    1, I2C_ADDRESS, 0x19}},
		{EReadRegisters::STAT_VERSION    , {"STAT_VERSION"    , EDataSize::BYTE    ,    1, I2C_ADDRESS, 0x1A}},
		{EReadRegisters::STAT_BOOT_CRC   , {"STAT_BOOT_CRC"   , EDataSize::WORD    ,    1, I2C_ADDRESS, 0x1C}},
		{EReadRegisters::STAT_CFG_CRC    , {"STAT_CFG_CRC"    , EDataSize::WORD    ,    1, I2C_ADDRESS, 0x1E}}
	}
{
	pinMode(SDA_PIN, OUTPUT);
	pinMode(SDL_PIN, OUTPUT);
	_wire->begin(SDA_PIN, SDL_PIN, I2C_CLOCK_SPEED);
}

MpptCommunication::~MpptCommunication() {
	delete _wire;
}

float MpptCommunication::uint8ToFloat(uint8_t* buffer, size_t size, unsigned divisionValue) {
	float value = 0;

	if (size == 1) {
		value = float(buffer[0]);
	} else if (size == 2) {
		value = float((buffer[1] << 8) + buffer[0]);
	} else if (size == 4) {
		value = float((buffer[3] << 24) + (buffer[2] << 16) + (buffer[1] << 8) + buffer[0]);
	}

	return value / divisionValue;
}

void MpptCommunication::send_data(SWriteRegInfo reg, uint16_t data) {
	_wire->beginTransmission(reg.i2cAddress);
	_wire->write(reg.registerAddress);
	_wire->write(data);
	_wire->endTransmission();
}

float MpptCommunication::get_register_data(SReadRegInfo reg) {
	size_t size = _typeToSize[reg.size];
	uint8_t* buffer = new uint8_t[size];
	recieve_bytes(buffer, reg.i2cAddress, reg.registerAddress, size);
	float value = uint8ToFloat(buffer, size, reg.devisionSize);
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