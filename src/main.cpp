#include <switch.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL2_gfxPrimitives.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char **argv) {
    // Initialize SDL
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        printf("Failed to initialize SDL: %s\n", SDL_GetError());
        return -1;
    }

    // Create an SDL window
    SDL_Window *window = SDL_CreateWindow("Switch SDL2 Example", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 1280, 720, SDL_WINDOW_SHOWN);
    if (!window) {
        printf("Failed to create SDL window: %s\n", SDL_GetError());
        SDL_Quit();
        return -1;
    }

    // Create an SDL renderer
    SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (!renderer) {
        printf("Failed to create SDL renderer: %s\n", SDL_GetError());
        SDL_DestroyWindow(window);
        SDL_Quit();
        return -1;
    }

    // Initialize HID (for input handling)
    hidInit();

    // Main loop
    while (appletMainLoop()) {
        // Scan input
        hidScanInput();

        // Get the state of the input
        u64 kDown = hidKeysDown(CONTROLLER_P1_AUTO);

        // Check if the Plus button was pressed
        if (kDown & KEY_PLUS) {
            break; // Exit the loop
        }

        // Clear the screen
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderClear(renderer);

        // Draw some graphics primitives using SDL2_gfx
        SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255); // Red color
        boxRGBA(renderer, 100, 100, 200, 200, 255, 0, 0, 255); // Draw a filled box

        // Present the rendered content
        SDL_RenderPresent(renderer);

        // Wait for V-Sync (or use SDL_Delay if needed)
        SDL_Delay(16); // Roughly 60 FPS
    }

    // Clean up
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
    hidExit();
    return 0;
}