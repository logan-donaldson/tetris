#include <SDL.h>
#include "renderer.h"

Renderer::Renderer() {
	this->sdlRenderer = nullptr;
}

Renderer::~Renderer() {
	this->free();
}

void Renderer::setSDLRenderer(SDL_Renderer* sdlRenderer) {
	this->sdlRenderer = sdlRenderer;
}

void Renderer::free() {
	SDL_DestroyRenderer(this->sdlRenderer);
}

void Renderer::setDrawColor(int red, int green, int blue, int alpha) {
	if (this->sdlRenderer) {
		SDL_SetRenderDrawColor(this->sdlRenderer, red, green, blue, alpha);
		
	}
}
void Renderer::setLogicalSize(int width, int height) {
	if (this->sdlRenderer) {
		SDL_RenderSetLogicalSize(this->sdlRenderer, width, height);
	}
}

void Renderer::renderClear() {
	if (this->sdlRenderer) {
		SDL_RenderClear(this->sdlRenderer);
	}
}

void Renderer::renderPresent() {
	if (this->sdlRenderer) {
		SDL_RenderPresent(this->sdlRenderer);
	}
}

SDL_Texture* Renderer::createTextureFromSurface(SDL_Surface* surface) {
	if (this->sdlRenderer) {
		return SDL_CreateTextureFromSurface(this->sdlRenderer, surface);
	}
	return nullptr;
}

void Renderer::renderCopyEx(SDL_Texture* texture, SDL_Rect* clip, SDL_Rect* quad, double angle, SDL_Point* center, SDL_RendererFlip flip) {
	if (this->sdlRenderer) {
		SDL_RenderCopyEx(this->sdlRenderer, texture, clip, quad, angle, center, flip);
	}
}

void Renderer::renderRect(int x, int y, int w, int h, bool fill) {
	SDL_Rect rect = { x, y, w, h };
	SDL_SetRenderDrawColor(this->sdlRenderer, 0xFF, 0xFF, 0xFF, 0xFF);
	if (fill) {
		SDL_RenderFillRect(this->sdlRenderer, &rect);
	} else {
		SDL_RenderDrawRect(this->sdlRenderer, &rect);
	}
}