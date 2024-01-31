#include "SDL.h"
#include <stdio.h>

int main() {
    // Initialize SDL and check for errors
    printf("Intitializing SDL...\n");
    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
        printf("Could not initialize SDL: %s\n", SDL_GetError());
        exit(-1);
    }
    printf("SDL successfully initialized\n");

    // TODO: Do stuff here

    // Quit SDL
    printf("Quitting SDL...\n");
    SDL_Quit();
    printf("Done!\n");

    // Exit
    printf("Exiting...\n");
    exit(0);
}