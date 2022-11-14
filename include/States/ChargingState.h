#include "State.h"

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
};