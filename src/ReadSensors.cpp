#include "ReadSensors.h"

#define ONE_WIRE_BUS 16
#define NUMBER_OF_SENSORS 2

ReadSensors::ReadSensors() : 
    _one_wire(ONE_WIRE_BUS),
	_sensors(&_one_wire)
{
    _sensors.begin();
}

ReadSensors::~ReadSensors() {

}

float ReadSensors::get_temperature(int sensorId) {
    if (sensorId >= 0 && sensorId < NUMBER_OF_SENSORS) {
        return _sensors.getTempCByIndex(sensorId);
    } else {
        return -1.0f;
    }
}