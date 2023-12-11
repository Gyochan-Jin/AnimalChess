#include <iostream>
#include <string>

#include "Graphics.h"
#include "Console.h"
#include "Board.h"
#include "Animal.h"
#include "Animals.h"

using namespace std;

// Console�� ExcitionCommand �޼��� ����


void Console::ExecuteCommand(void) {
	string param[2];

	int x[2] = { 0, };
	int y[2] = { 0, };

	Animal* pTarget = 0;

	int turn = 1;

	//��ɾ� �Է�
	cin >> param[0] >> param[1];
	
	//��ɾ�� ���� ��ġ ��������
	x[0] = param[0][0] - 'A';
	y[0] = 7 - (param[0][1] - '1'); // ���� ��ġ

	x[1] = param[1][0] - 'A';
	y[1] = 7 - (param[1][1] - '1'); // �̵� ��ġ

	//�� ��������
	pTarget = board.GetAnimal(x[0], y[0]);


	for (int i = 0; i <= 8; i++) {
		for (int j = 0; j <= 8; j++) {
			Animal* currentAnimal = board.GetAnimal(i, j);

			if (currentAnimal != nullptr && currentAnimal->Type == Animal::Frog) { // F�� own_ability() ȣ��    
				Frog* frog = dynamic_cast<Frog*>(currentAnimal);
				if (frog != nullptr) frog->own_ability(board, i, j);
			}

			else if (currentAnimal != nullptr && currentAnimal->Type == Animal::Pig) { // �� ���� 3�� ����̸� P�� own_ability() ȣ�� 
				if ((turn % 3) == 0) {
					Pig* pig = dynamic_cast<Pig*>(currentAnimal);
					if (pig != nullptr) pig->own_ability(board, i, j);
				}
			}
		}
	}

	//���� ���� �ùٸ��� �˻�
	if (pTarget->Team == iTeam) {
		if (board.GetAnimal(x[1], y[1]) && pTarget->Team == iTeam) { //�̵� ��ġ�� ���� ���� ���
			if (pTarget->Attack(x[1], y[1], x[0], y[0])) { //���ݸ��
				if (board.MoveTo(x[1], y[1], x[0], y[0])) {
					//�̵��� �������� ��� �� ����
					iTeam = !iTeam;
					turn += 1;
				}
			}
		} 
		else { //�̵� ��ġ�� ���� ���� ���
			if (pTarget->Move(x[1], y[1], x[0], y[0])) { //�̵� �������� �˻�
				if (board.MoveTo(x[1], y[1], x[0], y[0])) { //������ ��� �̵�
					iTeam = !iTeam;
					turn += 1;
				}
			}
		}
	}


    return;
}