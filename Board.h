#pragma once

class Animal;

class Board {
private:
	Animal *pBoard[8][8];

public:
	Board(bool bstd = true);
	~Board();

	Animal* GetAnimal(int x, int y);
	const Animal* GetAnimal(int x, int y) const;

	bool MoveTo(int ax, int ay, int bx, int by); 
	
};

