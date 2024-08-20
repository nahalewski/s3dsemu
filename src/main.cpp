#include <switch.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_opengl.h>
#include <stdio.h>
#include <stdlib.h>

#define LOAD_GL_FUNCTION(type, name) \
    name = (type)SDL_GL_GetProcAddress(#name); \
    if (!name) { \
        printf("Failed to load %s\n", #name); \
        return 1; \
    }

// Declare function pointers for OpenGL functions
PFNGLCREATESHADERPROC glCreateShader = NULL;
PFNGLSHADERSOURCEPROC glShaderSource = NULL;
PFNGLCOMPILESHADERPROC glCompileShader = NULL;
PFNGLGETSHADERIVPROC glGetShaderiv = NULL;
PFNGLGETSHADERINFOLOGPROC glGetShaderInfoLog = NULL;
PFNGLCREATEPROGRAMPROC glCreateProgram = NULL;
PFNGLATTACHSHADERPROC glAttachShader = NULL;
PFNGLLINKPROGRAMPROC glLinkProgram = NULL;
PFNGLGETPROGRAMIVPROC glGetProgramiv = NULL;
PFNGLGETPROGRAMINFOLOGPROC glGetProgramInfoLog = NULL;
PFNGLDELETESHADERPROC glDeleteShader = NULL;
PFNGLUSEPROGRAMPROC glUseProgram = NULL;
PFNGLGENBUFFERSPROC glGenBuffers = NULL;
PFNGLBINDBUFFERPROC glBindBuffer = NULL;
PFNGLBUFFERDATAPROC glBufferData = NULL;
PFNGLVERTEXATTRIBPOINTERPROC glVertexAttribPointer = NULL;
PFNGLENABLEVERTEXATTRIBARRAYPROC glEnableVertexAttribArray = NULL;
PFNGLDELETEBUFFERSPROC glDeleteBuffers = NULL;
PFNGLDELETEPROGRAMPROC glDeleteProgram = NULL;

// Vertex shader source code
const GLchar* vertexShaderSource = R"(
    attribute vec3 position;
    void main() {
        gl_Position = vec4(position, 1.0);
    }
)";

// Fragment shader source code
const GLchar* fragmentShaderSource = R"(
    precision mediump float;
    void main() {
        gl_FragColor = vec4(1.0, 0.0, 0.0, 1.0); // Red color
    }
)";

GLuint compileShader(GLenum type, const GLchar* source) {
    GLuint shader = glCreateShader(type);
    glShaderSource(shader, 1, &source, NULL);
    glCompileShader(shader);

    GLint success;
    glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
    if (!success) {
        GLchar infoLog[512];
        glGetShaderInfoLog(shader, sizeof(infoLog), NULL, infoLog);
        printf("ERROR::SHADER::COMPILATION_FAILED\n%s\n", infoLog);
        return 0;
    }
    return shader;
}

GLuint createProgram() {
    GLuint vertexShader = compileShader(GL_VERTEX_SHADER, vertexShaderSource);
    GLuint fragmentShader = compileShader(GL_FRAGMENT_SHADER, fragmentShaderSource);
    GLuint shaderProgram = glCreateProgram();

    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);

    GLint success;
    glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
    if (!success) {
        GLchar infoLog[512];
        glGetProgramInfoLog(shaderProgram, sizeof(infoLog), NULL, infoLog);
        printf("ERROR::PROGRAM::LINKING_FAILED\n%s\n", infoLog);
        return 0;
    }

    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);

    return shaderProgram;
}

