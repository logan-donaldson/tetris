#include <string>
#include <format>
#include <iostream>
#include <SDL.h>
#include <SDL_image.h>
#include "texture.h"
#include "main.h"

Texture::Texture() {
	this->sdlTexture = nullptr;
	this->width = 0;
	this->height = 0;
}

Texture::~Texture() {
	this->free();
}

void Texture::free() {
	if (this->sdlTexture) {
		SDL_DestroyTexture(this->sdlTexture);
		this->sdlTexture = nullptr;
		this->width = 0;
		this->height = 0;
	}
}

bool Texture::loadFromFile(std::string path) {
	this->free();

	SDL_Surface* loadedSurface = IMG_Load(path.c_str());
	if (!loadedSurface) {
		std::cout << std::format("Unable to load image {}! SDL_image Error: {}\n", path.c_str(), IMG_GetError());
		return false;
	}
	SDL_SetColorKey(loadedSurface, SDL_TRUE, SDL_MapRGB(loadedSurface->format, 0, 0xFF, 0xFF));

	this->sdlTexture = Global::renderer->createTextureFromSurface(loadedSurface);
	if (!this->sdlTexture) {
		std::cout << std::format("Unable to create texture from {}! SDL Error: {}\n", path.c_str(), SDL_GetError());
		return false;
	}

	this->width = loadedSurface->w;
	this->height = loadedSurface->h;

	SDL_FreeSurface(loadedSurface);
	return true;
}

bool Texture::loadFromRenderedText(std::string textureText, SDL_Color textColor, TTF_Font* font) {
	this->free();
	SDL_Surface* textSurface = TTF_RenderText_Solid(font, textureText.c_str(), textColor);
	if (!textSurface) {
		std::cout << std::format("Unable to render text surface! SDL_ttf Error: {}\n", TTF_GetError());
		return false;
	}

	this->sdlTexture = Global::renderer->createTextureFromSurface(textSurface);
	if (!this->sdlTexture) {
		std::cout << std::format("Unable to create texture from rendered text! SDL Error: {}\n", SDL_GetError());
		return false;
	}

	this->width = textSurface->w;
	this->height = textSurface->h;

	SDL_FreeSurface(textSurface);
	return true;
}

void Texture::setColorMod(Uint8 red, Uint8 green, Uint8 blue) {
	SDL_SetTextureColorMod(this->sdlTexture, red, green, blue);
}

void Texture::setBlendMode(SDL_BlendMode blending) {
	SDL_SetTextureBlendMode(this->sdlTexture, blending);
}

void Texture::setAlphaMod(Uint8 alpha) {
	SDL_SetTextureAlphaMod(this->sdlTexture, alpha);
}

void Texture::render(int x, int y, SDL_Rect* clip, double angle, SDL_Point* center, SDL_RendererFlip flip) {
	SDL_Rect renderQuad = { x, y, this->width, this->height };
	if (clip) {
		renderQuad.w = clip->w;
		renderQuad.h = clip->h;
	}
	Global::renderer->renderCopyEx(this->sdlTexture, clip, &renderQuad, angle, center, flip);
}

int Texture::getWidth() { return this->width; }
int Texture::getHeight() { return this->height; }
