#pragma once

#include "State.h"
#include "ControlFan.h"
#include "MpptCommunication.h"
#include "DisplayRegisterData.h"

/**
 * @brief Charging state class which is active when MPPT is charging the batteries.
 */
class ChargingState : public State
{
public:
	/**
	 * @brief Construct a new Charging State instance.
	 */
	ChargingState();
	/**
	 * @brief Destroy the Charging State instance.
	 */
	virtual ~ChargingState();

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

private:
	ControlFan _fan; 				  /*< Instance to control the fan. 	  */	
	MpptCommunication _coms;		  /*< Instance of MpptCommunication.  */
	DisplayRegisterData _display_data; /*< Display register data instance. */
};