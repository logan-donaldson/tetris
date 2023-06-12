#include "spawner.h"
#include "mino.h"

Spawner::Spawner() { 
	this->minoVec = { 'I', 'J', 'L', 'O', 'S', 'T', 'Z' };
}
Spawner::~Spawner() { }

Mino Spawner::spawnMino() {
	int i = rand() % this->minoVec.size();
	return Mino(this->minoVec[i]);
}