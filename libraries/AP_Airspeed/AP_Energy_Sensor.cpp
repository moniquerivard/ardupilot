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
 *   analog energy snesor driver - using MPXV7002DP
 */


#include <AP_HAL/AP_HAL.h>
#include <AP_Math/AP_Math.h>
#include <AP_Common/AP_Common.h>
#include <AP_ADC/AP_ADC.h>
#include <AP_ADC_AnalogSource/AP_ADC_AnalogSource.h>
#include "AP_Energy_Sensor.h"

extern const AP_HAL::HAL& hal;

//could add configs for other boards but just start here for now

#define ENERGY_DEFAULT_PIN 1 //usually airspeed is 0

//table of user settable paramaters
cost AP_Param::GroupInfo AP_Energy_Sensor::var_info[] PROGMEM = {

    // @Param: ENABLE
    // @DisplayName: Energy Sensor enable
    // @Description: enable energy sensor 
    // @Values: 0:Disable,1:Enable
    AP_GROUPINFO("ENABLE", 0, AP_Energy_Sensor, _enable, 1),

    // @Param: PIN
    // @DisplayName: Energy pin
    // @Description: The analog pin number that the energy sensor is connected to. Set this to 0..9 for the APM2 analog pins. Set to 64 on an APM1 for the dedicated airspeed port on the end of the board. Set to 11 on PX4 for the analog airspeed port. Set to 15 on the Pixhawk for the analog airspeed port. Set to 65 on the PX4 or Pixhawk for an EagleTree or MEAS I2C airspeed sensor.
    // @User: Advanced
    AP_GROUPINFO("PIN",  1, AP_Energy_Sensor, _pin, ENERGY_DEFAULT_PIN),

    // @Param: USE
    // @DisplayName: Energy use
    // @Description: use energy for flight control
    // @Values: 1:Use,0:Don't Use
    AP_GROUPINFO("USE",    2, AP_Energy_Sensor, _use, 0),


    // @Param: OFFSET
    // @DisplayName: Energy offset
    // @Description: Airspeed calibration offset
    // @Increment: 0.1
    AP_GROUPINFO("OFFSET", 3, AP_Energy_Sensor, _offset, 0),

    AP_GROUPEND
}

//all below code is from the analog modifeid code
// scaling for 3DR analog airspeed sensor
#define INPUT_TO_VOLTS (5.0/1024.0) //this is the value used from the mega, might be different
#define VOLTS_TO_KPA -2.5f //defined by sensor conversion

#if CONFIG_HAL_BOARD == HAL_BOARD_APM1
extern AP_ADC_ADS7844 apm1_adc;
#endif

void AP_Energy_Sensor::init() {
    _last_pressure = 0;
    _source = hal.analogin->channel(_pin);

}



// read the airspeed sensor
bool AP_Energy_Sensor::get_energy(float &diff)
{
    if (_source == NULL) {
        return false;
    }
    _source->set_pin(_pin);
    voltage = _source->voltage_average_ratiometric() * INPUT_TO_VOLTS;
    pressure = voltage + VOLTS_TO_KPA;

    //configure for energy usage
    diff = tempoaryPressure - pressure;
    tempPressure = pressure;
    return true;
}

