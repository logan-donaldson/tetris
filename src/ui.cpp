#include <SDL.h>
#include <iostream>
#include <format>
#include "main.h"
#include "ui.h"

Ui::Ui() {
	this->curScore = 0;
	this->smallFont = nullptr;
	this->bigFont = nullptr;
	this->scoreText = Texture();
	this->nextText = Texture();
	this->tText = Texture();
	this->eText = Texture(); 
	this->rText = Texture();
	this->iText = Texture();
	this->sText = Texture();
	this->curScoreText = Texture();
	this->restartText = Texture();
}

Ui::~Ui() { 
	this->free();
}

bool Ui::init() {
	this->smallFont = TTF_OpenFont("assets/fonts/orbitron_medium.ttf", 28);
	this->bigFont = TTF_OpenFont("assets/fonts/orbitron_medium.ttf", 48);
	if (!this->smallFont || !this->bigFont) {
		std::cout << std::format("Failed to load global font! SDL_ttf Error: {}\n", TTF_GetError());
		return false;
	}
	SDL_Color textColor = { 0xFF, 0xFF, 0xFF };
	if (!this->scoreText.loadFromRenderedText("Score", textColor, this->smallFont) ||
		!this->nextText.loadFromRenderedText("Next", textColor, this->smallFont) ||
		!this->tText.loadFromRenderedText("T", textColor, this->bigFont) ||
		!this->eText.loadFromRenderedText("E", textColor, this->bigFont) ||
		!this->rText.loadFromRenderedText("R", textColor, this->bigFont) ||
		!this->iText.loadFromRenderedText("I", textColor, this->bigFont) ||
		!this->sText.loadFromRenderedText("S", textColor, this->bigFont) ||
		!this->curScoreText.loadFromRenderedText(std::to_string(this->curScore), textColor, this->smallFont) ||
		!this->restartText.loadFromRenderedText("Press 'R' to Restart", textColor, this->smallFont)) {
		printf("Failed to render text texture!\n");
		return false;
	}
	return true;
}

void Ui::free() {
	TTF_CloseFont(this->smallFont);
	TTF_CloseFont(this->bigFont);
	this->smallFont = nullptr;
	this->bigFont = nullptr;
	this->scoreText.free();
	this->nextText.free();
	this->tText.free();
	this->eText.free();
	this->rText.free();
	this->iText.free();
	this->sText.free();
	this->curScoreText.free();
	this->restartText.free();
}

int Ui::getCurScore() {
	return this->curScore;
}

void Ui::renderUI(bool running) {
	if (!running) {
		restartText.render(Global::window->getWidth() / 2 - restartText.getWidth() / 2, Global::window->getHeight() / 2 - restartText.getHeight() / 2);
		return;
	}
	Global::renderer->renderRect(Global::Global::BUFFER, Global::BUFFER, 10*Global::BLOCK_SIZE, 20*Global::BLOCK_SIZE, false);
	Global::renderer->renderRect(20 + (10*Global::BLOCK_SIZE) + Global::BUFFER, Global::BUFFER, 100, 100, false);
	Global::renderer->renderRect(20 + (10 * Global::BLOCK_SIZE) + Global::BUFFER, Global::BUFFER + 100 + Global::BUFFER, 100, 200, false);
	scoreText.render(Global::BUFFER + (10 * Global::BLOCK_SIZE) + Global::BUFFER + 4, Global::BUFFER + 1);
	nextText.render(Global::BUFFER + (10 * Global::BLOCK_SIZE) + Global::BUFFER + 13, Global::BUFFER + 100 + Global::BUFFER + 2);
	this->curScoreText.render(Global::BUFFER + (10 * Global::BLOCK_SIZE) + Global::BUFFER + 50 - curScoreText.getWidth() / 2, Global::BUFFER + 1 + scoreText.getHeight() + curScoreText.getHeight() / 2);
	int letterBuffer{ 0 };
	tText.render(Global::BUFFER + (10 * Global::BLOCK_SIZE) + Global::BUFFER + 50 - tText.getWidth() / 2, Global::BUFFER + 100 + Global::BUFFER + 200 + Global::BUFFER);
	letterBuffer += tText.getHeight() + 5;
	eText.render(Global::BUFFER + (10 * Global::BLOCK_SIZE) + Global::BUFFER + 50 - eText.getWidth() / 2, Global::BUFFER + 100 + Global::BUFFER + 200 + Global::BUFFER + letterBuffer);
	letterBuffer += eText.getHeight() + 5;
	tText.render(Global::BUFFER + (10 * Global::BLOCK_SIZE) + Global::BUFFER + 50 - tText.getWidth() / 2, Global::BUFFER + 100 + Global::BUFFER + 200 + Global::BUFFER + letterBuffer);
	letterBuffer += tText.getHeight() + 5;
	rText.render(Global::BUFFER + (10 * Global::BLOCK_SIZE) + Global::BUFFER + 50 - rText.getWidth() / 2, Global::BUFFER + 100 + Global::BUFFER + 200 + Global::BUFFER + letterBuffer);
	letterBuffer += rText.getHeight() + 5;
	iText.render(Global::BUFFER + (10 * Global::BLOCK_SIZE) + Global::BUFFER + 50 - iText.getWidth() / 2, Global::BUFFER + 100 + Global::BUFFER + 200 + Global::BUFFER + letterBuffer);
	letterBuffer += sText.getHeight() + 5;
	sText.render(Global::BUFFER + (10 * Global::BLOCK_SIZE) + Global::BUFFER + 50 - sText.getWidth() / 2, Global::BUFFER + 100 + Global::BUFFER + 200 + Global::BUFFER + letterBuffer);
}

void Ui::incrementCurScore(int inc) {
	this->curScore += inc;
	this->curScoreText.loadFromRenderedText(std::to_string(this->curScore), { 0xFF, 0xFF, 0xFF }, this->smallFont);
}

