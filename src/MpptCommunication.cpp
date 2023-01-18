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
		{ERegisters::TELE_TBAT        , {"TELE_TBAT"        , EReadWrite::READ 	    , EDataSize::WORD,   10, I2C_ADDRESS, 0x00}},
		{ERegisters::TELE_POUT        , {"TELE_POUT"        , EReadWrite::READ 	    , EDataSize::WORD,  100, I2C_ADDRESS, 0x02}},
		{ERegisters::TELE_PIN         , {"TELE_PIN"         , EReadWrite::READ 	    , EDataSize::WORD, 1000, I2C_ADDRESS, 0x04}},
		{ERegisters::TELE_EFF         , {"TELE_EFF"         , EReadWrite::READ 	    , EDataSize::WORD,  100, I2C_ADDRESS, 0x06}},
		{ERegisters::TELE_IOUT        , {"TELE_IOUT"        , EReadWrite::READ 	    , EDataSize::WORD, 1000, I2C_ADDRESS, 0x08}},
		{ERegisters::TELE_IIN         , {"TELE_IIN"         , EReadWrite::READ 	    , EDataSize::WORD, 1000, I2C_ADDRESS, 0x0A}},
		{ERegisters::TELE_VBAT        , {"TELE_VBAT"        , EReadWrite::READ 	    , EDataSize::WORD,  100, I2C_ADDRESS, 0x0C}},
		{ERegisters::TELE_VIN         , {"TELE_VIN"         , EReadWrite::READ 	    , EDataSize::WORD,  100, I2C_ADDRESS, 0x0E}},
		{ERegisters::TELE_VINR        , {"TELE_VINR"        , EReadWrite::READ 	    , EDataSize::WORD,  100, I2C_ADDRESS, 0x10}},
		{ERegisters::STAT_CHARGER     , {"STAT_CHARGER"     , EReadWrite::READ 	    , EDataSize::BYTE,    1, I2C_ADDRESS, 0x12}},
		{ERegisters::STAT_SYSTEM      , {"STAT_SYSTEM"      , EReadWrite::READ 	    , EDataSize::BYTE,    1, I2C_ADDRESS, 0x13}},
		{ERegisters::STAT_SUPPLY      , {"STAT_SUPPLY"      , EReadWrite::READ 	    , EDataSize::BYTE,    1, I2C_ADDRESS, 0x14}},
		{ERegisters::STAT_TS0_REMAIN  , {"STAT_TS0_REMAIN"  , EReadWrite::READ 	    , EDataSize::BYTE,    1, I2C_ADDRESS, 0x15}},
		{ERegisters::STAT_TS1_REMAIN  , {"STAT_TS1_REMAIN"  , EReadWrite::READ 	    , EDataSize::BYTE,    1, I2C_ADDRESS, 0x16}},
		{ERegisters::STAT_TS2_REMAIN  , {"STAT_TS2_REMAIN"  , EReadWrite::READ 	    , EDataSize::BYTE,    1, I2C_ADDRESS, 0x17}},
		{ERegisters::STAT_TS3_REMAIN  , {"STAT_TS3_REMAIN"  , EReadWrite::READ 	    , EDataSize::BYTE,    1, I2C_ADDRESS, 0x18}},
		{ERegisters::STAT_CHRG_FAULTS , {"STAT_CHRG_FAULTS" , EReadWrite::READ 	    , EDataSize::BYTE,    1, I2C_ADDRESS, 0x19}},
		{ERegisters::STAT_VERSION     , {"STAT_VERSION"     , EReadWrite::READ 	    , EDataSize::BYTE,    1, I2C_ADDRESS, 0x1A}},
		{ERegisters::STAT_BOOT_CRC    , {"STAT_BOOT_CRC"    , EReadWrite::READ 	    , EDataSize::WORD,    1, I2C_ADDRESS, 0x1C}},
		{ERegisters::STAT_CFG_CRC     , {"STAT_CFG_CRC"     , EReadWrite::READ 	    , EDataSize::WORD,    1, I2C_ADDRESS, 0x1E}},
		{ERegisters::CTRL_WRT_TO_BOOT , {"CTRL_WRT_TO_BOOT" , EReadWrite::READ_WRITE, EDataSize::BYTE,    1, I2C_ADDRESS, 0x20}},
		{ERegisters::CTRL_EE_WRT_EN   , {"CTRL_EE_WRT_EN"   , EReadWrite::WRITE	    , EDataSize::BYTE,    1, I2C_ADDRESS, 0x21}},
		{ERegisters::CTRL_HALT_STARTUP, {"CTRL_HALT_STARTUP", EReadWrite::WRITE	    , EDataSize::BYTE,    1, I2C_ADDRESS, 0x22}},
		{ERegisters::CTRL_CHRG_EN     , {"CTRL_CHRG_EN"     , EReadWrite::WRITE	    , EDataSize::BYTE,    1, I2C_ADDRESS, 0x23}},
		{ERegisters::CTRL_RESTART_CHIP, {"CTRL_RESTART_CHIP", EReadWrite::WRITE	    , EDataSize::BYTE,    1, I2C_ADDRESS, 0x24}},
		{ERegisters::CTRL_RESET_FLAG  , {"CTRL_RESET_FLAG"  , EReadWrite::WRITE	    , EDataSize::BYTE,    1, I2C_ADDRESS, 0x25}},
		{ERegisters::CTRL_UPDATE_TELEM, {"CTRL_UPDATE_TELEM", EReadWrite::READ_WRITE, EDataSize::BYTE,    1, I2C_ADDRESS, 0x26}},
		{ERegisters::CFG_RSENSE1	  , {"CFG_RSENSE1"      , EReadWrite::READ		, EDataSize::WORD,  100, I2C_ADDRESS, 0x28}},
		{ERegisters::CFG_RIMON_OUT	  , {"CFG_RIMON_OUT"    , EReadWrite::READ		, EDataSize::WORD,  100, I2C_ADDRESS, 0x2A}},
		{ERegisters::CFG_RSENSE2	  , {"CFG_RSENSE2"      , EReadWrite::READ		, EDataSize::WORD,  100, I2C_ADDRESS, 0x2C}},
		{ERegisters::CFG_RDACO		  , {"CFG_RDACO"        , EReadWrite::READ		, EDataSize::WORD,  100, I2C_ADDRESS, 0x2E}},
		{ERegisters::CFG_RFBOUT1	  , {"CFG_RFBOUT1"      , EReadWrite::READ		, EDataSize::WORD,   10, I2C_ADDRESS, 0x30}},
		{ERegisters::CFG_RFBOUT2	  , {"CFG_RFBOUT2"      , EReadWrite::READ		, EDataSize::WORD,  100, I2C_ADDRESS, 0x32}},
		{ERegisters::CFG_RDACI		  , {"CFG_RDACI"        , EReadWrite::READ		, EDataSize::WORD,  100, I2C_ADDRESS, 0x34}},
		{ERegisters::CFG_RFBIN2	  	  , {"CFG_RFBIN2"       , EReadWrite::READ		, EDataSize::WORD,  100, I2C_ADDRESS, 0x36}},
		{ERegisters::CFG_RFBIN1		  , {"CFG_RFBIN1"       , EReadWrite::READ		, EDataSize::WORD,   10, I2C_ADDRESS, 0x38}},
		{ERegisters::CFG_INIT_CHRG_EN , {"CFG_INIT_CHRG_EN" , EReadWrite::READ_WRITE, EDataSize::BYTE,    1, I2C_ADDRESS, 0x3A}},
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

void MpptCommunication::send_data(SRegisterInfo reg, uint16_t data) {
	_wire->beginTransmission(reg.i2cAddress);
	_wire->write(reg.registerAddress);
	_wire->write(data);
	_wire->endTransmission();
}

float MpptCommunication::get_register_data(SRegisterInfo reg) {
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