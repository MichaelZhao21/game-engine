#ifndef LOG_H
#define LOG_H

#include <time.h>
#include <stdarg.h>

#define GL_LOG_FILE "gl.log"

int restart_gl_log();
int gl_log(const char* msg, ...);
int gl_log_err(const char* msg, ...);
int log_gl_params();

#endif // LOG_H
