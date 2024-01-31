#include "SDL2/SDL.h"
#include <stdio.h>

int main()
{
    // Initialize SDL and check for errors
    printf("Intitializing SDL...\n");
    if (SDL_Init(SDL_INIT_VIDEO) != 0)
    {
        fprintf(stderr, "Could not initialize SDL: %s\n", SDL_GetError());
        exit(-1);
    }
    printf("SDL successfully initialized\n");

    // Cleanup on exit
    atexit(SDL_Quit);

    SDL_Window *window = NULL;
    SDL_Surface *surface = NULL;

    window = SDL_CreateWindow("SDL Tutorial", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 640, 480, SDL_WINDOW_SHOWN);
    if (window == NULL)
    {
        fprintf(stderr, "Could not create window: %s\n", SDL_GetError());
        exit(-1);
    }

    screen = SDL_GetWindowSurface(window);
    SDL_FillRect(screen, NULL, SDL_MapRGB(screen->format, 0xFF, 0xFF, 0xFF));

    SDL_UpdateWindowSurface(window);

    // Game loop
    SDL_Event event;
    int running = 1;
    while (running)
    {
        while (SDL_PollEvent(&event))
        {
            if (event.type == SDL_QUIT)
                running = 0;
        }
    }

    SDL_DestoryWindow(window);

    // Exit
    printf("Exiting...\n");
    exit(0);
}
