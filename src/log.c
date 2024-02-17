#include <stdio.h>
#include <GL/glew.h>

#include "log.h"

int restart_gl_log()
{
    FILE *file = fopen(GL_LOG_FILE, "w");
    if (!file)
    {
        fprintf(stderr, "ERROR: could not open GL_LOG_FILE log file %s for writing\n", GL_LOG_FILE);
        return 1;
    }

    time_t now = time(NULL);
    char *date = ctime(&now);
    fprintf(file, "GL_LOG_FILE log | local time: %s\n", date);
    fclose(file);

    return 0;
}

int gl_log(const char* msg, ...) {
    va_list arg;

    // Open file
    FILE* file = fopen(GL_LOG_FILE, "a");
    if (!file) {
        fprintf(stderr, "ERROR: Could not open GL_LOG_FILE %s file for appending\n", GL_LOG_FILE);
        return 1;
    }

    // Print error message
    va_start(arg, msg);
    vfprintf(file, msg, arg);
    va_end(arg);
    
    // Close file
    fclose(file);
    
    return 0;
}

int gl_log_err(const char* msg, ...) {
    va_list arg;

    // Open file
    FILE* file = fopen(GL_LOG_FILE, "a");
    if (!file) {
        fprintf(stderr, "ERROR: Could not open GL_LOG_FILE %s file for appending\n", GL_LOG_FILE);
        return 1;
    }

    // Print error message
    va_start(arg, msg);
    vfprintf(file, msg, arg);
    va_end(arg);

    // Also print to stderr
    va_start(arg, msg);
    vfprintf(stderr, msg, arg);
    va_end(arg);

    // Close file
    fclose(file);

    return 0;
}

int log_gl_params()
{
    // Define parameters and their names
    GLenum params[] = {
        GL_MAX_COMBINED_TEXTURE_IMAGE_UNITS,
        GL_MAX_CUBE_MAP_TEXTURE_SIZE,
        GL_MAX_DRAW_BUFFERS,
        GL_MAX_FRAGMENT_UNIFORM_COMPONENTS,
        GL_MAX_TEXTURE_IMAGE_UNITS,
        GL_MAX_TEXTURE_SIZE,
        GL_MAX_VARYING_FLOATS,
        GL_MAX_VERTEX_ATTRIBS,
        GL_MAX_VERTEX_TEXTURE_IMAGE_UNITS,
        GL_MAX_VERTEX_UNIFORM_COMPONENTS,
        GL_MAX_VIEWPORT_DIMS,
        GL_STEREO,
    };
    const char *names[] = {
        "GL_MAX_COMBINED_TEXTURE_IMAGE_UNITS",
        "GL_MAX_CUBE_MAP_TEXTURE_SIZE",
        "GL_MAX_DRAW_BUFFERS",
        "GL_MAX_FRAGMENT_UNIFORM_COMPONENTS",
        "GL_MAX_TEXTURE_IMAGE_UNITS",
        "GL_MAX_TEXTURE_SIZE",
        "GL_MAX_VARYING_FLOATS",
        "GL_MAX_VERTEX_ATTRIBS",
        "GL_MAX_VERTEX_TEXTURE_IMAGE_UNITS",
        "GL_MAX_VERTEX_UNIFORM_COMPONENTS",
        "GL_MAX_VIEWPORT_DIMS",
        "GL_STEREO",
    };

    gl_log("===== GL Context Params =====\n");

    // Get the version and print it
    const char *ver = (const char *)glGetString(GL_VERSION);
    gl_log("GL_VERSION: %s\n", ver);

    // Get all params and print them
    for (int i = 0; i < 10; i++) {
        int v = 0;
        glGetIntegerv(params[i], &v);
        gl_log("%s = %i\n", names[i], v);
    }

    // Print the other params
    int v[2];
    v[0] = v[1] = 0;
    glGetIntegerv(params[10], v);
    gl_log("%s = %i, %i\n", names[10], v[0], v[1]);

    unsigned char s = 0;
    glGetBooleanv(params[11], &s);
    gl_log("%s = %u\n", names[11], (unsigned int)s);

    gl_log("=============================\n\n");
    
    return 0;
}
