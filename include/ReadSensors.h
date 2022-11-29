#pragma once

#include <OneWire.h>
#include <DallasTemperature.h>

/**
 * @brief Read the sensors values of temprature sensors of MPPT
 */
class ReadSensors 
{
public:
    /**
     * @brief Construct a new Read Sensors instance.
     */
    ReadSensors();
    /**
     * @brief Destroy the Read Sensors instance.
     */
    virtual ~ReadSensors();	

    /**
     * @brief Get the temperature of one of the two sensors on the circuit board.
     * 
     * @param sensorId Define which sensor to read.
     * @return float Returns the temperature of the sensor.
     */
    float get_temperature(int sensorId);

private:
    OneWire _one_wire;			/*< OneWire object for one wire communication. 		  */
	DallasTemperature _sensors;	/*< DallasTemperature object for temperature sensors. */
};