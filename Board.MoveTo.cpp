#include <iostream>
#include <string>
#include "Console.h"
#include "Board.h"
#include "Animal.h"
#include "Animals.h"

// Board�� MoveTo �޼��� ����


bool Board::MoveTo(int ax, int ay, int bx, int by) {
	//�̵��� ���� ���� ������ ���� ���� �� survive�� false�� ����, true �� �ڸ� ����
	
	int damageA = pBoard[ax][by]->get_attack_damage();
	int damageB = pBoard[bx][by]->get_attack_damage();

	
	if (pBoard[ax][ay]){

		pBoard[ax][ay]->damaged(damageB);
		pBoard[bx][by]->damaged(damageA);

		if (pBoard[ax][ay]->get_survive() == false) {
			delete pBoard[ax][ay];
			//�ܼ� �̵�
			pBoard[ax][ay] = pBoard[bx][ay];

			// �̵��� �Ϸ�� ��� ������ �ڸ��� 0���� 
			pBoard[bx][by] = 0;

			return true;
		}
		else if (pBoard[bx][by]->get_survive() == false) {
			delete pBoard[bx][by];
		}
		else if (pBoard[bx][by]->get_survive() && pBoard[ax][ay]->get_survive() == false) {
			delete pBoard[ax][ay], pBoard[bx][by];
		}
		else if (pBoard[bx][by]->get_survive() && pBoard[ax][ay]->get_survive() == true) {
			
		}

	}

	//�ܼ� �̵�
	pBoard[ax][ay] = pBoard[bx][ay];

	// �̵��� �Ϸ�� ��� ������ �ڸ��� 0���� 
	pBoard[bx][by] = 0;

	return true;
}