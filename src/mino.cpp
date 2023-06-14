#include "mino.h"
#include "main.h"
#include <iostream>
#include <vector>

Mino::Mino() {
	this->shape = 'I';
	this->frozen = false;
	this->location = { 3, -1 };
	this->layout = { {false, false, false, false},
					{true, true, true, true},
					{false, false, false, false},
					{false, false, false, false} };
}

Mino::Mino(char shape) {
	this->shape = shape;
	this->frozen = false;
	switch (shape) {
		case 'I':
			this->location = { 3, -2 };
			this->layout = { {false, false, false, false},
							{true, true, true, true},
							{false, false, false, false},
							{false, false, false, false} };
			break;
		case 'O':
			this->location = { 4, -2 };
			this->layout = { { true, true },
							{true, true} };
			break;
		case 'T':
			this->location = { 3, -2 };
			this->layout = { { false, false, false },
							{false, true, false},
							{true, true, true} };
			break;
		case 'Z':
			this->location = { 3, -2 };
			this->layout = { { false, false, false },
							{true, true, false},
							{false, true, true} };
			break;
		case 'S':
			this->location = { 3, -2 };
			this->layout = { { false, false, false },
							{false, true, true},
							{true, true, false} };
			break;
		case 'J':
			this->location = { 3, -2 };
			this->layout = { { false, false, false },
							{true, false, false},
							{true, true, true} };
			break;
		case 'L':
			this->location = { 3, -2 };
			this->layout = { { false, false, false },
							{false, false, true},
							{true, true, true} };
			break;
		default:
			break;
	}
}

Mino::~Mino() { }

std::pair<int, int> Mino::getLocation() {
	return this->location;
}

bool Mino::getFrozen() {
	return this->frozen;
}

void Mino::setFrozen(bool val) {
	this->frozen = val;
}

void Mino::render() {
	for (int i = 0; i < this->layout.size(); ++i) {
		for (int j = 0; j < this->layout[i].size(); ++j) {
			if (this->layout[i][j]) {
				int y = Global::BUFFER + (Global::BLOCK_SIZE * (this->location.second + i));
				if (y > 0) {
					int x = Global::BUFFER + (Global::BLOCK_SIZE * (this->location.first + j));
					Global::renderer->renderRect(x, y, Global::BLOCK_SIZE, Global::BLOCK_SIZE, frozen);
				}
			}
		}
	}
}

void Mino::renderAsNext() {
	int locx{};
	int locy{};
	std::vector<std::vector<bool>> tempLayout{};

	switch (this->shape) {
		case 'I':
			locx = Global::BUFFER + (10 * Global::BLOCK_SIZE) + Global::BUFFER + ((100 - Global::BLOCK_SIZE) / 2);
			locy = Global::BUFFER + 100 + Global::BUFFER + ((200-Global::BLOCK_SIZE * 4) / 2);
			tempLayout = { {true},
							{true},
							{true},
							{true} };
			break;
		case 'O':
			locx = Global::BUFFER + (10 * Global::BLOCK_SIZE) + Global::BUFFER + ((100 - Global::BLOCK_SIZE*2) / 2);
			locy = Global::BUFFER + 100 + Global::BUFFER + ((200 - Global::BLOCK_SIZE * 2) / 2);
			tempLayout = { { true, true },
							{ true, true } };
			break;
		case 'T':
			locx = Global::BUFFER + (10 * Global::BLOCK_SIZE) + Global::BUFFER + ((100 - Global::BLOCK_SIZE * 2) / 2);
			locy = Global::BUFFER + 100 + Global::BUFFER + ((200 - Global::BLOCK_SIZE * 3) / 2);
			tempLayout = { { true, false },
							{ true, true },
							{ true, false } };
			break;
		case 'Z':
			locx = Global::BUFFER + (10 * Global::BLOCK_SIZE) + Global::BUFFER + ((100 - Global::BLOCK_SIZE * 2) / 2);
			locy = Global::BUFFER + 100 + Global::BUFFER + ((200 - Global::BLOCK_SIZE * 3) / 2);
			tempLayout = { { true, false, false },
							{true, true, false},
							{false, true, false} };
			break;
		case 'S':
			locx = Global::BUFFER + (10 * Global::BLOCK_SIZE) + Global::BUFFER + ((100 - Global::BLOCK_SIZE * 2) / 2);
			locy = Global::BUFFER + 100 + Global::BUFFER + ((200 - Global::BLOCK_SIZE * 3) / 2);
			tempLayout = { { false, true, false },
							{true, true, false},
							{true, false, false} };
			break;
		case 'J':
			locx = Global::BUFFER + (10 * Global::BLOCK_SIZE) + Global::BUFFER + ((100 - Global::BLOCK_SIZE * 2) / 2);
			locy = Global::BUFFER + 100 + Global::BUFFER + ((200 - Global::BLOCK_SIZE * 3) / 2);
			tempLayout = { { false, true, false },
							{false, true, false},
							{true, true, false} };
			break;
		case 'L':
			locx = Global::BUFFER + (10 * Global::BLOCK_SIZE) + Global::BUFFER + ((100 - Global::BLOCK_SIZE * 2) / 2);
			locy = Global::BUFFER + 100 + Global::BUFFER + ((200 - Global::BLOCK_SIZE * 3) / 2);
			tempLayout = { { true, false, false },
							{true, false, false},
							{true, true, false} };
			break;
		default:
			break;
	}
	for (int i = 0; i < tempLayout.size(); ++i) {
		for (int j = 0; j < tempLayout[i].size(); ++j) {
			if (tempLayout[i][j]) {
				int y = 10 + (Global::BLOCK_SIZE * i) + locy;
				int x = (Global::BLOCK_SIZE * j) + locx;
				Global::renderer->renderRect(x, y, Global::BLOCK_SIZE, Global::BLOCK_SIZE, frozen);
			}
		}
	}
}

