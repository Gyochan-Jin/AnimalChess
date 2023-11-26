#include <Windows.h>
#include <iostream>
#include "Board.h"
#include "Graphics.h"
#include "Animal.h"




void Graphics::Draw(void) const {
	using namespace std;
	//말 좌표 그래픽 구현
	const char szBottom[] = "ABCDEFGH";

	const Animal* pTarget = 0;

	cout << "좌표를 입력하여 말을 움직이세요 ex) B1 B2" << endl;

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
		}
		cout << endl;
	}
	cout << "--|----P1-----|-----P2----" << endl;
	cout << "  |  HP   AD  |   HP   AD" << endl;
	return;
}