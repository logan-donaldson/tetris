#ifndef UI_H
#define UI_H

#include <SDL_ttf.h>
#include "texture.h"

class Ui {
public:
	Ui();
	~Ui();
	bool init();
	void renderUI(bool running);
	void free();
	int getCurScore();
	void incrementCurScore(int inc);

private:
	int curScore;
	TTF_Font* smallFont;
	TTF_Font* bigFont;
	Texture scoreText, nextText, tText, eText, rText, iText, sText, curScoreText, restartText;
};

#endif
