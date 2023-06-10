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
		!this->sText.loadFromRenderedText("S", textColor, this->bigFont)) {
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
}

int Ui::getCurScore() {
	return this->curScore;
}

void Ui::renderRect(int x, int y, int w, int h) {
	SDL_Rect outlineRect = { x, y, w, h };
	SDL_SetRenderDrawColor(Global::renderer, 0xFF, 0xFF, 0xFF, 0xFF);
	SDL_RenderDrawRect(Global::renderer, &outlineRect);
}

void Ui::renderUI() {
	renderRect(Global::Global::BUFFER, Global::BUFFER, 10*Global::BLOCK_SIZE, 20*Global::BLOCK_SIZE);
	renderRect(20 + (10*Global::BLOCK_SIZE) + Global::BUFFER, Global::BUFFER, 100, 100);
	renderRect(20 + (10 * Global::BLOCK_SIZE) + Global::BUFFER, Global::BUFFER + 100 + Global::BUFFER, 100, 200);
	scoreText.render(Global::BUFFER + (10 * Global::BLOCK_SIZE) + Global::BUFFER + 4, Global::BUFFER + 1);
	nextText.render(Global::BUFFER + (10 * Global::BLOCK_SIZE) + Global::BUFFER + 13, Global::BUFFER + 100 + Global::BUFFER + 2);
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

