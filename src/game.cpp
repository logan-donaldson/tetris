#include "main.h"
#include "game.h"
#include "ui.h"
#include <iostream>

Game::Game() {
	this->activeMino = Mino('I');
	this->ui = Ui();
}

Game::~Game() {
	this->free();
}

bool Game::init() {
	if (!this->ui.init()) return false;
	return true;
}

void Game::free() {
	this->ui.free();
}

void Game::render() {
	Global::renderer->setDrawColor(0x00, 0x00, 0x00, 0x00);
	Global::renderer->renderClear();
	this->ui.renderUI();
	this->activeMino.render();
	for (auto& mino : this->lockedMinos) {
		mino.render();
	}
	Global::renderer->renderPresent();
}

void Game::addMino(Mino mino) {
	this->lockedMinos.push_back(mino);
}

void Game::handleEvent(SDL_Event& e) {
    if (e.type == SDL_KEYDOWN && e.key.keysym.sym == SDLK_d) {
		this->activeMino.rotate(true);
    }
	if (e.type == SDL_KEYDOWN && e.key.keysym.sym == SDLK_a) {
		this->activeMino.rotate(false);
	}
}