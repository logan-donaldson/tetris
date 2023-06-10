#ifndef TEXTURE_H
#define TEXTURE_H

#include <SDL_image.h>
#include <SDL_ttf.h>
#include <string>


//Texture wrapper class
class Texture {
public:
    Texture();
    ~Texture();

    bool loadFromFile(std::string path);
    bool loadFromRenderedText(std::string textureText, SDL_Color textColor, TTF_Font* font);

    void free();

    void setColorMod(Uint8 red, Uint8 green, Uint8 blue);
    void setBlendMode(SDL_BlendMode blending);
    void setAlphaMod(Uint8 alpha);

    void render(int x, int y, SDL_Rect* clip = NULL, double angle = 0.0, SDL_Point* center = NULL, SDL_RendererFlip flip = SDL_FLIP_NONE);

    int getWidth();
    int getHeight();

private:
    SDL_Texture* sdlTexture;
    int width;
    int height;
};

#endif
