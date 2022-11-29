class ControlFan
{
public:
    /**
     * @brief Construct a new Control Fan instance.
     */
    ControlFan();
    /**
     * @brief Destroy the Control Fan instance.
     */
    virtual ~ControlFan();
    /**
     * @brief Set the Fan Speed.
     * 
     * @param speed Speed of the fan in integers.
     */
    void setFanSpeed(int speed);
};