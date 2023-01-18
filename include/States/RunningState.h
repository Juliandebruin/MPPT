#pragma once

#include "State.h"
#include "CanComs.h"
#include "ReadSensors.h"
#include "MpptCommunication.h"
#include "DisplayRegisterData.h"

/**
 * @brief Running state class which is active when MPPT is running but not charging the batteries.
 */
class RunningState : public State
{
public:
	/**
	 * @brief Construct a new Running State instance.
	 */
	RunningState();
	/**
	 * @brief Destroy the Running State instance.
	 */
	virtual ~RunningState();

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
	CanComs _can_coms;			   	   /*< Instance of CanComs. 										  */
	ReadSensors _sensors;			   /*< Instance torRead the temperature sensors on the circuit board. */
	MpptCommunication _coms;		   /*< Instance of MpptCommunication.  								  */
	DisplayRegisterData _display_data; /*< Display register data instance. 								  */
};