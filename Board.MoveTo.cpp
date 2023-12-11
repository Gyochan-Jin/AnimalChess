#include <iostream>
#include <string>
#include "Console.h"
#include "Board.h"
#include "Animal.h"
#include "Animals.h"

// Board의 MoveTo 메서드 정의


bool Board::MoveTo(int ax, int ay, int bx, int by) {


	Animal* pAlly = pBoard[bx][by];
	Animal* pEnemy = pBoard[ax][ay];




	
	//이동할 곳에 말이 있으면 양쪽 전투 후 목표 말의 hp가 0과 같거나 작으면 제거 후 움직이는 말 자리이동, 0보다 크면 자리 유지
	if (pBoard[ax][ay]) {

		int damageA = pBoard[ax][ay]->get_attack_damage();
		int damageB = pBoard[bx][by]->get_attack_damage();

		for (int i = 0; i < 8; i++) { 
			for (int j = 0; j < 8; j++) { 
				Animal* currentAnimal = pBoard[i][j]; 
				if (currentAnimal != nullptr) { 
					if (currentAnimal->Type == Animal::Duck) { // D의 위치 찾기
						Frog* frog = dynamic_cast<Frog*>(currentAnimal); 
						if (pBoard[ax][ay]->Team == pBoard[i][j]->Team) { // 아군이 피격 되었으면 F의 own_ability() 호출 
							if (frog != nullptr) frog->own_ability(*this, i, j); 
						}
					}
				}
			}
		}
		

		if (pBoard[ax][ay]->Type == Animal::Cow) { // 피격자가 Cow 면 C의 own_ability() 호출
			if (pBoard[bx][by]->Attack(ax, ay, bx, by) == true) {
				Cow* cow = dynamic_cast<Cow*> (pBoard[ax][ay]);
				cow->own_ability(*this, ax, ay);
			}
		}

		// 공격자와 피격자 데미지 입음
		pBoard[ax][ay]->damaged(damageB); 
		pBoard[bx][by]->damaged(damageA); 

		if (pBoard[bx][by]->Type == Animal::Elephant) {         // 공격자가 Elephant면 E의 own_ability() 호출
			if (pBoard[bx][by]->Attack(ax, ay, bx, by) == true) {
				Elephant* elephant = dynamic_cast<Elephant*>(pBoard[bx][by]);
				elephant->own_ability(*this, bx, by);
			}
		}

		// 1. 공격자가 피격자를 잡는 경우
		if (pBoard[ax][ay]->get_hp() <= 0 && pBoard[bx][by]->get_hp() > 0) { 
			delete pBoard[ax][ay]; 
			pBoard[ax][ay] = pBoard[bx][by]; 
			pBoard[bx][by] = 0;

			if (pBoard[bx][by]->Type == Animal::Hippo) {         // 상대 말을 잡은 말이 Hippo면 H의 own_ability() 호출
				Hippo* hippo = dynamic_cast<Hippo*>(pBoard[bx][by]);
				hippo->own_ability(pBoard[ax][ay]->get_survive()); 
			}

			return true;
		}

		// 2. 공격자가 반동으로 죽고 피격자가 살아남은 경우
		else if (pBoard[bx][by]->get_hp() <= 0 && pBoard[ax][ay]->get_hp() >= 0) {
			delete pBoard[bx][by];
			pBoard[bx][by] = 0; 
			return true;
		}

		// 3. 공격자와 피격자가 동시에 죽는 경우
		else if (pBoard[bx][by]->get_hp() && pBoard[ax][ay]->get_hp() <= 0) {
			delete pBoard[ax][ay];
			delete pBoard[bx][by];
			pBoard[ax][ay] = 0;
			pBoard[bx][by] = 0;
			return true;
		}

		// 4. 공격자와 피격자 둘다 살아남은 경우
		else if (pBoard[bx][by]->get_hp() && pBoard[ax][ay]->get_hp() > 0) {
			return true;
		}

	}

	//이동할 곳에 말이 없으면 단순 이동
	else {

		//단순 이동
		pBoard[ax][ay] = pBoard[bx][by];

		// 이동이 완료될 경우 지나간 자리는 0으로 
		pBoard[bx][by] = 0;

		return true;
	}

}