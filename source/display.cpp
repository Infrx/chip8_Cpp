#ifndef DISPLAY_CPP
#define DISPLAY_CCPP

#include "display.h"



bool display::init()
{
    // Initialize SDL
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        std::cerr << "SDL could not initialize! SDL_Error: " << SDL_GetError() << std::endl;
        return false;
    }

    // Create window
    window = SDL_CreateWindow("CHIP-8 Emulator",
        SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
        CHIP8_WIDTH * SCALE, CHIP8_HEIGHT * SCALE,
        SDL_WINDOW_SHOWN);
    if (!window) {
        std::cerr << "Window could not be created! SDL_Error: " << SDL_GetError() << std::endl;
        return false;
    }

    // Create renderer
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (!renderer) {
        std::cerr << "Renderer could not be created! SDL_Error: " << SDL_GetError() << std::endl;
        return false;
    }

    // Create texture
    texture = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_ARGB8888, SDL_TEXTUREACCESS_STREAMING, CHIP8_WIDTH, CHIP8_HEIGHT);
    if (!texture) {
        std::cerr << "Texture could not be created! SDL_Error: " << SDL_GetError() << std::endl;
        return false;
    }

    // Initialize the pixel buffer to black
    memset(pixels, 0, sizeof(pixels));

    return true;
}

void display::close()
{
    if (texture) {
        SDL_DestroyTexture(texture);
    }
    if (renderer) {
        SDL_DestroyRenderer(renderer);
    }
    if (window) {
        SDL_DestroyWindow(window);
    }
    SDL_Quit();
}

void display::drawGraphics(const uint32_t* pixels)
{
    // knows that pixels is 64 x 32 due to width*size
    SDL_UpdateTexture(texture, nullptr, pixels, CHIP8_WIDTH * sizeof(uint32_t));

    // Clear renderer
    SDL_RenderClear(renderer);
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255); // Black background
    // Copy texture to renderer
    SDL_RenderCopy(renderer, texture, nullptr, nullptr);

    // Present renderer
    SDL_RenderPresent(renderer);
}
#endif