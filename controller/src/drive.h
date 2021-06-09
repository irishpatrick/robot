#ifndef DRIVE_H
#define DRIVE_H

#include <stdint.h>

#define LEFT 0
#define RIGHT 1

typedef struct _DRIVE
{
    uint8_t dir[2];
    uint32_t speed[2];
    uint32_t tach[2];
    uint32_t* rpm_map[2];
    uint8_t modified;
} DRIVE;

int32_t drive_init(DRIVE*);
void drive_setdir(DRIVE*, uint8_t, uint8_t);
void drive_setspeed(DRIVE*, uint8_t, uint32_t);
void drive_update(DRIVE*);
void drive_cleanup(DRIVE*);

#endif /* DRIVE_H */
