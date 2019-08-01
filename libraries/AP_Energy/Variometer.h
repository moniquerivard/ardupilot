#ifndef __VARIOMETER_H__
#define __VARIOMETER_H__

#include <AP_AHRS/AP_AHRS.h>
#include <AP_Param/AP_Param.h>

class Variometer {

    AP_AHRS &_ahrs;
    AP_Airspeed _airspeed;

public:
    //constructor
    Variometer(const AP_Vehicle::FixedWing& parms, AP_AHRS& ahrs);

    static const struct AP_Param::GroupInfo var_info[];

    float total_E;
    float prev_energy;
    float energy_change;
    float aspd;
    float alt;

    // The plane's current location
    struct Location current_loc {};

    void calc_energy(void);

    //accessors
    float get_energy(void) {
        return total_E;
    }

    float get_energy_change(void) {
        return energy_change;
    }

};

#endif //__VARIOMETER_H__
