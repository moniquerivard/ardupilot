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

void AP_DSoar::init(float &lat, float &lon) {
    //using this to set origin for the x state to be compared  back to 
}

void AP_DSoar::math_stuff(float origin) {
    int32_t a0;
    int32_t mu_dt;
    int32_t cl_dt;

    //state inputs  

    //x position? compare to the origin 
    int32_t x = 1;

    //speed - needs to be in ft/s to work for this equation
    int32_t v;
    if (airspeed.enabled()) {
        v = airspeed.get_airspeed;
    }
    else
    {
        _ahrs.airspeed_estimate(&v);
    }
    v = v * MS_TO_FTS; 

    //pitch in degrees
    int32_t gamma = _ahrs.pitch; 
    gamma = gamma * RAD_TO_DEG;

    //heading in degrees
    int32_t psi = _ahrs.yaw; 
    psi = psi * RAD_TO_DEG; 

    //equations determined by NEAT algorithm 
    a0 = sigmoid(((beta * beta) / GRAVITY_MSS) * WXAO * x + BAO);
    mud_dt = sigmoid(WAOMU * a0 + (beta / GRAVITY_MSS) * WVMU * v + BMU);
    cl_dt = sigmoid(WPSICL * psi + WGAMMACL * gamma + BCL);
    
    //determine desired lift and heading angle from above math 
    int32_t mu = mass* mu_dt * 2 * _muMax-_muMax;
    int32_t cl = cl_dt * (_clMax - _clMin) + _clMin;

    int32_t alpha = cl /360; //small airfoil, small AOA THIN AIRFOIL THEORY 
}

int32_t AP_DSoar::sigmoid(int32_t arg) {
    int32_t numerator = 1.0f;
    int32_t denom = 1.0 + exp(-1.0 * arg);
    return numerator / denom;
}



