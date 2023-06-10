#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <iostream>
#include <format>
#include "main.h"
#include "window.h"
#include "util.h"


bool init() {

	if (SDL_Init(SDL_INIT_EVERYTHING) < 0) {
		std::cout << std::format("SDL could not initialize! SDL Error: {}\n", SDL_GetError());
		return false;
	}

	if (!SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1")) {
		std::cout << ("Warning: Linear texture filtering not enabled!");
	}

	Global::window = new Window();
	if (!Global::window->init()) return false;

	Global::renderer = Global::window->createRenderer();
	if (!Global::renderer) {
		std::cout << std::format("Renderer could not be created! SDL Error: {}\n", SDL_GetError());
		return false;
	}
	SDL_SetRenderDrawColor(Global::renderer, 0xFF, 0xFF, 0xFF, 0xFF);
	SDL_RenderSetLogicalSize(Global::renderer, Global::INIT_WINDOW_WIDTH, Global::INIT_WINDOW_HEIGHT);

	int imgFlags = IMG_INIT_PNG;
	if (!(IMG_Init(imgFlags) & imgFlags)) {
		std::cout << std::format("SDL_image could not initialize! SDL_image Error: {}\n", IMG_GetError());
		return false;
	}

	if (TTF_Init() == -1) {
		std::cout << std::format("SDL_ttf could not initialize! SDL_ttf Error: {}\n", TTF_GetError());
		return false;
	}

	Global::game = new Game();
	if (!Global::game->init()) return false;

	return true;
}

void clean() {
	Global::window->free();
	delete Global::window;

	SDL_DestroyRenderer(Global::renderer);

	Global::game->free();
	delete Global::game;

	Global::renderer = nullptr;
	Global::game = nullptr;

	TTF_Quit();
	IMG_Quit();
	SDL_Quit();
}