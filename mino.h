#ifndef MINO_H
#define MINO_H

#include <list>
#include <utility>

class Mino {
public:
	Mino(char shape);
	~Mino();
	
	void render();

	std::list<std::pair<int, int>>* getCoords();
	int getNumCoords();
	bool getFrozen();

	void rotate();
	void lower();

private:
	std::list<std::pair<int, int>> coords;
	bool frozen;

};

#endif
