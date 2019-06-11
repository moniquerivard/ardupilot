/// -*- tab-width: 4; Mode: C++; c-basic-offset: 4; indent-tabs-mode: nil -*-

#ifndef __AP_ENERGY_ANALOG_H__
#define __AP_ENERGY_ANALOG_H__

#include <AP_HAL/AP_HAL.h>
#include "AP_Energy_Backend.h"

class AP_Energy_Analog : public AP_Energy_Backend //do i need the backend code? what does this do?
{
public:
    AP_Energy_Analog(const AP_Int8& pin) :
        _source(NULL),
        _pin(pin),
        _last_pin(-1)
    {}

    // probe and initialise the sensor
    bool init(void);

    // return the current energy change
    bool get_differential_pressure(float& pressure);

private:
    AP_HAL::AnalogSource* _source;
    const AP_Int8& _pin;
    int8_t _last_pin;
};

#endif // __AP_ENERGY_ANALOG.H


