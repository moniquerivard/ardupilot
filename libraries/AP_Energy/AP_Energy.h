/// -*- tab-width: 4; Mode: C++; c-basic-offset: 4; indent-tabs-mode: nil -*-

#ifndef __AP_ENERGY_H__
#define __AP_ENERGY_H__

#include <AP_Common/AP_Common.h>
#include <AP_HAL/AP_HAL.h>
#include <AP_Param/AP_Param.h>
#include <GCS_MAVLink/GCS_MAVLink.h>
#include <AP_Vehicle/AP_Vehicle.h>
#include "AP_Energy_Analog.h"

class AP_Energy
{
public:
    // constructor
    AP_Energy(const AP_Vehicle::FixedWing& parms):
        _energy(0.0f),
        _last_pressure(0.0f),
        _raw_pressure(0.0f),
        _healthy(false),
        _last_update_ms(0),
        _hil_set(false)
    {
		AP_Param::setup_object_defaults(this, var_info);
    };

    void        init(void);

    // read the analog source and update _energy
    void        read(void);

    // return the current change in energy [dimmensionless]
    float        get_energy(void) const {
        return _energy;
    }

    // return true if energy is enabled, and energy use is set
    bool        use(void) const {
        return _enable && _use;
    }

    // return true if energy is enabled
    bool        enabled(void) const {
        return _enable;
    }

    // force disable the energy sensor
    void        disable(void) {
        _enable.set(0);
    }

    // return the current raw pressure
    float get_raw_pressure(void) const {
        return _raw_pressure;
    }

	//log data to MAVLink -LOOK INTO CREATING ONE FOR THE ENERGY?
	//void log_mavlink_send(mavlink_channel_t chan, const Vector3f &vground);

    // return health status of sensor
    bool healthy(void) const { return _healthy;}

    void setHIL(float pressure) { _healthy = _hil_set = true; _hil_pressure = pressure; };

    // return time in ms of last update
    uint32_t last_update_ms(void) const { return _last_update_ms; }

    static const struct AP_Param::GroupInfo var_info[];

private:
    AP_Int8         _use;
    AP_Int8         _enable;
    float           _energy;
    float			_last_pressure;
    float			_raw_pressure;
    float           _hil_pressure;
    bool		    _healthy:1;
    uint32_t        _last_update_ms;
    bool            _hil_set :1;

    float get_pressure(void);

    AP_Energy_Analog analog;
};


#endif // __AP_Energy_H__

