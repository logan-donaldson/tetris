#ifndef GAME_H
#define GAME_H
#include <list>
#include "mino.h"
#include "ui.h"
#include "spawner.h"

class Game {
	public:
		Game();
		~Game();
		bool init();
		void free();
		void render();
		void handleEvent(SDL_Event& e);
		void addMino(Mino mino);
		Mino& getActiveMino();
		Mino& getNextMino();
		void setActiveMino(Mino mino);
		void setNextMino(Mino mino);
		Mino spawnMino();

	private:
		Ui ui;
		Mino activeMino;
		Mino nextMino;
		std::list<Mino> lockedMinos;
		Spawner spawner;
};

#endif
