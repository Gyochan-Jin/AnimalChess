#include <iostream>
#include <string>
#include "Console.h"
#include "Board.h"
#include "Animal.h"

using namespace std;

// Console의 ExcitionCommand 메서드 정의

void Console::ExecuteCommand(void) {
	string param[2];

	int x[2] = { 0, };
	int y[2] = { 0, };

	Animal *pTarget = 0;

	//명령어 입력
	cin >> param[0] >> param[1];
	
	//명령어에서 실제 위치 가져오기
	x[0] = param[0][0] - 'A';
	y[0] = 7 - (param[0][1] - '1'); // 이전 위치

	x[1] = param[1][0] - 'A';
	y[1] = 7 - (param[1][1] - '1'); // 이동 위치

	//말 가져오기
	pTarget = board.GetAnimal(x[0], y[0]);

	//이동 위치에 말이 있을 경우
	if (board.GetAnimal(x[1], y[1])) {
		//공격 모드
		if (pTarget->Attack(x[1], y[1], x[0], y[0])) {
			board.MoveTo(x[1], y[1], x[0], y[0]);
		}
	}
	else {
		//이동 가능한지 검사
		if (pTarget->Move(x[1], y[1], x[0], y[0])) {
			//가능할 경우 이동
			board.MoveTo(x[1], y[1], x[0], y[0]);
		}
	}
	return;
}