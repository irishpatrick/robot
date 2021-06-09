#include "drive.h"

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include <pigpio.h>

#define PWM_FREQ 200e3

int32_t drive_init(DRIVE* d)
{
    // init data structure
    memset(d->dir, 1, 2 * sizeof(uint8_t));
    memset(d->speed, 0, 2 * sizeof(uint32_t));
    memset(d->tach, 0, 2 * sizeof(uint32_t));
    d->modified = 1;

    // load rpm maps

    // hardware pwm pins
    //gpioSetMode(12, PI_OUTPUT);
    //gpioSetMode(13, PI_OUTPUT);
    
    // direction pins
    gpioSetMode(5, PI_OUTPUT);
    gpioSetMode(6, PI_OUTPUT);
    
    return 0;
}

void drive_setdir(DRIVE* d, uint8_t m, uint8_t r)
{
    d->dir[m] = r;
    d->modified = 1;
}

void drive_setspeed(DRIVE* d, uint8_t m, uint32_t s)
{
    d->speed[m] = s;
    d->modified = 1;
}

void drive_update(DRIVE* d)
{
    if (d->modified)
    {
        int err[2];
        d->modified = 0;
        err[0] = gpioHardwarePWM(12, PWM_FREQ, d->speed[0]);
        err[1] = gpioHardwarePWM(13, PWM_FREQ, d->speed[1]);
        gpioWrite(5, d->dir[0]);
        gpioWrite(6, d->dir[1]);
    }
}

void drive_cleanup(DRIVE* d)
{
    drive_setspeed(d, LEFT, PI_MIN_DUTYCYCLE_RANGE);
    drive_setspeed(d, RIGHT, PI_MIN_DUTYCYCLE_RANGE);
    drive_update(d);
}
