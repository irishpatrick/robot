#include "display.h"

#include <stdlib.h>
#include <stdbool.h>
#include <SDL.h>

static SDL_Window* window;
static SDL_Renderer* renderer;
static SDL_Event event;
static bool running;

void display_init(uint32_t w, uint32_t h)
{
    int err = SDL_Init(SDL_INIT_VIDEO | SDL_INIT_EVENTS);
    if (err)
    {
        exit(1);
    }

    uint32_t flags = 0;
    window = SDL_CreateWindow(
        "Robot Commander", 
        SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
        w, h,
        flags
    );
    if (!window)
    {
        exit(2);
    }

    flags = 0;
    renderer = SDL_CreateRenderer(window, -1, flags);
    if (!renderer)
    {
        exit(3);
    }

    running = true;
}

void display_destroy()
{
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
}

void display_mainloop()
{
    while (running)
    {
        while (SDL_PollEvent(&event))
        {
            if (event.type == SDL_QUIT)
            {
                running = false;
            }
        }

        SDL_RenderPresent(renderer);
    }
}