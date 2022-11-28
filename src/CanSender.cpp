#include "CanSender.h"

#include <CAN.h>

CanSender::CanSender() {
	CAN.begin(500E3);
}

CanSender::~CanSender() {

}

void CanSender::send_message(uint16_t id, std::string message) {
	CAN.beginPacket(id);
	CAN.write('h');
	CAN.write('e');
	CAN.write('l');
	CAN.write('l');
	CAN.write('o');
	CAN.endPacket();
}