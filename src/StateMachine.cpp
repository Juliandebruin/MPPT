#include "States\InitializationState.h"
#include "States\RunningState.h"
#include "States\ChargingState.h"
#include "States\ErrorState.h"
#include "StateMachine.h"
#include "State.h"

StateMachine::StateMachine() : 
	_all_states({
	   	{INITIALISATION, new InitialisationState},
		{RUNNING	   , new RunningState		},
		{CHARGING	   , new ChargingState		},
		{ERROR		   , new ErrorState			}
	}),
	_current_state({INVALID, nullptr})
{	
}

StateMachine::~StateMachine()
{
	delete _all_states[INITIALISATION];
	delete _all_states[RUNNING 		 ];
	delete _all_states[CHARGING		 ];
	delete _all_states[ERROR		 ];
}

void StateMachine::start() {
	_current_state = {INITIALISATION, _all_states[INITIALISATION]};
	_current_state.second->enter();
}

void StateMachine::update() {
	if (_current_state.first != INVALID) {
		_current_state.second->update();
	}
}

void StateMachine::change_state(EState newState) {
	if (_current_state.first != INVALID) {
		_current_state.second->exit();
	}
	
	_current_state = {newState, _all_states[newState]};
	_current_state.second->enter();
}

EState StateMachine::get_current_state() {
	return _current_state.first;
}