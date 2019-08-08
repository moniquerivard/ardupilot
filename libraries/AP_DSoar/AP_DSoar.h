#ifndef __AP_DSOAR_H__
#define __AP_DSOAR_H__

#include <AP_AHRS/AP_AHRS.h>
#include <AP_Param/AP_Param.h>
#include <AP_Airspeed/AP_Airspeed.h>
#include <AP_SpdHgtControl/AP_SpdHgtControl.h>

class AP_DSoar {

    AP_AHRS &_ahrs;
    AP_Airspeed _airspeed;
   
public:
    //constructor
    AP_DSoar(const AP_Vehicle::FixedWing &parms, AP_AHRS &ahrs);

    static const struct AP_Param::GroupInfo var_info[];
    
    //define constants
    float neg = 1.0f;

    /*
    float BMU = 1.51f;
    float BCL = neg * 0.25f;
    float WXAO = neg * 1.69f;
    float WAOMU = 0.90f;
    float WVMU = neg * 3.86f;
    float WPSICL = neg * 3.04f;
    float WGAMMACL = neg * 7.24f;
    float BAO = neg * 4.91f;
     */

    float b1 = 1.05326689227f;
    float w_v_n1 = 1.0f;
    float b2 = neg * 1.43078889606f;
    float w_n1_n2 = 1.31341279392f;
    float bmu = 0.67455379686f;
    float w_v_mu = neg* 0.914065507212f;
    float w_n2_mu = neg * 0.258135759556f;
    float bcl = 0.00953498555207;
    float w_gamma_cl = neg * 0.0705295732367f;

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
    AP_Float vMax;
    float mu;
    float cl;
    float alpha;
    float n1;
    float n2;
    float mu_dt;
    float cl_dt;
    float v;
    float gamma;
};

#endif //__AP_DSOAR_H__