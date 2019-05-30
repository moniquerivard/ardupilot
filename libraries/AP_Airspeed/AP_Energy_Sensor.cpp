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
#include "AP_Airspeed.h"

extern const AP_HAL::HAL& hal;

// scaling for 3DR analog airspeed sensor
#define INPUT_TO_VOLTS (5.0/1024.0) //this is the value used from the mega, might be different
#define VOLTS_TO_KPA -2.5f //defined by sensor conversion

#if CONFIG_HAL_BOARD == HAL_BOARD_APM1
extern AP_ADC_ADS7844 apm1_adc;
#endif

bool AP_Energy_Sensor::init()
{
    tempoaryPressure = 0; //this might need to be in different location, based on code strucutre?
#if CONFIG_HAL_BOARD == HAL_BOARD_APM1
    if (_pin == 64) {
        _source = new AP_ADC_AnalogSource( &apm1_adc, 7, 1.0f);
        return true;
    }
#endif
    _source = hal.analogin->channel(_pin);
    return true;
}

// read the airspeed sensor
bool AP_Energy_Sensor::get_energy(float &diff)
{
    if (_source == NULL) {
        return false;
    }
    _source->set_pin(_pin);
    pressure = _source->voltage_average_ratiometric() * INPUT_TO_VOLTS;
    pressure = voltage + VOLTS_TO_KPA;

    //configure for energy usage
    diff = tempoaryPressure - pressure;
    tempPressure = pressure;
    return true;
}

