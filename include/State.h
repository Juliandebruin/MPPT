#pragma once

/**
 * @brief Enum for all enums of the statemachine.
 */
typedef enum
{
	INVALID,		/*< Invalid		   state */
	INITIALISATION, /*< Initialisation state */
	RUNNING, 		/*< Running 	   state */
	CHARGING, 		/*< Charging       state */
	ERROR 			/*< Error          state */
} EState;

/**
 * @brief Abstract state class
 */
class State
{
public:
	/**
	 * @brief Destroy the State instance.
	 */
	virtual ~State() = default;
	/**
	 * @brief Function is called when state is entered.
	 */
	virtual void enter()  = 0;
	/**
	 * @brief Function contains the update loop of the state.
	 */
	virtual void update() = 0;
	/**
	 * @brief Function is called when state is exited.
	 */
	virtual void exit()   = 0;
};