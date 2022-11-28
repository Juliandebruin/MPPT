#pragma once

#include "State.h"

/**
 * @brief Initialisation state class which is active when MPPT is initializing on start up.
 */
class InitialisationState : public State
{
public:
	/**
	 * @brief Construct a new Initialisation State instance.
	 */
	InitialisationState();
	/**
	 * @brief Destroy the Initialisation State instance.
	 */
	virtual ~InitialisationState();

	/**
	 * @brief Function is called when state is entered.
	 */
	virtual void enter()  override;
	/**
	 * @brief Function contains the update loop of the state.
	 */
	virtual void update() override;
	/**
	 * @brief Function is called when state is exited.
	 */
	virtual void exit()   override;
};