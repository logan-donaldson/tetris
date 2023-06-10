#include "main.h"
#include "game.h"
#include "ui.h"

Game::Game() { 
	this->ui = Ui();
};

Game::~Game() {
	this->free();
};

bool Game::init() {
	if (!this->ui.init()) return false;
	return true;
}

void Game::free() {
	this->ui.free();
}

void Game::render() {
	SDL_SetRenderDrawColor(Global::renderer, 0x00, 0x00, 0x00, 0x00);
	SDL_RenderClear(Global::renderer);
	this->ui.renderUI();
	SDL_RenderPresent(Global::renderer);
}