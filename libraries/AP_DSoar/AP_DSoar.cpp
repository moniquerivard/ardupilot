#include "AP_DSoar.h"

#define MS_TO_FTS 3.28084

const AP_Param::GroupInfo AP_DSoar::var_info[] PROGMEM = {

    // @Param: CLMAX
    // @DisplayName: Max lift coeff
    // @Description: set cl max for calculations
    // @Values: 
    AP_GROUPINFO("ClMax",    0, AP_DSoar, _clMax, 1.5),

    // @Param: CLMIN
    // @DisplayName: Min lift coeff
    // @Description: set cl min for calculations
    // @Values: 
    AP_GROUPINFO("ClMin",    1, AP_DSoar, _clMin, -0.2),

    // @Param: MUMAX
    // @DisplayName: Mav roll angle
    // @Description: max roll angle in degrees
    // @Values: 
    AP_GROUPINFO("muMax", 2, AP_DSoar, _muMax, 60), //degrees

    // @Param: MASS
    // @DisplayName: aircraft mass
    // @Description: mass of the aircraft in slugs
    // @Values:
    AP_GROUPINFO("mass",  3, AP_DSoar, mass, 0.58f), //slugs

    AP_GROUPINFO("vMax", 4, AP_DSoar, vMax, 30), //ft per sec
    AP_GROUPEND
};

AP_DSoar::AP_DSoar(const AP_Vehicle::FixedWing &parms, AP_AHRS &ahrs) :
    _ahrs(ahrs),
    _airspeed(parms)
{
 AP_Param::setup_object_defaults(this, var_info);
}

void AP_DSoar::math_stuff(void) {

    //speed - needs to be in ft/s to work for this equation
    if (_airspeed.enabled()) {
        v = _airspeed.get_airspeed();
    }
    else
    {
        _ahrs.airspeed_estimate(&v);
    }
    v = v * MS_TO_FTS; 

    //pitch in degrees
    gamma = (_ahrs.pitch)* RAD_TO_DEG;

    /*
    //equations determined by NEAT algorithm 
    a0 = sigmoid(((beta * beta) / GRAVITY_MSS) * WXAO * x + BAO);
    mu_dt = sigmoid(WAOMU * a0 + (beta / GRAVITY_MSS) * WVMU * v + BMU);
    cl_dt = sigmoid(WPSICL * psi + WGAMMACL * gamma + BCL);
     */

    //equations determined by NEAT
    n1 = sigmoid(w_v_n1*(v/vMax)+b1);
    n2 = sigmoid(w_n1_n2*n1+b2);
    mu_dt = sigmoid(w_v_mu*(v/vMax) + w_n2_mu*n2 + bmu);
    cl_dt =sigmoid(w_gamma_cl*(gamma/(PI*0.5))+bcl);

    //determine desired lift and heading angle from above math 
    mu = mass* mu_dt * 2 * _muMax-_muMax;
    cl = cl_dt * (_clMax - _clMin) + _clMin;

    alpha = cl /360; //small airfoil, small AOA THIN AIRFOIL THEORY
}

float AP_DSoar::sigmoid(float arg) {
    float numerator = 1.0f;
    float denom = 1.0 + exp(-1.0 * arg);
    return numerator / denom;
}



