#include <iostream>
#include <string>
#include "Console.h"
#include "Board.h"
#include "Animal.h"
#include "Animals.h"

// Board의 MoveTo 메서드 정의


bool Board::MoveTo(int ax, int ay, int bx, int by) {
	
	int damageA = pBoard[ax][by]->get_attack_damage();
	int damageB = pBoard[bx][by]->get_attack_damage();

	//이동할 곳에 말이 있으면 양쪽 전투 후 목표 말의survive가 false면 제거 후 움직이는 말 자리이동, true 면 자리 유지
	if (pBoard[ax][ay]){

		pBoard[ax][ay]->damaged(damageB);
		pBoard[bx][by]->damaged(damageA);

		if (pBoard[ax][ay]->get_survive() == false) {
			delete pBoard[ax][ay];
			pBoard[ax][ay] = pBoard[bx][ay];
			pBoard[bx][by] = 0;

			return true;
		}
		else if (pBoard[bx][by]->get_survive() == false) {
			delete pBoard[bx][by];
			pBoard[bx][by] = 0;
			return true;
		}
		else if (pBoard[bx][by]->get_survive() && pBoard[ax][ay]->get_survive() == false) {
			delete pBoard[ax][ay], pBoard[bx][by];
			pBoard[ax][ay], pBoard[bx][by] = 0;
			return true;
		}
		else if (pBoard[bx][by]->get_survive() && pBoard[ax][ay]->get_survive() == true) {
			return true;
		}

	}

	//이동할 곳에 말이 없으면 단순 이동
	else {

		//단순 이동
		pBoard[ax][ay] = pBoard[bx][ay];

		// 이동이 완료될 경우 지나간 자리는 0으로 
		pBoard[bx][by] = 0;

		return true;
	}
}