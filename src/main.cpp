#include "StateMachine.h"
#include "State.h"

#include <Arduino.h>																						

void setup() {
	Serial.begin(9600);
	Serial.print("\n\n Start \n\n");

	StateMachine::instance().start();
	StateMachine::instance().change_state(EState::RUNNING);
}

void loop() {
	StateMachine::instance().update();
}