int main(int argc, char** argv) {
    // Initialize the services
    socketInitializeDefault();
    nxlinkStdio();

    // Initialize SDL
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        printf("SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
        return 1;
    }

    SDL_Window* window = SDL_CreateWindow("SDL2 OpenGL", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 1280, 720, SDL_WINDOW_OPENGL);
    if (!window) {
        printf("Window could not be created! SDL_Error: %s\n", SDL_GetError());
        return 1;
    }

    SDL_GLContext context = SDL_GL_CreateContext(window);
    if (!context) {
        printf("OpenGL context could not be created! SDL_Error: %s\n", SDL_GetError());
        return 1;
    }

    // Load OpenGL functions
    LOAD_GL_FUNCTION(PFNGLCREATESHADERPROC, glCreateShader);
    LOAD_GL_FUNCTION(PFNGLSHADERSOURCEPROC, glShaderSource);
    LOAD_GL_FUNCTION(PFNGLCOMPILESHADERPROC, glCompileShader);
    LOAD_GL_FUNCTION(PFNGLGETSHADERIVPROC, glGetShaderiv);
    LOAD_GL_FUNCTION(PFNGLGETSHADERINFOLOGPROC, glGetShaderInfoLog);
    LOAD_GL_FUNCTION(PFNGLCREATEPROGRAMPROC, glCreateProgram);
    LOAD_GL_FUNCTION(PFNGLATTACHSHADERPROC, glAttachShader);
    LOAD_GL_FUNCTION(PFNGLLINKPROGRAMPROC, glLinkProgram);
    LOAD_GL_FUNCTION(PFNGLGETPROGRAMIVPROC, glGetProgramiv);
    LOAD_GL_FUNCTION(PFNGLGETPROGRAMINFOLOGPROC, glGetProgramInfoLog);
    LOAD_GL_FUNCTION(PFNGLDELETESHADERPROC, glDeleteShader);
    LOAD_GL_FUNCTION(PFNGLUSEPROGRAMPROC, glUseProgram);
    LOAD_GL_FUNCTION(PFNGLGENBUFFERSPROC, glGenBuffers);
    LOAD_GL_FUNCTION(PFNGLBINDBUFFERPROC, glBindBuffer);
    LOAD_GL_FUNCTION(PFNGLBUFFERDATAPROC, glBufferData);
    LOAD_GL_FUNCTION(PFNGLVERTEXATTRIBPOINTERPROC, glVertexAttribPointer);
    LOAD_GL_FUNCTION(PFNGLENABLEVERTEXATTRIBARRAYPROC, glEnableVertexAttribArray);
    LOAD_GL_FUNCTION(PFNGLDELETEBUFFERSPROC, glDeleteBuffers);
    LOAD_GL_FUNCTION(PFNGLDELETEPROGRAMPROC, glDeleteProgram);

    glViewport(0, 0, 1280, 720);

    GLuint shaderProgram = createProgram();
    glUseProgram(shaderProgram);

    GLfloat vertices[] = {
        0.0f,  0.5f, 0.0f,
       -0.5f, -0.5f, 0.0f,
        0.5f, -0.5f, 0.0f,
    };

    GLuint VBO;
    glGenBuffers(1, &VBO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (GLvoid*)0);
    glEnableVertexAttribArray(0);

    glBindBuffer(GL_ARRAY_BUFFER, 0);

    // Initialize HID (for input handling)
    padConfigureInput(1, HidNpadStyleSet_NpadStandard);  // Configure the input for one controller
    PadState pad;
    padInitializeDefault(&pad);

    // Main loop
    bool running = true;
    while (running) {
        padUpdate(&pad);  // Update the pad state

        u64 kDown = padGetButtonsDown(&pad);  // Get the buttons that were pressed this frame

        // Check if the Plus button was pressed
        if (kDown & HidNpadButton_Plus) {
            running = false;
        }

        glClear(GL_COLOR_BUFFER_BIT);
        glBindBuffer(GL_ARRAY_BUFFER, VBO);
        glDrawArrays(GL_TRIANGLES, 0, 3);

        SDL_GL_SwapWindow(window);
    }

    glDeleteBuffers(1, &VBO);
    glDeleteProgram(shaderProgram);

    SDL_GL_DeleteContext(context);
    SDL_DestroyWindow(window);
    SDL_Quit();
    socketExit();
    return 0;
}