void Mino::rotateHelper() {
	size_t N{ this->layout.size() };
	for (int i = 0; i < N / 2; ++i) {
		for (int j = i; j < N - i - 1; ++j) {
			bool temp{ this->layout[i][j] };
			this->layout[i][j] = this->layout[j][N - 1 - i];
			this->layout[j][N - 1 - i] = this->layout[N - 1 - i][N - 1 - j];
			this->layout[N - 1 - i][N - 1 - j] = this->layout[N - 1 - j][i];
			this->layout[N - 1 - j][i] = temp;
		}
	}
}

Mino Mino::rotate(bool clockwise) {
	if (clockwise) {
		this->rotateHelper();
	} else {
		this->rotateHelper();
		this->rotateHelper();
		this->rotateHelper();
	}
	return *this;
}

Mino Mino::translate(char dir) {
	switch (dir) {
		case 'L':
			this->location.first -= 1;
			break;
		case 'R':
			this->location.first += 1;
			break;
		case 'D':
			this->location.second += 1;
			break;
		case 'U':
			this->location.second -= 1;
			break;
		default:
			break;
	}
	return *this;
}


bool Mino::checkWallCollision() {
	for (int i = 0; i < this->layout.size(); ++i) {
		for (int j = 0; j < this->layout[i].size(); ++j) {
			if (this->layout[i][j]) {
				int left = Global::BUFFER + (Global::BLOCK_SIZE * (this->location.first + j));
				int top = Global::BUFFER + (Global::BLOCK_SIZE * (this->location.second + i));
				int right = left + Global::BLOCK_SIZE;
				int bottom = top + Global::BLOCK_SIZE;
				if (bottom > Global::BUFFER + 20 * Global::BLOCK_SIZE || left < Global::BUFFER || right > Global::BUFFER + 10 * Global::BLOCK_SIZE) {
					return true;
				}
			}
		}
	}
	return false;
}

std::vector<std::vector<bool>> Mino::getLayout() {
	return this->layout;
}

bool Mino::checkMinoCollision(Mino other) {
	for (int i = 0; i < this->layout.size(); ++i) {
		for (int j = 0; j < this->layout[i].size(); ++j) {
			for (int k = 0; k < other.getLayout().size(); ++k) {
				for (int l = 0; l < other.getLayout()[k].size(); ++l) {
					int locx{ this->location.first + i };
					int locy{ this->location.second + j };
					int olocx{ other.getLocation().first + k };
					int olocy{ other.getLocation().second + l };
					bool condition{ (locx == olocx) && (locy == olocy) };
					if (condition && this->layout[i][j] && other.getLayout()[k][l]) {
						return true;
					}
				}
			}
		}
	}
	return false;
}