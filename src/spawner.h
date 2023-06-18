#ifndef SPAWNER_H
#define SPAWNER_H

#include <vector>
#include "mino.h"

class Spawner {
	public:
		Spawner();
		Mino spawnMino();
	private:
		std::vector<char> minoVec;
};

#endif
