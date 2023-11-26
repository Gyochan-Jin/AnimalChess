#include "Board.h"
#include "Animal.h"
#include "Animals.h" 

// Board의 MoveTo 메서드 정의


bool Board::MoveTo(int ax, int ay, int bx, int by) {
	//이동할 곳에 말이 있으면 양쪽의 체력/공격력 비교 후 체력이 0 이하면 제거
	if (pBoard[ax][ay]) {
		//비교 후 제거0
	}

	//단순 이동
	pBoard[ax][ay] = pBoard[bx][ay];

	// 이동이 완료될 경우 지나간 자리는 0으로 
	pBoard[bx][by] = 0;

	return true;
}