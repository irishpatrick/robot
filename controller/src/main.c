#include <signal.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/ioctl.h>
#include <linux/i2c-dev.h>
#include <pigpio.h>
#include <stdbool.h>
#include <stdio.h>
#include <pthread.h>

#include "drive.h"
#include "server.h"
#include "msgq.h"

static DRIVE drive;
static bool running;

typedef struct _server_data
{
    pthread_mutex_t* send_mutex;
    pthread_mutex_t* recv_mutex;
    bmsgq* chan;
} server_data;

static pthread_t server_thread;
static pthread_mutex_t recv_mutex;
static pthread_mutex_t send_mutex;
static bmsgq server_channel;
static server_data sdat;


void handle_sigint(int sig)
{
    running = false;
}

int init()
{
    int err;

    printf("starting server...\n");
    bmsgq_init(&server_channel);
    
    err = pthread_mutex_init(&send_mutex, NULL);
    if (err)
    {
        return 1;
    }
    err = pthread_mutex_init(&recv_mutex, NULL);
    if (err)
    {
        return 1;
    }

    sdat.send_mutex = &recv_mutex;
    sdat.recv_mutex = &send_mutex;
    sdat.chan = &server_channel;

    err = pthread_create(&server_thread, NULL, server_main, (void*)(&sdat));
    if (err)
    {
        return 1;
    }

    printf("starting drivetrain...\n");
    drive_init(&drive);
    drive_setspeed(&drive, LEFT, PI_HW_PWM_RANGE / 2);
    drive_setspeed(&drive, RIGHT, PI_HW_PWM_RANGE / 2);

    printf("attaching signals...\n");
    signal(SIGINT, handle_sigint);

    running = true;

    printf("ready!\n");

    return 0;
}

void loop()
{
    drive_update(&drive);
}

void cleanup()
{
    printf("stopping drivetrain...\n");
    drive_cleanup(&drive);
    printf("stopping server...\n");
    server_stop();
    printf("waiting for server shutdown...\n");
    pthread_join(server_thread, NULL);
    printf("freeing resources...\n");
    bmsgq_delete(&server_channel);
}

int main(int argc, char** argv)
{
    int err;
   
    err = gpioInitialise();
    if (err < 0)
    {
        return 1;
    }

    init();

    while (running)
    {
        loop();
    }

    cleanup();

    gpioTerminate();
    return 0;
}
