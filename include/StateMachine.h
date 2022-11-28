#pragma once

#include "State.h"

#include <map>
#include <utility>

/**
 * @brief State machine class which handles the state transitions.
 */
class StateMachine
{
public:
	/**
	 * @brief Creates static instance of StateMachine,
	 * which can be accessed from anywhere and only exists once.
	 * 
	 * @return static StateMachine instance
	 */
	static StateMachine &instance()
	{
		static StateMachine INSTANCE;
		return INSTANCE;
	}
	/**
	 * @brief Function starts the state machine.
	 */
	void start();
	/**
	 * @brief Function calles update function of state.
	 */
	void update();
	/**
	 * @brief Function switches states and calles exit and enter functions.
	 * 
	 * @param newState The new state to switch to.
	 */
	void change_state(EState newState);
	/**
	 * @brief Get the current state.
	 * 
	 * @return Returns EState.
	 */
	EState get_current_state();

private:
	/**
	 * @brief Construct a new StateMachine instance.
	 */
	StateMachine();
	/**
	 * @brief Destroy the State Machine instance.
	 */
	virtual ~StateMachine();

	std::map <EState, State *> _all_states;		/*< Map to acess all states. */
	std::pair<EState, State *> _current_state;  /*< The current state.		 */
};