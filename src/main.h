#ifndef MAIN_H
#define MAIN_H
#include <SDL.h>
#include <atomic>
#include "window.h"
#include "renderer.h"
#include "game.h"
#include "timer.h"

struct Global {
	const static int BLOCK_SIZE{ 32 };
	const static int INIT_WINDOW_WIDTH{ 32 * 15 };
	const static int INIT_WINDOW_HEIGHT{ 32 * 20 + 40 };
	const static int BUFFER{ 20 };
	static Uint32 dropRate;
	static Window* window;
	static Renderer* renderer;
	static Game* game;
	static Timer* timer;
};

#endif
