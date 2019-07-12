#include "Variometer.h"


//this is kinda messy code bud just ideas for now

/*

1. get airspeed from sensor or from AHRS
2. get altitude from inner sensor?
3. 
4. total energy = alt + 0.5faspedfiltaspdfilt/grav

*/

void Variometer::calc_energy(void) {
 
    prev_energy = total_E;
    
    float aspd;
    float alt = current_loc.alt / 100.0f;

    if (airspeed.enabled()) {
        aspd = airspeed.get_airspeed;
    }
    else
    {
       _ahrs.airspeed_estimate(&aspd);
    }

    total_E = alt + (0.5f * aspd * aspd / GRAVITY_MSS);
    energy_change = total_E - prev_energy;
    prev_energy = total_E;
}


