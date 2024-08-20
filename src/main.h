#ifndef MAIN_H
#define MAIN_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_opengl.h>
#include <switch.h>

// Shader source code
extern const GLchar* vertexShaderSource;
extern const GLchar* fragmentShaderSource;

// Function prototypes
GLuint compileShader(GLenum type, const GLchar* source);
GLuint createProgram();

#endif // MAIN_H
