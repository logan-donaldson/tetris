#ifndef GAME_H
#define GAME_H
#include <list>
#include "Mino.h"
#include "Ui.h"

class Game {
public:
	Game();
	~Game();
	bool init();
	void free();
	void render();

private:
	Ui ui;
	std::list<Mino> minos;
};

#endif
