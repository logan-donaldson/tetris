#ifndef RENDERER_H
#define RENDERER_H

#include <SDL.h>

class Renderer {
public:
	Renderer();
	~Renderer();
	void free();
	
	void setSDLRenderer(SDL_Renderer* sdlRenderer);
	void setDrawColor(int red, int green, int blue, int alpha);
	void setLogicalSize(int width, int height);
	void renderClear();
	void renderPresent();
	void renderCopyEx(SDL_Texture* texture, SDL_Rect* clip, SDL_Rect* quad, double angle, SDL_Point* center, SDL_RendererFlip flip);
	SDL_Texture* createTextureFromSurface(SDL_Surface* loadedSurface);

	void renderRect(int x, int y, int w, int h, bool fill);

	
	

private:
	SDL_Renderer* sdlRenderer;
};

#endif

