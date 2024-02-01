#ifndef GRAPHICS_H
#define GRAPHICS_H

#include <SDL2/SDL.h>

typedef struct
{
    int width;
    int height;
    SDL_Window *window;
    SDL_GLContext gl_context;
} Graphics;

int graphics_init(Graphics *graphics, int width, int height);
int graphics_cleanup(Graphics *graphics);

#endif // GRAPHICS_H