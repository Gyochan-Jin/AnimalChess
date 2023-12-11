#include <iostream>
#include <string>
#include "Console.h"
#include "Board.h"
#include "Animal.h"
#include "Animals.h"

// Board�� MoveTo �޼��� ����


bool Board::MoveTo(int ax, int ay, int bx, int by) {


	Animal* pAlly = pBoard[bx][by];
	Animal* pEnemy = pBoard[ax][ay];




	
	//�̵��� ���� ���� ������ ���� ���� �� ��ǥ ���� hp�� 0�� ���ų� ������ ���� �� �����̴� �� �ڸ��̵�, 0���� ũ�� �ڸ� ����
	if (pBoard[ax][ay]) {

		int damageA = pBoard[ax][ay]->get_attack_damage();
		int damageB = pBoard[bx][by]->get_attack_damage();

		for (int i = 0; i < 8; i++) { 
			for (int j = 0; j < 8; j++) { 
				Animal* currentAnimal = pBoard[i][j]; 
				if (currentAnimal != nullptr) { 
					if (currentAnimal->Type == Animal::Duck) { // D�� ��ġ ã��
						Frog* frog = dynamic_cast<Frog*>(currentAnimal); 
						if (pBoard[ax][ay]->Team == pBoard[i][j]->Team) { // �Ʊ��� �ǰ� �Ǿ����� F�� own_ability() ȣ�� 
							if (frog != nullptr) frog->own_ability(*this, i, j); 
						}
					}
				}
			}
		}
		

		if (pBoard[ax][ay]->Type == Animal::Cow) { // �ǰ��ڰ� Cow �� C�� own_ability() ȣ��
			if (pBoard[bx][by]->Attack(ax, ay, bx, by) == true) {
				Cow* cow = dynamic_cast<Cow*> (pBoard[ax][ay]);
				cow->own_ability(*this, ax, ay);
			}
		}

		// �����ڿ� �ǰ��� ������ ����
		pBoard[ax][ay]->damaged(damageB); 
		pBoard[bx][by]->damaged(damageA); 

		if (pBoard[bx][by]->Type == Animal::Elephant) {         // �����ڰ� Elephant�� E�� own_ability() ȣ��
			if (pBoard[bx][by]->Attack(ax, ay, bx, by) == true) {
				Elephant* elephant = dynamic_cast<Elephant*>(pBoard[bx][by]);
				elephant->own_ability(*this, bx, by);
			}
		}

		// 1. �����ڰ� �ǰ��ڸ� ��� ���
		if (pBoard[ax][ay]->get_hp() <= 0 && pBoard[bx][by]->get_hp() > 0) { 
			delete pBoard[ax][ay]; 
			pBoard[ax][ay] = pBoard[bx][by]; 
			pBoard[bx][by] = 0;

			if (pBoard[bx][by]->Type == Animal::Hippo) {         // ��� ���� ���� ���� Hippo�� H�� own_ability() ȣ��
				Hippo* hippo = dynamic_cast<Hippo*>(pBoard[bx][by]);
				hippo->own_ability(pBoard[ax][ay]->get_survive()); 
			}

			return true;
		}

		// 2. �����ڰ� �ݵ����� �װ� �ǰ��ڰ� ��Ƴ��� ���
		else if (pBoard[bx][by]->get_hp() <= 0 && pBoard[ax][ay]->get_hp() >= 0) {
			delete pBoard[bx][by];
			pBoard[bx][by] = 0; 
			return true;
		}

		// 3. �����ڿ� �ǰ��ڰ� ���ÿ� �״� ���
		else if (pBoard[bx][by]->get_hp() && pBoard[ax][ay]->get_hp() <= 0) {
			delete pBoard[ax][ay];
			delete pBoard[bx][by];
			pBoard[ax][ay] = 0;
			pBoard[bx][by] = 0;
			return true;
		}

		// 4. �����ڿ� �ǰ��� �Ѵ� ��Ƴ��� ���
		else if (pBoard[bx][by]->get_hp() && pBoard[ax][ay]->get_hp() > 0) {
			return true;
		}

	}

	//�̵��� ���� ���� ������ �ܼ� �̵�
	else {

		//�ܼ� �̵�
		pBoard[ax][ay] = pBoard[bx][by];

		// �̵��� �Ϸ�� ��� ������ �ڸ��� 0���� 
		pBoard[bx][by] = 0;

		return true;
	}

}