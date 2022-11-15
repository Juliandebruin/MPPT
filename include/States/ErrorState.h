#include "State.h"

/**
 * @brief Error state class which is active an error occurs in the MPPT.
 */
class ErrorState : public State
{
public:
	/**
	 * @brief Construct a new Error State instance.
	 */
	ErrorState();
	/**
	 * @brief Destroy the Error State instance.
	 */
	virtual ~ErrorState();

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