#ifndef MAIN_H
#define MAIN_H
#include <SDL.h>
#include <SDL_ttf.h>
#include "window.h"
#include "texture.h"
#include "game.h"

struct Global {
	const static int BLOCK_SIZE{ 32 };
	const static int INIT_WINDOW_WIDTH{ 32 * 15 };
	const static int INIT_WINDOW_HEIGHT{ 32 * 20 + 40 };
	const static int BUFFER{ 20 };
	static Window* window;
	static SDL_Renderer* renderer;
	static Game* game;
};

#endif
