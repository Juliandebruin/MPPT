#include "CanSender.h"

#include <CAN.h>

CanSender::CanSender() {
	CAN.begin(100E3);
}

CanSender::~CanSender() {

}

void CanSender::send_message(uint16_t id, std::string message) {
	CAN.beginPacket(id);
	for (int i = 0; i < message.length(); i++){
		CAN.write(message[i]);
	}
	CAN.endPacket();
}