#include "pico_servo.h"
#include "pico/stdlib.h"

#include "board.h"

void check(int err, const char* msg)
{
    if (err)
    {
        panic(msg);
    }
}

void setup()
{
    int err;
    err = servo_init();
    check(err, "couldn't init servo system");

    err = servo_clock_auto();
    check(err, "couldn't set pwm clock");

    err = servo_attach(SERVO_A);
    check(err, "couldn't attach servo a");
    err = servo_attach(SERVO_B);
    check(err, "couldn't attach servo b");

    servo_move_to(SERVO_A, 90);
    servo_move_to(SERVO_B, 90);
}

void loop()
{

}

int main()
{
    setup();

    while (true)
    {
        loop();
    }
}
