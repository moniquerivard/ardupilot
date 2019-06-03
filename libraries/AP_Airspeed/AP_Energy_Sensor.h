/// -*- tab-width: 4; Mode: C++; c-basic-offset: 4; indent-tabs-mode: nil -*-

#ifndef __AP_ENERGY_SENSOR_H__
#define __AP_ENERGY_SENSOR_H__

#include <AP_HAL/AP_HAL.h>


class AP_Energy_Sensor : public AP_Airspeed_Backend //do i need the backend code? what does this do?
{
public:
    AP_Energy_Sensor(const AP_Int8& pin) :
        _source(NULL),
        _pin(pin),
        _last_pin(-1)

    {}

    // probe and initialise the sensor
    bool init(void);

    // return the current energy change
    bool get_energy(float& diff);
};

class AP_Energy_Sensor
{
public:
    // constructor
    AP_Energy_Sensor(const AP_Vehicle::FixedWing& parms) :
        _source(NULL),
        _pin(pin),
        _last_pin(-1)
        _raw_airspeed(0.0f),
        _airspeed(0.0f),
        _last_pressure(0.0f), //
        _raw_pressure(0.0f),
        _EAS2TAS(1.0f),
        _healthy(false),
        _hil_set(false),
        _last_update_ms(0),
        _calibration(parms),
        _last_saved_ratio(0.0f),
        _counter(0),
        analog(_pin)
    {
        AP_Param::setup_object_defaults(this, var_info);
    };

private:
    AP_Int8     _enable;
    AP_Int8     _pin;
    AP_Int8     _offset;
    AP_Int8     _use;

    AP_HAL::AnalogSource* _source;
    const AP_Int8& _pin;
    int8_t _last_pin;

};

#endif // __AP_ENERGY_SENSOR.H


