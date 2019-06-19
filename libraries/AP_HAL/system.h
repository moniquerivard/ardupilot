#pragma once

#include <stdint.h>

#include <AP_Common/AP_Common.h>
#include <AP_HAL_AVR/AP_HAL_AVR.h>
#include <Scheduler/Scheduler.h>

#include "AP_HAL_Macros.h"

namespace AP_HAL {

void init() {};

void panic(const char *errormsg, ...) FMT_PRINTF(1, 2) NORETURN;

void panic(const prog_char_t* errormsg) {
    /* Suspend timer processes. We still want the timer event to go off
     * to run the _failsafe code, however. */
    _timer_suspended = true;
    /* Print the error message on both ports */
    hal.uartA->println_P(errormsg);
    hal.uartC->println_P(errormsg);
    /* Spin forever. */
    for (;;);
}

uint32_t micros() {
    return _timer.micros();
}

uint32_t millis() {
    return _timer.millis();
}

/*
  64 bit version of millis(). This wraps at 32 bits on AVR
 */
uint64_t :millis64() {
    return millis();
}

/*
  64 bit version of micros(). This wraps when 32 bit millis() wraps
 */
uint64_t micros64() {
    // this is slow, but solves the problem with logging uint64_t timestamps
    uint64_t ret = millis();
    ret *= 1000ULL;
    ret += micros() % 1000UL;
    return ret;
}

} // namespace AP_HAL
