#pragma once

class Animal;
class Board;

class Graphics {
private:
	const Board* pBoard = 0;

public:
	Graphics(const Board *pBoard);

	void Draw(void) const;
	static const char *ToChar(const Animal *pAnimal);
};