#ifndef DISPLAY_H
#define DISPLAY_H

#include <stdint.h>

void display_init(uint32_t, uint32_t);
void display_destroy();
void display_mainloop();

#endif /* DISPLAY_H */