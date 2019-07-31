#ifndef __VARIOMETER_H__
#define __VARIOMETER_H__

#include <AP_AHRS/AP_AHRS.h>
#include <AP_Param/AP_Param.h>


class Variometer {
       
public:
    //constructor
    Variometer(const AP_Vehicle::FixedWing& parms, const AP_AHRS& ahrs) :
        _ahrs(ahrs)
    {
        AP_Param::setup_object_defaults(this, var_info);
    };

    static const struct AP_Param::GroupInfo var_info[];

    float total_E;
    float prev_energy;
    float energy_change;

    void calc_energy(void);

    float get_energy(void) {
        return total_E;
    }

    float get_energy_change(void) {
        return energy_change;
    }

    // Airspeed Sensors
    AP_Airspeed airspeed;

   
private:
    const AP_AHRS& _ahrs;
};

#endif //__VARIOMETER_H__
