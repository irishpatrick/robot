#include <stdlib.h>
#include <stdio.h>
#include <assert.h>

#include "client.h"
#include "display.h"

static client cli;

int main(int argc, char** argv)
{
    client_init(&cli);
    client_start(&cli);

    display_init(512, 480);
    display_mainloop();
    display_destroy();

    client_join(&cli);
    
    return 0;
}

