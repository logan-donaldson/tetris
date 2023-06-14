#ifndef MINO_H
#define MINO_H

#include <list>
#include <utility>
#include <vector>
#include <atomic>

class Mino {
public:
	Mino();
	Mino(char shape);
	~Mino();
	
	void render();
	void renderAsNext();

	bool getFrozen();
	void setFrozen(bool val);
	std::pair<int, int> getLocation();
	std::vector<std::vector<bool>> getLayout();

	Mino rotate(bool clockwise);
	Mino translate(char dir);

	bool checkWallCollision();
	bool checkMinoCollision(Mino other);

private:
	bool frozen;
	char shape;
	std::pair<int, int> location;
	std::vector<std::vector<bool>> layout;

	void rotateHelper();
};

#endif
