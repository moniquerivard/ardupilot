
#include <AP_AHRS/AP_AHRS.h>
#include <AP_Param/AP_Param.h>


class Variometer {
    
    const AP_AHRS& _ahrs;
    
    
public:
    //constructor
    Variometer();

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

};