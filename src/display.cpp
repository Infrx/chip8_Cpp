#ifndef DISPLAY_CPP
#define DISPLAY_CPP

#include "display.h"



bool display::init()
{
	SDL_Init(SDL_INIT_VIDEO);
    window = SDL_CreateWindow("CHIP-8 Emulator",SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,CHIP8_WIDTH * SCALE, CHIP8_HEIGHT * SCALE,SDL_WINDOW_SHOWN);
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    texture = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_ARGB8888, SDL_TEXTUREACCESS_STREAMING, CHIP8_WIDTH, CHIP8_HEIGHT);
    memset(pixels, 0, sizeof(pixels));
    return true;
}

void display::close()
{
    SDL_DestroyTexture(texture);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}

void display::drawGraphics(const uint32_t* pixels)
{
    SDL_UpdateTexture(texture, nullptr, pixels, CHIP8_WIDTH * sizeof(uint32_t));
    SDL_RenderClear(renderer);
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderCopy(renderer, texture, nullptr, nullptr);
    SDL_RenderPresent(renderer);
}


bool display::keyPresses(uint8_t* hexpad)
{
    bool quit = false;
    while (SDL_PollEvent(&event) != 0) {
		switch (event.type)
		{
			case SDL_QUIT:
				quit = true;
			break;

			case SDL_KEYDOWN:
			{
				switch (event.key.keysym.sym)
				{
					case SDLK_ESCAPE:
						quit = true;
					break;

					case SDLK_x:
						hexpad[0] = 1;
					break;

					case SDLK_1:
						hexpad[1] = 1;
					break;

					case SDLK_2:
						hexpad[2] = 1;
					break;

					case SDLK_3:
						hexpad[3] = 1;
					break;

					case SDLK_q:
						hexpad[4] = 1;
					break;

					case SDLK_w:
						hexpad[5] = 1;
					break;

					case SDLK_e:
						hexpad[6] = 1;
					break;

					case SDLK_a:
						hexpad[7] = 1;
					break;

					case SDLK_s:
						hexpad[8] = 1;
					break;

					case SDLK_d:
						hexpad[9] = 1;
					break;

					case SDLK_z:
						hexpad[0xA] = 1;
					break;

					case SDLK_c:
						hexpad[0xB] = 1;
					break;

					case SDLK_4:
						hexpad[0xC] = 1;
					break;

					case SDLK_r:
						hexpad[0xD] = 1;
					break;

					case SDLK_f:
						hexpad[0xE] = 1;
					break;

					case SDLK_v:
						hexpad[0xF] = 1;
					break;
				}
				break;
			} 
			case SDL_KEYUP:
			{
				switch (event.key.keysym.sym)
				{
					case SDLK_x:
						hexpad[0] = 0;
					break;

					case SDLK_1:
						hexpad[1] = 0;
					break;

					case SDLK_2:
						hexpad[2] = 0;
					break;

					case SDLK_3:
						hexpad[3] = 0;
					break;

					case SDLK_q:
						hexpad[4] = 0;
					break;

					case SDLK_w:
						hexpad[5] = 0;
					break;

					case SDLK_e:
						hexpad[6] = 0;
					break;

					case SDLK_a:
						hexpad[7] = 0;
					break;

					case SDLK_s:
						hexpad[8] = 0;
					break;

					case SDLK_d:
						hexpad[9] = 0;
					break;

					case SDLK_z:
						hexpad[0xA] = 0;
					break;

					case SDLK_c:
						hexpad[0xB] = 0;
					break;

					case SDLK_4:
						hexpad[0xC] = 0;
					break;

					case SDLK_r:
						hexpad[0xD] = 0;
					break;

					case SDLK_f:
						hexpad[0xE] = 0;
					break;

					case SDLK_v:
						hexpad[0xF] = 0;
					break;
				}
			} break;
		}
	}
	return quit;
}
#endif

