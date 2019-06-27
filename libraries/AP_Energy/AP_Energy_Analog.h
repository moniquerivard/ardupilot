/// -*- tab-width: 4; Mode: C++; c-basic-offset: 4; indent-tabs-mode: nil -*-

#ifndef __AP_ENERGY_ANALOG_H__
#define __AP_ENERGY_ANALOG_H__

#include <AP_HAL/AP_HAL.h>
#include <AP_Common/AP_Common.h>

class AP_Energy_Analog 
{
public:
    AP_Airspeed_Analog(const AP_Int8 &pin) : 
        _source(NULL),
        _pin(pin),
        _last_pin(-1)
    {}

private:
    AP_HAL::AnalogSource *_source;
    const AP_Int8 &_pin;
    int8_t _last_pin;
};

#endif // __AP_ENERGY_ANALOG_H__
