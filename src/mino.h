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
	
	void renderAsNext();

	std::pair<int, int> getLocation();
	std::vector<std::vector<bool>> getLayout();
	void setLayout(int i, int j, bool val);

	Mino rotate(bool clockwise);
	Mino translate(char dir);

	bool checkWallCollision();
	bool checkMinoCollision();

private:
	char shape;
	std::pair<int, int> location;
	std::vector<std::vector<bool>> layout;

	void rotateHelper();
};

#endif
