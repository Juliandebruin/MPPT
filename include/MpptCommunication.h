#pragma once

#include <Arduino.h>
#include <Wire.h>
#include <map>

/**
 * @brief Enum which contains all the possible data sizes of a value.
 */
enum EDataSize {
	BYTE,
	WORD,
	LONGWORD
};

/**
 * @brief Struct which holds information about a register.
 */
struct SRegister {
	std::string name;			/*< Name of register. 			  */
	EDataSize size;				/*< Size of register. 			  */
	unsigned devisionSize;		/*< Devision size of register. 	  */
	uint16_t i2cAddress;		/*< I2C address of register. 	  */
	uint16_t registerAddress;	/*< Register address of register. */
};

/**
 * @brief Class which handles sending and recieving data to the MPPT.
 */
class MpptCommunication
{
public:
	/**
	 * @brief Construct a new MpptCommunication instance.
	 */
	MpptCommunication();
	/**
	 * @brief Destroy the MpptCommunication instance.
	 */
	virtual ~MpptCommunication();


	void send_data(uint16_t adress, const uint8_t *data, unsigned size);

	/**
	 * @brief Transform a uint8_t pointer to float and dive it by a division value.
	 * 
	 * @param buffer Buffer of unsigned 8 bit pointer.
	 * @param size Size of the buffer in bytes.
	 * @param divisionValue Value by which the float will be divided.
	 * @return Returns the transformed float.
	 */
	float uint8ToFloat(uint8_t* buffer, size_t size, unsigned divisionValue);

	/**
	 * @brief Retrieve a message from the MPPT.
	 * 
	 * @param reg Struct which contains the register information.
	 * @return Float value of the register.
	 */
	float get_register_data(SRegister reg);

private:
	/**
	 * @brief Recieve bytes from the MPPT.
	 * 
	 * @param i2cAddress Address of i2c slave to acces register.
	 * @param registerAddress Addres which register to access.
	 * @param size Size of data to recieve.
	 */
	void recieve_bytes(uint8_t* buffer, uint16_t i2cAddress, uint16_t registerAddress, size_t size);

private:
	TwoWire *_wire; 						 /*< Pointer to the TwoWire instance. 					    */
	std::map<EDataSize, size_t> _typeToSize; /*< Map which is used to transform string size to a value. */
};