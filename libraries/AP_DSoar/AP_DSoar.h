#ifndef __AP_DSOAR_H__
#define __AP_DSOAR_H__

#include <AP_AHRS/AP_AHRS.h>
#include <AP_Param/AP_Param.h>

class AP_DSoar {

   
public:
    //constructor
    AP_DSoar(const AP_Vehicle::FixedWing& parms, const AP_AHRS& ahrs) :
        _clMax(0.0f),
        _clMin(0.0f),
        _muMax(0.0f),
        mass(0.0f),
        mu(0.0f),
        cl(0.0f),
        alpha(0.0f),
        _ahrs(ahrs)
    {
        AP_Param::setup_object_defaults(this, var_info);
    };

    static const struct AP_Param::GroupInfo var_info[];
    
    //define constants
    int32_t neg = 1.0;

    int32_t BMU = 1.51;
    int32_t BCL = neg * 0.25;
    int32_t WXAO = neg * 1.69;
    int32_t WAOMU = 0.90;
    int32_t WVMU = neg * 3.86;
    int32_t WPSICL = neg * 3.04;
    int32_t WGAMMACL = neg * 7.24;
    int32_t BAO = neg * 4.91;

    int32_t get_mu(void) {
        return mu;
    }

    int32_t get_alpha(void) {
        return alpha;
    }

private:
    int32_t _clMax;
    int32_t _clMin;
    int32_t _muMax;
    int32_t mass;
    int32_t mu;
    int32_t cl;
    int32_t alpha;

    const AP_AHRS& _ahrs;
};

#endif //__AP_DSOAR_H__