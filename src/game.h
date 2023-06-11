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
	void handleEvent(SDL_Event& e);
	void addMino(Mino mino);

private:
	Ui ui;
	Mino activeMino;
	std::list<Mino> lockedMinos;
};

#endif
