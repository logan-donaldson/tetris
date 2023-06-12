#include "main.h"
#include "game.h"
#include "ui.h"
#include "spawner.h"
#include <iostream>

Game::Game() {
	this->activeMino = this->spawnMino();
	this->nextMino = this->spawnMino();
	this->ui = Ui();
	this->spawner = Spawner();
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

Mino& Game::getActiveMino() {
	return this->activeMino;
}

Mino& Game::getNextMino() {
	return this->nextMino;
}

void Game::setActiveMino(Mino mino) {
	this->activeMino = mino;
}

void Game::setNextMino(Mino mino) {
	this->nextMino = mino;
}

void Game::render() {
	Global::renderer->setDrawColor(0x00, 0x00, 0x00, 0x00);
	Global::renderer->renderClear();
	this->ui.renderUI();
	this->activeMino.render();
	this->nextMino.renderAsNext();
	for (auto& mino : this->lockedMinos) {
		mino.render();
	}
	Global::renderer->renderPresent();
}

void Game::addMino(Mino mino) {
	this->lockedMinos.push_back(mino);
}

void Game::handleEvent(SDL_Event& e) {
	if (e.type == SDL_KEYDOWN) {
		if (e.key.keysym.sym == SDLK_d) {
			this->activeMino.rotate(true);
		}
		if (e.key.keysym.sym == SDLK_a) {
			this->activeMino.rotate(false);
		}
		if (e.key.keysym.sym == SDLK_LEFT) {
			this->activeMino.translate('L');
		}
		if (e.key.keysym.sym == SDLK_RIGHT) {
			this->activeMino.translate('R');
		}
		if (e.key.keysym.sym == SDLK_DOWN) {
			Global::dropRate = 100;
		}
	}
	if (e.type == SDL_KEYUP) {
		if (e.key.keysym.sym == SDLK_DOWN) {
			Global::dropRate = 500;
		}
	}
}

Mino Game::spawnMino() {
	return this->spawner.spawnMino();
}