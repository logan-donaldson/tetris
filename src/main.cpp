#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <iostream>
#include <atomic>
#include "main.h"
#include "window.h"
#include "util.h"
#include "ui.h"

Window* Global::window{nullptr};
Renderer* Global::renderer{nullptr};
Game* Global::game{nullptr};
std::atomic<Uint32> Global::dropRate = 500;

int main(int argc, char* argv[]) { 
	std::cout << "Hello SDL\n";
	
	if (!init()) return -1;

	SDL_TimerID timerID = SDL_AddTimer(Global::dropRate, dropCallback, nullptr);

	bool quit{ false };
	SDL_Event e{ };
	while (!quit) {
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

	SDL_RemoveTimer(timerID);
	clean();
	return 0;
}