#ifndef __AP_DSOAR_H__
#define __AP_DSOAR_H__

#include <AP_AHRS/AP_AHRS.h>
#include <AP_Param/AP_Param.h>
#include <AP_Airspeed/AP_Airspeed.h>

class AP_DSoar {

    AP_AHRS &_ahrs;
    AP_Airspeed _airspeed;
   
public:
    //constructor
    AP_DSoar(const AP_Vehicle::FixedWing &parms, AP_AHRS &ahrs);

      /*  _clMax(0.0f),
        _clMin(0.0f),
        _muMax(0.0f),
        mass(0.0f),
        mu(0.0f),
        cl(0.0f),
        alpha(0.0f),
        _ahrs(ahrs)
    {
        AP_Param::setup_object_defaults(this, var_info);
    };*/

    static const struct AP_Param::GroupInfo var_info[];
    
    //define constants
    float neg = 1.0f;

    float BMU = 1.51f;
    float BCL = neg * 0.25f;
    float WXAO = neg * 1.69f;
    float WAOMU = 0.90f;
    float WVMU = neg * 3.86f;
    float WPSICL = neg * 3.04f;
    float WGAMMACL = neg * 7.24f;
    float BAO = neg * 4.91f;

    void  math_stuff(void);

    float sigmoid(float arg);

    float get_mu(void) {
        return mu;
    }

    float get_alpha(void) {
        return alpha;
    }

private:
    AP_Float _clMax;
    AP_Float _clMin;
    AP_Float _muMax;
    AP_Float mass;
    float mu;
    float cl;
    float alpha;
    float a0;
    float mu_dt;
    float cl_dt;
    float v;
    float gamma;
    float psi;
    float beta;
};

#endif //__AP_DSOAR_H__