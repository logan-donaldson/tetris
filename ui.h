#ifndef UI_H
#define UI_H

#include <SDL_ttf.h>
#include "texture.h"

class Ui {
public:
	Ui();
	~Ui();
	bool init();
	void renderRect(int x, int y, int w, int h);
	void renderUI();
	void free();
	int getCurScore();
private:
	int curScore;
	TTF_Font* smallFont;
	TTF_Font* bigFont;
	Texture scoreText, nextText, tText, eText, rText, iText, sText;
};

#endif
