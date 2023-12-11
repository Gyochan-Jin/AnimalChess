#include <Windows.h>
#include <iostream>
#include "Board.h"
#include "Graphics.h"
#include "Animal.h"
#include "Animals.h"

using namespace std;


void Graphics::Draw(void) const {
	
	
	//�� ��ǥ �׷��� ����
	const char szBottom[] = "ABCDEFGH";

	const Animal* pTarget = 0;

	int player1_animal_hp[7] = {};
	int player2_animal_hp[7] = {};
	int player1_animal_damage[7] = {};
	int player2_animal_damage[7] = {};

	cout << "��ǥ�� �Է��Ͽ� ���� �����̼��� ex) B1 B2" << endl; 
	cout << "�� ĭ�� ������ �� �ִ� �䳢�� ������ ��� ���� �� ĭ�� ������ �� �ֽ��ϴ�" << endl;
	cout << "C : �ǰ� �� �ڽ��� �߽����� 3*3 �ȿ� �ִ� �Ʊ����� ���ݷ�+1/ü��+1" << endl;
	cout << "D : �ڽ��� �߽����� 3*3 �ȿ� �ִ� �Ʊ��� �ǰ� �� �ش� �Ʊ��� ü��+1" << endl;
	cout << "F : 3�� ��� �ϸ��� �ڽŰ� ���� ����(x��, y��)�� �ִ� �Ʊ��� ���ݷ� + 1" << endl;
	cout << "P : 3�� ��� �ϸ��� �ڽ��� �߽����� 5*5 �ȿ� �ִ� ��� ��(���� �� ����)���� ü�� +1" << endl;
	cout << "H : �ڽ��� ������ ����� hp�� 0���ϰ� �Ǹ� �ڽ��� ���ݷ�+1, ü��+1" << endl;
	cout << "E : ���� �� �ڽ��� �߽����� 3*3 �ȿ� �ִ� ��� ��(�Ʊ� �� ����) ü��-1" << endl;

	cout << "������ player1 (�Ķ�) �Դϴ�" << endl;
	cout << endl;

	for (int i = 0; i <= 8; i++) {
		for (int j = 0; j <= 8; j++) {
			if (i == 8) {
				if (j == 0) cout << "  ";
				else {
					// �׵θ� ����
					SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY);
					cout << szBottom[j - 1] << " ";
				}
				continue;
			}
			if (j == 0) {
				//�׵θ� ����
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY);
				cout << 8 - i << " ";
			}
			else {
				pTarget = pBoard->GetAnimal(j - 1, i);
				if (pTarget && pTarget->Team == Animal::player1) {
					SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_BLUE | FOREGROUND_INTENSITY);
				}
				else {
					SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_INTENSITY);
				}
				cout << ToChar(pTarget);
			}




			unsigned int ianimal[7] = { Animal::Cow, Animal::Duck, Animal::Frog, Animal::Rabbit, Animal::Pig, Animal::Hippo, Animal::Elephant }; 

			// ������ hp, attack_damage�� �迭�� ����
			const Animal* currentAnimal = pBoard->GetAnimal(i, j);
			for(int k = 0; k <= 6; k++ ) {
				if (currentAnimal != nullptr && currentAnimal->Type == ianimal[k] && currentAnimal->Team == Animal::player1) {
					player1_animal_hp[k] = currentAnimal->get_hp();
					player1_animal_damage[k] = currentAnimal->get_attack_damage();
				}
				else if (currentAnimal != nullptr && currentAnimal->Type == ianimal[k] && currentAnimal->Team == Animal::player2) {
					player2_animal_hp[k] = currentAnimal->get_hp();
					player2_animal_damage[k] = currentAnimal->get_attack_damage();
				}
			}			
		}
		cout << endl;
	}
	
	string aniname[] = {"C", "D", "F", "R", "P", "H", "E"};

	cout << endl;
	cout << "    |       P1       |       P2       |" << endl;
	cout << "----|----HP----AD----|----HP----AD----|" << endl;
	for (int i = 0; i <= 6; i++) {
		cout << "  " << aniname[i] << " |    " << player1_animal_hp[i] << "     " << player1_animal_damage[i] << "     |     " << player2_animal_hp[i] << "     " << player2_animal_damage[i] << "    |     " << endl;
	}
	return;
}