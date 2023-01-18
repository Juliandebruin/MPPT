#include "CanComs.h"

#include <CAN.h>

CanComs::CanComs() {
	CAN.begin(500E3);
}

CanComs::~CanComs() {

}

void CanComs::send_message(uint16_t id, std::string message) {
	CAN.beginPacket(id);
	for (int i = 0; i < message.length(); i++){
		CAN.write(message[i]);
	}
	CAN.endPacket();
}

std::pair<long, std::string> CanComs::receive_message() {
	std::pair<long, std::string> package;
	int packetSize = CAN.parsePacket();

	if (packetSize || CAN.packetId()) {
		package.first = CAN.packetId();

		if (!CAN.packetRtr()) {
			while (CAN.available())	{
				package.second += (char)CAN.read();
			}
		}
	}

	return package;
}