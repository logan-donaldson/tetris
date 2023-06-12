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
	char getShape();
	std::pair<int, int> getLocation();
	std::vector<std::vector<bool>> getLayout();

	Mino rotate(bool clockwise);
	Mino translate(char dir);

private:
	bool frozen;
	char shape;
	std::pair<int, int> location;
	std::vector<std::vector<bool>> layout;

	void rotateHelper();
	bool checkWallCollision();
	bool checkMinoCollision(Mino other);
};

#endif
