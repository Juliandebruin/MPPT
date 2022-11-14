#include "StateMachine.h"
#include "State.h"

#include <Arduino.h>

void setup() {
	Serial.begin(9600);
	Serial.print("\n\n");

	StateMachine::instance().start();
	StateMachine::instance().update();
}

void loop() {
	StateMachine::instance().change_state(EState::RUNNING);
	StateMachine::instance().update();
	StateMachine::instance().change_state(EState::CHARGING);
	StateMachine::instance().update();
	
	delay(2000);
}
