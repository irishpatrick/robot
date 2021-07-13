#ifndef PACKET_H
#define PACKET_H

#include <stdint.h>

typedef struct _commander_pkt
{
    uint8_t inst;
    uint8_t argc;
    int32_t argv[10];
} commander_pkt;

typedef struct _robot_pkt
{
    uint32_t rpm[2];
    uint32_t axis[2];
    // todo map
    // todo lidar data
} robot_pkt;

#endif /* PACKET_H */