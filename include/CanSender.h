#pragma once

#include <string>

/**
 * @brief Class to send CAN messages over the CAN bus.
 */
class CanSender
{
public:
	/**
	 * @brief Construct a new Can Sender instance.
	 */
	CanSender();
	/**
	 * @brief Destroy the Can Sender instance.
	 */
	virtual ~CanSender();

	/**
	 * @brief Send a message to the CAN bus.
	 * 
	 * @param id Id used to as address by can bus.
	 * @param message Message to send.
	 */
	void send_message(uint16_t id, std::string message);
};