#include <iostream>
#include <string>

#include "Graphics.h"
#include "Console.h"
#include "Board.h"
#include "Animal.h"
#include "Animals.h"

using namespace std;

// Console의 ExcitionCommand 메서드 정의


void Console::ExecuteCommand(void) {
	string param[2];

	int x[2] = { 0, };
	int y[2] = { 0, };

	Animal* pTarget = 0;

	int turn = 1;

	//명령어 입력
	cin >> param[0] >> param[1];
	
	//명령어에서 실제 위치 가져오기
	x[0] = param[0][0] - 'A';
	y[0] = 7 - (param[0][1] - '1'); // 이전 위치

	x[1] = param[1][0] - 'A';
	y[1] = 7 - (param[1][1] - '1'); // 이동 위치

	//말 가져오기
	pTarget = board.GetAnimal(x[0], y[0]);


	for (int i = 0; i <= 8; i++) {
		for (int j = 0; j <= 8; j++) {
			Animal* currentAnimal = board.GetAnimal(i, j);

			if (currentAnimal != nullptr && currentAnimal->Type == Animal::Frog) { // F의 own_ability() 호출    
				Frog* frog = dynamic_cast<Frog*>(currentAnimal);
				if (frog != nullptr) frog->own_ability(board, i, j);
			}

			else if (currentAnimal != nullptr && currentAnimal->Type == Animal::Pig) { // 턴 수가 3의 배수이면 P의 own_ability() 호출 
				if ((turn % 3) == 0) {
					Pig* pig = dynamic_cast<Pig*>(currentAnimal);
					if (pig != nullptr) pig->own_ability(board, i, j);
				}
			}
		}
	}

	//현재 턴이 올바른지 검사
	if (pTarget->Team == iTeam) {
		if (board.GetAnimal(x[1], y[1]) && pTarget->Team == iTeam) { //이동 위치에 말이 있을 경우
			if (pTarget->Attack(x[1], y[1], x[0], y[0])) { //공격모드
				if (board.MoveTo(x[1], y[1], x[0], y[0])) {
					//이동에 성공했을 경우 턴 변경
					iTeam = !iTeam;
					turn += 1;
				}
			}
		} 
		else { //이동 위치에 말이 없을 경우
			if (pTarget->Move(x[1], y[1], x[0], y[0])) { //이동 가능한지 검사
				if (board.MoveTo(x[1], y[1], x[0], y[0])) { //가능할 경우 이동
					iTeam = !iTeam;
					turn += 1;
				}
			}
		}
	}


    return;
}