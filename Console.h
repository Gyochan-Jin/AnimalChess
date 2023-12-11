#pragma once

#include "Board.h"
#include "Graphics.h"
#include "Animal.h"

class Console {
private:
	Board board;
	Graphics graphics;

	//처음은 player1이 먼저 시작
	unsigned int iTeam = Animal::player1;
	
	

private:
	Console(Console& program);

	void ExecuteCommand(void);

public:

	int turn = 1;

	Console(void);

	int Run(void);

};

