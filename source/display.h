#ifndef DISPLAY_H
#define DISPLAY_H

#include <SDL.h>
#include <iostream>
#include <cstring>

// CHIP-8 display dimensions
const int CHIP8_WIDTH = 64;
const int CHIP8_HEIGHT = 32;
const int SCALE = 10;  // Scaling factor for better visibility

class display
{
public:
	bool init();
	void close();
	void drawGraphics(const uint32_t* pixels);
	//void clear();
	// SDL related variables
	SDL_Window* window = nullptr;
	SDL_Renderer* renderer = nullptr;
	SDL_Texture* texture = nullptr;
	uint32_t pixels[CHIP8_WIDTH * CHIP8_HEIGHT]{0};
	SDL_Event event;

	//functions
};

#endif