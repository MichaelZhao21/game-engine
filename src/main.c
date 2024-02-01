#define GLEW_STATIC

#include <stdio.h>
#include <stdlib.h>

#include <GL/glew.h>
#include <SDL2/SDL.h>

#include "graphics.h"

// Define vertex shader source
const GLchar* vertexSource = R"glsl(
    #version 150 core

    in vec2 position;

    void main()
    {
        gl_Position = vec4(position, 0.0, 1.0);
    }
)glsl";

// Define fragment shader source
const char *fragmentSource = R"glsl(
    #version 150 core

    out vec4 outColor;

    void main()
    {
        outColor = vec4(1.0, 1.0, 1.0, 1.0);
    }
    )glsl";

int main()
{
    Graphics graphics;
    GLenum err;

    // Initialize graphics + SDL
    if (graphics_init(&graphics, 800, 600) != 0)
    {
        fprintf(stderr, "Could not initialize graphics\n");
        exit(-1);
    }

    // SDL_Delay(2000);
    // graphics_cleanup(&graphics);
    // return 0;

    // Def vertices for triangle
    float vertices[] = {
        0.0f, 0.5f,  // Vertex 1 (X, Y)
        0.5f, -0.5f, // Vertex 2 (X, Y)
        -0.5f, -0.5f // Vertex 3 (X, Y)
    };

    // Create Vertex Buffer Object and bind it
    GLuint vbo;
    glGenBuffers(1, &vbo);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    
    // Create Vertex Array Objects
    GLuint vao;
    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);

    // Link attributes
    glEnableVertexAttribArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, NULL);

    // GLint posAttrib = glGetAttribLocation(shaderProgram, "position");
    // glVertexAttribPointer(posAttrib, 2, GL_FLOAT, GL_FALSE, 0, 0);
    // glEnableVertexAttribArray(posAttrib);

    // Check for error
    while ((err = glGetError()) != GL_NO_ERROR)
    {
        fprintf(stderr, "OpenGL error 1: %s\n", gluErrorString(err));
        exit(-1);
    }


    // Create Vertex shader
    GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vertexSource, NULL);
    glCompileShader(vertexShader);

    // Check status of shader compilation
    GLint status;
    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &status);
    if (status != GL_TRUE)
    {
        fprintf(stderr, "Vertex shader compilation err: %d\n", status);
        exit(-1);
    }
    printf("Vertex shader compiled successfully!\n");

    // Create fragment shader
    GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragmentSource, NULL);
    glCompileShader(fragmentShader);

    // Check status of shader compilation
    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &status);
    if (status != GL_TRUE)
    {
        fprintf(stderr, "Fragment shader compilation err: %d\n", status);
        exit(-1);
    }
    printf("Fragment shader compiled successfully!\n");

    // Combine shaders to create shader program
    GLuint shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);

    // Specify which framebuffer the fragment shader is to write to
    glBindFragDataLocation(shaderProgram, 0, "outColor");

    // Link and use program
    glLinkProgram(shaderProgram);
    glUseProgram(shaderProgram);


    // Check for error
    while ((err = glGetError()) != GL_NO_ERROR)
    {
        fprintf(stderr, "OpenGL error: %s\n", gluErrorString(err));
        exit(-1);
    }

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

        glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        glDrawArrays(GL_TRIANGLES, 0, 3);

        SDL_GL_SwapWindow(graphics.window);
    }

    graphics_cleanup(&graphics);

    // Exit
    printf("Exiting...\n");
    exit(0);
}
