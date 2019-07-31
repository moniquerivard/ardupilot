#include "AP_DSoar.h"

#define MS_TO_FTS 3.28084
#define RAD_TO_DEG 180/PI

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

    AP_GROUPEND
};

void AP_DSoar::math_stuff(float origin, const AP_AHRS &ahrs) {
    float a0;
    float mu_dt;
    float cl_dt;

    //state inputs  

    //x position? compare to the origin 
    float x = 1;

    //speed - needs to be in ft/s to work for this equation
    float v;
    if (airspeed.enabled()) {
        v = airspeed.get_airspeed;
    }
    else
    {
        ahrs.airspeed_estimate(&v);
    }
    v = v * MS_TO_FTS; 

    //pitch in degrees
    float gamma = ahrs.pitch;
    gamma = gamma * RAD_TO_DEG;

    //heading in degrees
    float psi = ahrs.yaw;
    psi = psi * RAD_TO_DEG;

    //equations determined by NEAT algorithm 
    a0 = sigmoid(((beta * beta) / GRAVITY_MSS) * WXAO * x + BAO);
    mud_dt = sigmoid(WAOMU * a0 + (beta / GRAVITY_MSS) * WVMU * v + BMU);
    cl_dt = sigmoid(WPSICL * psi + WGAMMACL * gamma + BCL);
    
    //determine desired lift and heading angle from above math 
    float mu = mass* mu_dt * 2 * _muMax-_muMax;
    float cl = cl_dt * (_clMax - _clMin) + _clMin;

    float alpha = cl /360; //small airfoil, small AOA THIN AIRFOIL THEORY 
}

float AP_DSoar::sigmoid(float arg) {
    float numerator = 1.0f;
    float denom = 1.0 + exp(-1.0 * arg);
    return numerator / denom;
}



