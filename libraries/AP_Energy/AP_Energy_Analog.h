/// -*- tab-width: 4; Mode: C++; c-basic-offset: 4; indent-tabs-mode: nil -*-

#ifndef __AP_ENERGY_ANALOG_H__
#define __AP_ENERGY_ANALOG_H__

#include <AP_HAL/AP_HAL.h>
#include "AP_Energy_Backend.h"

class AP_Energy_Analog : public AP_Energy_Backend
{
public:
    AP_Energy_Analog(const AP_Int8 &pin) : 
        _source(NULL),
        _pin(pin),
        _last_pin(-1)
    {}

    // probe and initialise the sensor
    bool init(void);

    // return the current differential_pressure in Pascal
    bool get_differential_pressure(float &pressure);

    // temperature not available via analog backend
    bool get_temperature(float &temperature) { return false; }

private:
    AP_HAL::AnalogSource *_source;
    const AP_Int8 &_pin;
    int8_t _last_pin;
};

#endif // __AP_ENERGY_ANALOG_H__
