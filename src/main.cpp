#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <iostream>
#include <atomic>
#include <time.h>
#include "main.h"
#include "window.h"
#include "util.h"
#include "ui.h"
#include "timer.h"

Window* Global::window{nullptr};
Renderer* Global::renderer{nullptr};
Game* Global::game{nullptr};
Timer* Global::timer{nullptr};
Uint32 Global::dropRate = 500;

int main(int argc, char* argv[]) { 
	std::cout << "Hello SDL\n";
	srand((unsigned int) time(NULL));
	
	if (!init()) return -1;

	bool quit{ false };
	SDL_Event e{ };
	Global::timer->start();
	while (!quit) {
		if (Global::timer->getTicks() >= Global::dropRate) {
			Global::timer->stop();
			Global::game->dropMino();
			Global::timer->start();
		}
		while (SDL_PollEvent(&e)) {
			if (e.type == SDL_QUIT) quit = true;
			Global::window->handleEvent(e);
			if (!Global::window->getMinimized()) {
				Global::game->handleEvent(e);
			}
		}
		if (!Global::window->getMinimized()) {
			Global::game->render();
		}
	}

	clean();
	return 0;
}