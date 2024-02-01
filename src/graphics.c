#include <stdio.h>
#include <stdlib.h>

#include <GL/glew.h>
#include <SDL2/SDL.h>

#include "graphics.h"

int graphics_init(Graphics *graphics, int width, int height)
{
    // Initialize SDL and check for errors
    printf("Intitializing SDL...\n");
    if (SDL_Init(SDL_INIT_VIDEO) != 0)
    {
        fprintf(stderr, "Could not initialize SDL: %s\n", SDL_GetError());
        return -1;
    }
    printf("SDL successfully initialized\n");

    // Cleanup on exit
    atexit(SDL_Quit);

    // Set OpenGL version to 4.6
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 6);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);

    // Turn on OpenGL double buffering with a 24 bit Z buffer
    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
    SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);
    SDL_GL_SetAttribute(SDL_GL_STENCIL_SIZE, 8);

    // Create SDL Window
    graphics->window = SDL_CreateWindow("WINDOWWWW", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN);
    if (graphics->window == NULL)
    {
        fprintf(stderr, "Could not create window: %s\n", SDL_GetError());
        return -1;
    }

    // Create OpenGL Context and attach to window
    graphics->gl_context = SDL_GL_CreateContext(graphics->window);
    if (graphics->gl_context == NULL)
    {
        fprintf(stderr, "Could not create OpenGL context: %s\n", SDL_GetError());
        return -1;
    }

    // Init GLEW
    glewExperimental = GL_TRUE;
    GLenum err = glewInit();
    if (err != GLEW_OK)
    {
        fprintf(stderr, "Error initializing GLEW: %s\n", glewGetErrorString(err));
    }
    printf("Using GLEW %s\n", glewGetString(GLEW_VERSION));

    // Sync buffer swap with monitor's vertical refresh rate
    if (SDL_GL_SetSwapInterval(1) < 0)
    {
        fprintf(stderr, "Warning: Unable to set VSync! SDL Error: %s\n", SDL_GetError());
    }

    // Set background to black
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    return 0;
}

int graphics_cleanup(Graphics *graphics)
{
    // Destroy OpenGL context
    SDL_GL_DeleteContext(graphics->gl_context);

    // Destroy window
    SDL_DestroyWindow(graphics->window);

    // SDL Quit
    SDL_Quit();

    return 0;
}