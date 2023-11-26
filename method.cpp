#include <iostream>
#include "Console.h"
#include "Board.h"
#include "Graphics.h"
#include "Animal.h"
#include "Animals.h"

//========Console 메서드=========

Console::Console(Console& program):
	graphics(&board) {
}

Console::Console(void) :
	graphics(&board) {
}


int Console::Run(void) {
	while (true) {
		std::system("cls"); //화면 지우기
		graphics.Draw();

		//명령 실행
		ExecuteCommand();
	}
	return 0;
}


//=========Board 메서드==========

Board::Board(bool bstd) {
	// 0으로 초기화
	for (int i = 0; i < 8; i++) {
		for (int j = 0; j < 8; j++) {
			pBoard[i][j] = 0;
		}
	}
	// 말 배치
	if (bstd) {
		unsigned int iTeam = Animal::player1;
		unsigned int iPos = 0;
		int j = 0;
		for (unsigned int i = 0; i < 2; i++) {
			pBoard[abs(0-j)][iPos] = new Cow(iTeam);
			pBoard[abs(1-j)][iPos] = new Duck(iTeam);
			pBoard[abs(2-j)][iPos] = new Frog(iTeam);
			pBoard[abs(3-j)][iPos] = new Rabbit(iTeam);
			pBoard[abs(4-j)][iPos] = new Pig(iTeam);
			pBoard[abs(5-j)][iPos] = new Hippo(iTeam);
			pBoard[abs(6-j)][iPos] = new Elephant(iTeam);
			pBoard[abs(7-j)][iPos] = 0;

			iPos = 7;
			j = 7;
			iTeam = Animal::player2;
		}
	}
}

Board::~Board() {
	for (unsigned int i = 0; i < 8; i++) {
		for (unsigned int j = 0; j < 8; j++) {
			if (pBoard[i][j] != nullptr) {
				delete pBoard[i][j];
				pBoard[i][j] = nullptr; // dangling 포인터 방지
			}
		}
	}
}

Animal* Board::GetAnimal(int x, int y) {
	if (x >= 0 && x < 8 && y >= 0 && y < 8) {
		return pBoard[x][y];
	}
	return 0;
}
const Animal* Board::GetAnimal(int x, int y) const {
	if (x >= 0 && x < 8 && y >= 0 && y < 8) {
		return pBoard[x][y];
	}
	return 0;
}


//=============Graphics 메서드===============

Graphics::Graphics(const Board* pBoard):
	pBoard(pBoard) {
}

const char* Graphics::ToChar(const Animal* pAnimal) {
	if (pAnimal == nullptr) return "  ";
	else {
		switch (pAnimal->Type) {
		case Animal::Cow:
			return "C ";
		case Animal::Duck:
			return "D ";
		case Animal::Frog:
			return "F ";
		case Animal::Rabbit:
			return "R ";
		case Animal::Pig:
			return "P ";
		case Animal::Hippo:
			return "H ";
		case Animal::Elephant:
			return "E ";
		default:
			return 0;
		}
	}
	return 0;
}


