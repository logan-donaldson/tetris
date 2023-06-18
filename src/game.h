#ifndef GAME_H
#define GAME_H
#include <list>
#include <vector>
#include "mino.h"
#include "ui.h"
#include "spawner.h"
#include "mixer.h"

class Game {
	public:
		Game();
		~Game();
		bool init();
		void free();
		void render();
		void handleEvent(SDL_Event& e);
		Mino& getActiveMino();
		Mino& getNextMino();
		void setActiveMino(Mino mino);
		void setNextMino(Mino mino);
		Mino spawnMino();
		bool checkCollisions();
		void dropMino();
		int checkLines();
		std::vector<std::vector<int>>& getBoard();

	private:
		Ui ui;
		Mino activeMino;
		Mino nextMino;
		Spawner spawner;
		std::vector<std::vector<int>> board;
		bool running;
		Mixer mixer;

		void updateBoard(bool freeze);
		void restart();
		
};

#endif
