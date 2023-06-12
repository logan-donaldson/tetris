#include "mino.h"
#include "main.h"

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
			this->location = { 3, -1 };
			this->layout = { {false, false, false, false},
							{true, true, true, true},
							{false, false, false, false},
							{false, false, false, false} };
			break;
		case 'O':
			break;
		case 'T':
			break;
		case 'S':
			break;
		case 'Z':
			break;
		case 'J':
			break;
		case 'L':
			break;
		default:
			break;
	}
}

Mino::~Mino() { }

std::pair<int, int> Mino::getLocation() {
	return this->location;
}

void Mino::render() {
	for (size_t i = 0; i < this->layout.size(); ++i) {
		for (size_t j = 0; j < this->layout[i].size(); ++j) {
			if (this->layout[i][j]) {
				int x = Global::BUFFER + (Global::BLOCK_SIZE * (this->location.first + j));
				int y = Global::BUFFER + (Global::BLOCK_SIZE * (this->location.second + i));
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
		default:
			break;
	}
	return *this;
}