/// -*- tab-width: 4; Mode: C++; c-basic-offset: 4; indent-tabs-mode: nil -*-
/*
   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */
/*
 *   AP_Energy.cpp - energy (pitot) driver
 */


#include <AP_HAL/AP_HAL.h>
#include <AP_Math/AP_Math.h>
#include <AP_Common/AP_Common.h>
#include <AP_ADC/AP_ADC.h>
#include "AP_Energy.h"

extern const AP_HAL::HAL& hal;

//could add configs for other boards but just start here for now

#define ENERGY_DEFAULT_PIN 3 //usually airspeed is 0

//table of user settable paramaters
const AP_Param::GroupInfo AP_Energy::var_info[] PROGMEM = {

    // @Param: ENABLE
    // @DisplayName: Energy Sensor enable
    // @Description: enable energy sensor 
    // @Values: 0:Disable,1:Enable
    AP_GROUPINFO("ENABLE", 0, AP_Energy, _enable, 1),

    // @Param: PIN
    // @DisplayName: Energy pin
    // @Description: The analog pin number that the energy sensor is connected to. Set this to 0..9 for the APM2 analog pins. Set to 64 on an APM1 for the dedicated airspeed port on the end of the board. Set to 11 on PX4 for the analog airspeed port. Set to 15 on the Pixhawk for the analog airspeed port. Set to 65 on the PX4 or Pixhawk for an EagleTree or MEAS I2C airspeed sensor.
    // @User: Advanced
    AP_GROUPINFO("PIN",  1, AP_Energy, _pin, ENERGY_DEFAULT_PIN),

    // @Param: USE
    // @DisplayName: Energy use
    // @Description: use energy for flight control
    // @Values: 1:Use,0:Don't Use
    AP_GROUPINFO("USE",    2, AP_Energy, _use, 1),

    AP_GROUPEND
};

/*
  this scaling factor converts from the old system where we used a 
  0 to 4095 raw ADC value for 0-5V to the new system which gets the
  voltage in volts directly from the ADC driver
 */
#define SCALING_OLD_CALIBRATION 819 // 4095/5

void AP_Energy::init()
{
    _last_pressure = 0;
    //_calibration.init(_ratio);
    //_last_saved_ratio = _ratio;
    //_counter = 0;
    
    analog.init();
}

// read the energy sensor
float AP_Energy::get_pressure(void)
{
    //if sensor is not enabled, do not do anything
    if (!_enable) {
        return 0;
    }
    //what is _hil_set?
    if (_hil_set) {
        _healthy = true;
        return _hil_pressure;
    }

    //actually returning the pressure value from the sensor
    float pressure = 0;
    _healthy = analog.get_differential_pressure(pressure);
    return pressure; //this is changed in get_diff_pressure bc passed by reference
}

//no callibration needed? taking the difference?

// read the energy sensor
void AP_Energy::read(void)
{
    if (!_enable) {
        return;
    }
   float current_pressure = get_pressure();
    // remember raw pressure for logging
    _raw_pressure = current_pressure;

    _energy = _last_pressure-current_pressure; //calculate energy with the difference between current and previous
    _last_pressure          = current_pressure; // update last_pressure to current for next comparison
    _last_update_ms         = hal.scheduler->millis(); //update time?
}

