#include "MpptCommunication.h"

#include <string>

/**
 * @brief Class which handles displaying register data.
 */
class DisplayRegisterData
{
public:
    /**
     * @brief Construct a new Display Register Data instance.
     */
    DisplayRegisterData();
    /**
     * @brief Destroy the Display Register Data instance.
     */
    virtual ~DisplayRegisterData();
    /**
     * @brief Display the register data on the serial monitor as float.
     * 
     * @param reg Register information.
     * @param value Value of register as float.
     */
    void display_register_as_float(SRegister reg, float value);

private:
    /**
     * @brief Transforms a float into string value.
     * 
     * @param value Value to transform.
     * @return std::string transformed value.
     */
    std::string float_to_string(float value);
};