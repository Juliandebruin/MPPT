#pragma once

#include <Arduino.h>
#include <Wire.h>

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
	 * @brief Recieve data from the MPPT.
	 * 
	 * @param i2cAddress Address of i2c slave to acces register.
	 * @param registerAddress Addres which register to access.
	 * @param size Size of data to recieve.
	 * @return Retruns byte or bytes depeiding on the size in uint8_t*.
	 */
	uint8_t* recieve_data(const uint16_t i2cAddress, const uint16_t registerAddress, size_t size);

private:
	TwoWire *_wire;
};