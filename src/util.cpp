#include <SDL.h>
#include <SDL_image.h>
#include <SDL_mixer.h>
#include <SDL_ttf.h>
#include <iostream>
#include <format>
#include "main.h"
#include "window.h"
#include "util.h"
#include "timer.h"

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

	Global::renderer = new Renderer();
	Global::renderer->setSDLRenderer(Global::window->createRenderer());
	if (!Global::renderer) {
		std::cout << std::format("Renderer could not be created! SDL Error: {}\n", SDL_GetError());
		return false;
	}
	Global::renderer->setDrawColor(0xFF, 0xFF, 0xFF, 0xFF);
	Global::renderer->setLogicalSize(Global::INIT_WINDOW_WIDTH, Global::INIT_WINDOW_HEIGHT);

	int imgFlags = IMG_INIT_PNG;
	if (!(IMG_Init(imgFlags) & imgFlags)) {
		std::cout << std::format("SDL_image could not initialize! SDL_image Error: {}\n", IMG_GetError());
		return false;
	}

	if (TTF_Init() == -1) {
		std::cout << std::format("SDL_ttf could not initialize! SDL_ttf Error: {}\n", TTF_GetError());
		return false;
	}

	if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0)
	{
		printf("SDL_mixer could not initialize! SDL_mixer Error: %s\n", Mix_GetError());
		return false;

	}

	Global::game = new Game();
	if (!Global::game->init()) return false;

	Global::timer = new Timer();

	return true;
}

void clean() {
	Global::window->free();
	delete Global::window;

	Global::renderer->free();
	delete Global::renderer;

	Global::game->free();
	delete Global::game;

	delete Global::timer;

	Global::window = nullptr;
	Global::renderer = nullptr;
	Global::game = nullptr;
	Global::timer = nullptr;

	Mix_Quit();
	TTF_Quit();
	IMG_Quit();
	SDL_Quit();
}