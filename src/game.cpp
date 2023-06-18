#include "main.h"
#include "game.h"
#include "ui.h"
#include "spawner.h"
#include "mino.h"
#include <iostream>
#include <unordered_map>
#include <algorithm>

Game::Game() {
	this->activeMino = this->spawnMino();
	this->nextMino = this->spawnMino();
	this->ui = Ui();
	this->spawner = Spawner();
	for (int i = 0; i < 22; ++i) {
		std::vector<int> v(10, 0);
		this->board.push_back(v);
	}
	this->running = true;
	this->mixer = Mixer();
}

Game::~Game() {
	this->free();
}

bool Game::init() {
	if (!this->ui.init()) return false;
	if (!this->mixer.init()) return false;
	this->mixer.playMusic();
	return true;
}

void Game::free() {
	this->ui.free();
	this->mixer.free();
}

Mino& Game::getActiveMino() {
	return this->activeMino;
}

Mino& Game::getNextMino() {
	return this->nextMino;
}

void Game::setActiveMino(Mino mino) {
	this->activeMino = mino;
	this->updateBoard(false);
}

void Game::setNextMino(Mino mino) {
	this->nextMino = mino;
}

void Game::render() {
	Global::renderer->setDrawColor(0x00, 0x00, 0x00, 0x00);
	Global::renderer->renderClear();
	this->ui.renderUI(this->running);
	if (this->running) {
		this->nextMino.renderAsNext();
		for (int i = 2; i < this->board.size(); ++i) {
			for (int j = 0; j < this->board[i].size(); ++j) {
				if (this->board[i][j] != 0) {
					int y = Global::BUFFER + (Global::BLOCK_SIZE * (i - 2));
					if (y > 0) {
						int x = Global::BUFFER + (Global::BLOCK_SIZE * j);
						Global::renderer->renderRect(x, y, Global::BLOCK_SIZE, Global::BLOCK_SIZE, this->board[i][j] == 1);
					}
				}
			}
		}
	} 
	Global::renderer->renderPresent();
}

void Game::handleEvent(SDL_Event& e) {
	if (e.type == SDL_KEYDOWN) {
		if (this->running) {
			if (e.key.keysym.sym == SDLK_d) {
				this->activeMino.rotate(true);
				if (this->checkCollisions()) {
					this->activeMino.rotate(false);
				}
				else {
					this->updateBoard(false);
					this->mixer.playRotateSound();
				}
			}
			if (e.key.keysym.sym == SDLK_a) {
				this->activeMino.rotate(false);
				if (this->checkCollisions()) {
					this->activeMino.rotate(true);
				}
				else {
					this->updateBoard(false);
					this->mixer.playRotateSound();
				}
			}
			if (e.key.keysym.sym == SDLK_LEFT) {
				this->activeMino.translate('L');
				if (this->checkCollisions())
					this->activeMino.translate('R');
				else
					this->updateBoard(false);
			}
			if (e.key.keysym.sym == SDLK_RIGHT) {
				this->activeMino.translate('R');
				if (this->checkCollisions())
					this->activeMino.translate('L');
				else
					this->updateBoard(false);
			}
			if (e.key.keysym.sym == SDLK_DOWN) {
				Global::dropRate = 100;
			}
		}
		if (!this->running && e.key.keysym.sym == SDLK_r) {
			this->restart();
			this->mixer.playMusic();
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

bool Game::checkCollisions() {
	return this->activeMino.checkWallCollision() || this->activeMino.checkMinoCollision();
}

void Game::dropMino() {
	this->getActiveMino().translate('D');
	if (this->checkCollisions()) {
		this->getActiveMino().translate('U');
		this->updateBoard(true);
		if (std::find(this->board[1].begin(), this->board[1].end(), 1) != this->board[1].end()) {
			this->running = false;
			this->mixer.pauseMusic();
		}
		this->setActiveMino(Global::game->getNextMino());
		this->setNextMino(Global::game->spawnMino());
		int num_cleared{ this->checkLines() };
		switch (num_cleared) {
			case 1:
				this->ui.incrementCurScore(40);
				break;
			case 2:
				this->ui.incrementCurScore(100);
				break;
			case 3:
				this->ui.incrementCurScore(400);
				break;
			case 4:
				this->ui.incrementCurScore(1200);
				break;
			default:
				break;
		}
	} else {
		if (Global::dropRate == 100)
			this->ui.incrementCurScore(1);
		this->updateBoard(false);
	}
}

int Game::checkLines() {
	int count = 0;
	for (int i = 0; i < this->board.size(); ++i) {
		if (this->board[i][0] == 1 && std::equal(this->board[i].begin() + 1, this->board[i].end(), this->board[i].begin())) {
			for (int j = i; j >= 2; --j)
				this->board[j] = this->board[j-1];
			count += 1;
		}
	}
	return count;
}

std::vector<std::vector<int>>& Game::getBoard() {
	return this->board;
}

void Game::updateBoard(bool freeze) {
	int val = freeze ? 1 : 2;

	for (int i = 0; i < this->board.size(); ++i) {
		for (int j = 0; j < this->board[i].size(); ++j) {
			if (this->board[i][j] == 2)
				this->board[i][j] = 0;
		}
	}

	for (int i = 0; i < this->activeMino.getLayout().size(); ++i) {
		for (int j = 0; j < this->activeMino.getLayout()[i].size(); ++j) {
			if (this->activeMino.getLayout()[i][j])
				this->board[this->activeMino.getLocation().second + i][this->activeMino.getLocation().first + j] = val;
		}
	}
}

void Game::restart() {
	Global::game = new Game();
	Global::game->init();
	delete this;
}
