#include <Windows.h>
#include <iostream>
#include "Board.h"
#include "Graphics.h"
#include "Animal.h"
#include "Animals.h"

using namespace std;


void Graphics::Draw(void) const {
	
	
	//말 좌표 그래픽 구현
	const char szBottom[] = "ABCDEFGH";

	const Animal* pTarget = 0;

	int player1_animal_hp[7] = {};
	int player2_animal_hp[7] = {};
	int player1_animal_damage[7] = {};
	int player2_animal_damage[7] = {};

	cout << "좌표를 입력하여 말을 움직이세요 ex) B1 B2" << endl; 
	cout << "두 칸씩 움직일 수 있는 토끼를 제외한 모든 말은 한 칸씩 움직일 수 있습니다" << endl;
	cout << "C : 피격 시 자신을 중심으로 3*3 안에 있는 아군에게 공격력+1/체력+1" << endl;
	cout << "D : 자신을 중심으로 3*3 안에 있는 아군이 피격 시 해당 아군의 체력+1" << endl;
	cout << "F : 3의 배수 턴마다 자신과 같은 라인(x축, y축)에 있는 아군의 공격력 + 1" << endl;
	cout << "P : 3의 배수 턴마다 자신을 중심으로 5*5 안에 있는 모든 말(적의 말 포함)에게 체력 +1" << endl;
	cout << "H : 자신이 공격한 상대의 hp가 0이하가 되면 자신의 공격력+1, 체력+1" << endl;
	cout << "E : 공격 시 자신을 중심으로 3*3 안에 있는 모든 말(아군 말 포함) 체력-1" << endl;

	cout << "선공은 player1 (파랑) 입니다" << endl;
	cout << endl;

	for (int i = 0; i <= 8; i++) {
		for (int j = 0; j <= 8; j++) {
			if (i == 8) {
				if (j == 0) cout << "  ";
				else {
					// 테두리 검정
					SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY);
					cout << szBottom[j - 1] << " ";
				}
				continue;
			}
			if (j == 0) {
				//테두리 검정
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

			// 말들의 hp, attack_damage를 배열에 저장
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