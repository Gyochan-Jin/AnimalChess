#include "Animals.h"
#include "Board.h"
#include <utility>
#include <string>
#include <stdbool.h>

using namespace std;

// ������ ���ϴ� ������ ��ũ��
#define myabs(x) ((x) < 0 ? -(x) : (x))

//�� Ŭ����
Cow::Cow(unsigned int iTeam) : Animal(5, 3, Animal::Cow, iTeam) {
	this->ability_range = 5;
}
bool Cow::Move(int ax, int ay, int bx, int by) const {
	// x�� �������� �̵� 
	if ((ay == by) && (myabs(ax - bx) == 1)) return Animal::Move(ax, ay, bx, by);
	// y�� �������� �̵� 
	if ((ax == bx) && (myabs(ay - by) == 1)) return Animal::Move(ax, ay, bx, by);
	// �밢�� �������� �̵� 
	if ((myabs(ax - bx) == 1) && (myabs(ay - by) == 1)) return Animal::Move(ax, ay, bx, by);
}
bool Cow::Attack(int ax, int ay, int bx, int by) const {
	if ((myabs(ax - bx) <= 1) || (myabs(ay - by) <= 1)) return true;

	return false;
}


void Cow::own_ability(Board& pBoard, int ax, int ay) {
	//�ǰ� �� �ڽ��� �߽����� 3*3 �ȿ� �ִ� �Ʊ����� ���ݷ�+1/ü��+1 => change(1, 1) �̿��ϱ�
	int newRow;
	int newCol;
	pair<int, int> findAllyCow; 
		// �ֺ� 8ĭ Ȯ��
		for (int i = -1; i <= 1; ++i) 
		{
			for (int j = -1; j <= 1; ++j) 
			{
				newRow = ax + i;
				newCol = ay + j;

				// ��ȿ�� ���� ���� �ִ��� Ȯ��
				if (newRow >= 0 && newRow < 8 && newCol >= 0 && newCol < 8) {
					// �Ʊ� ���� �ִ��� Ȯ��
					if (pBoard.GetAnimal(newRow, newCol)->Team == pBoard.GetAnimal(ax, ay)->Team) {
						findAllyCow = make_pair(newRow, newCol);
					}
				}
			}
		}
	findAllyCow.first = newRow; //�Ʊ���ġ x��ǥ
	findAllyCow.second = newCol; //�Ʊ���ġ y��ǥ
	pBoard.GetAnimal(newRow, newCol)->change(1, 1); //�Ʊ� ���ݷ� +1
}

//���� Ŭ����
Duck::Duck(unsigned int iTeam) : Animal(3, 1, Animal::Duck, iTeam) {
	this->ability_range = 5;
}
bool Duck::Move(int ax, int ay, int bx, int by) const {
	// x�� �������� �̵� 
	if ((ay == by) && (myabs(ax - bx) == 1)) return Animal::Move(ax, ay, bx, by);
	// y�� �������� �̵� 
	if ((ax == bx) && (myabs(ay - by) == 1)) return Animal::Move(ax, ay, bx, by);
	// �밢�� �������� �̵� 
	if ((myabs(ax - bx) == 1) && (myabs(ay - by) == 1)) return Animal::Move(ax, ay, bx, by);
}
bool Duck::Attack(int ax, int ay, int bx, int by) const {
	if ((myabs(ax - bx) <= 1) || (myabs(ay - by) <= 1)) return true;

	return false;
}


void Duck::own_ability(Board& pBoard, int ax, int ay) {
	//�ڽ��� �߽����� 3*3 �ȿ� �ִ� �Ʊ��� �ǰ� �� �ش� �Ʊ��� ü��+1 => change(1, 0) �̿��ϱ�
	int newRow;
	int newCol;
	pair<int, int> findAllyDuck;
		// �ֺ� 8ĭ Ȯ��
		for (int i = -1; i <= 1; ++i) 
		{
			for (int j = -1; j <= 1; ++j) 
			{
				newRow = ax + i;
				newCol = ay + j;
				// ��ȿ�� ���� ���� �ִ��� Ȯ��
				if (newRow >= 0 && newRow < 8 && newCol >= 0 && newCol < 8)
				{
					// �Ʊ� ���� �ִ��� Ȯ��
					if (pBoard.GetAnimal(newRow, newCol) != nullptr) { // ���� ó��
						if (pBoard.GetAnimal(newRow, newCol)->Team == pBoard.GetAnimal(ax, ay)->Team)
						{
							findAllyDuck = make_pair(newRow, newCol);
						}
				    }
				}
			}
		}
	findAllyDuck.first = newRow;
	findAllyDuck.second = newCol;
	if (findAllyDuck.first != -1 && findAllyDuck.second != -1)
	{
		pBoard.GetAnimal(findAllyDuck.first, findAllyDuck.second)->change(1, 0); //�Ʊ� ü�� +1
	}
}

//������ Ŭ����
Frog::Frog(unsigned int iTeam) : Animal(2, 1, Animal::Frog, iTeam) {
	this->ability_range = 5;
}
bool Frog::Move(int ax, int ay, int bx, int by) const {
	// x�� �������� �̵� 
	if ((ay == by) && (myabs(ax - bx) == 1)) return Animal::Move(ax, ay, bx, by);
	// y�� �������� �̵� 
	if ((ax == bx) && (myabs(ay - by) == 1)) return Animal::Move(ax, ay, bx, by);
	// �밢�� �������� �̵� 
	if ((myabs(ax - bx) == 1) && (myabs(ay - by) == 1)) return Animal::Move(ax, ay, bx, by);
}
bool Frog::Attack(int ax, int ay, int bx, int by) const {
	if ((myabs(ax - bx) <= 1) || (myabs(ay - by) <= 1)) return true;

	return false;
}
void Frog::own_ability(Board& pBoard, int ax, int ay) {
	/*�ڽŰ� ���� ����(x��, y��)�� �ִ� �Ʊ��� ���ݷ� + 1
	x��� y�࿡ ���� �ִ��� Ȯ��
	�� ���� �Ʊ��̶�� => change(0,1) �̿��ϱ�  */
	pair<int, int> FindAllyFrog;
		// �ֺ� Ȯ��
		for (int i = -4; i <= 4; ++i)
		{
			int newX = ax + i;
			// ��ȿ�� ���� ���� �ִ��� Ȯ��
			if (newX >= 0 && newX < 8)
			{
				// x�࿡ �Ʊ� ���� �ִ��� Ȯ��
				if (pBoard.GetAnimal(newX, ay) != nullptr) { // ���� ó��
					if (pBoard.GetAnimal(newX, ay)->Team == pBoard.GetAnimal(ax, ay)->Team)
					{
						FindAllyFrog = make_pair(newX, ay); //�Ʊ��� ��ǥ ��ȯ
					}
				}
			}
			int newY = ay + i;
			// ��ȿ�� ���� ���� �ִ��� Ȯ��
			if (newY >= 0 && newY < 8)
			{
				// y�࿡ �Ʊ� ���� �ִ��� Ȯ��
				if (pBoard.GetAnimal(ax, newY) != nullptr) { // ���� ó��
					if (pBoard.GetAnimal(ax, newY)->Team == pBoard.GetAnimal(ax, ay)->Team)
					{
						FindAllyFrog = make_pair(ax, newY);
					}
				}
			}
		}

	if (FindAllyFrog.first != -1 && FindAllyFrog.second != -1)
	{
		pBoard.GetAnimal(FindAllyFrog.first, FindAllyFrog.second)->change(0, 1); //�Ʊ� ���ݷ� +1
	}
}


// �䳢 Ŭ���� 
Rabbit::Rabbit(unsigned int iTeam) : Animal(2, 2, Animal::Rabbit, iTeam) {
	// �ڵ� ���� 
}
bool Rabbit::Move(int ax, int ay, int bx, int by) const {
	// x�� �������� �̵� 
	if ((ay == by) && (myabs(ax - bx) == 2)) return Animal::Move(ax, ay, bx, by);
	// y�� �������� �̵� 
	if ((ax == bx) && (myabs(ay - by) == 2)) return Animal::Move(ax, ay, bx, by);
	// �밢�� �������� �̵� 
	if ((myabs(ax - bx) == 2) && (myabs(ay - by) == 2)) return Animal::Move(ax, ay, bx, by);
}
bool Rabbit::Attack(int ax, int ay, int bx, int by) const {
	if ((myabs(ax - bx) <= 2) || (myabs(ay - by) <= 2)) {
		if (((myabs(ax - bx) == 1) && (myabs(ay - by) == 2)) || ((myabs(ay - by) == 1) && (myabs(ax - bx) == 2))) {
			return false;
		}
		return true;
	}

	return false;
}

// ���� Ŭ���� 
Pig::Pig(unsigned int iTeam) : Animal(3, 2, Animal::Pig, iTeam) {
	this->ability_range = 5;
}
bool Pig::Move(int ax, int ay, int bx, int by) const {
	// x�� �������� �̵� 
	if ((ay == by) && (myabs(ax - bx) == 1)) return Animal::Move(ax, ay, bx, by);
	// y�� �������� �̵� 
	if ((ax == bx) && (myabs(ay - by) == 1)) return Animal::Move(ax, ay, bx, by);
	// �밢�� �������� �̵� 
	if ((myabs(ax - bx) == 1) && (myabs(ay - by) == 1)) return Animal::Move(ax, ay, bx, by);
}
bool Pig::Attack(int ax, int ay, int bx, int by) const {
	if ((myabs(ax - bx) <= 1) || (myabs(ay - by) <= 1)) return true;

	return false;
}
// if((turn % 3)== 0) Pig::own_ability(ability_range);
void Pig::own_ability(Board& pBoard, int ax, int ay) {
	//3�� ��� �ϸ��� �ڽ��� �߽����� 5*5 �ȿ� �ִ� ��� ��(���� �� ����)���� ü�� +1 => change(1, 0) �̿��ϱ� 
	int newRow;
	int newCol;
	pair<int, int> findAllyPig;
		// �ֺ� 8ĭ Ȯ��
		for (int i = -2; i <= 2; ++i) {
			for (int j = -2; j <= 2; ++j) 
			{
				newRow = ax + i;
				newCol = ay + j;

				// ��ȿ�� ���� ���� �ִ��� Ȯ��
				if (newRow >= 0 && newRow < 8 && newCol >= 0 && newCol < 8) {
					if (pBoard.GetAnimal(newRow, newCol) != nullptr) { // ���� ó��
						findAllyPig = make_pair(newRow, newCol);
					}
				}
			}
		}

	findAllyPig.first = newRow; //x��ǥ
	findAllyPig.second = newCol; //y��ǥ
	pBoard.GetAnimal(newRow, newCol)->change(1, 0); // ü��+1 
}

// �ϸ� Ŭ���� 
Hippo::Hippo(unsigned int iTeam) : Animal(4, 3, Animal::Hippo, iTeam) {
	// �ڵ� ���� 
}
bool Hippo::Move(int ax, int ay, int bx, int by) const {
	// x�� �������� �̵� 
	if ((ay == by) && (myabs(ax - bx) == 1)) return Animal::Move(ax, ay, bx, by);
	// y�� �������� �̵� 
	if ((ax == bx) && (myabs(ay - by) == 1)) return Animal::Move(ax, ay, bx, by);
	// �밢�� �������� �̵� 
	if ((myabs(ax - bx) == 1) && (myabs(ay - by) == 1)) return Animal::Move(ax, ay, bx, by);
}
bool Hippo::Attack(int ax, int ay, int bx, int by) const {
	if ((myabs(ax - bx) <= 1) || (myabs(ay - by) <= 1)) return true;

	return false;
}
// Hippo�� ������ ������ own_ability(������ ����� survive); ���� 
void Hippo::own_ability(bool enemy_survive) {
	//���� ������ ����� hp�� 0���ϰ� �Ǿ� survive�� false�� �Ǹ� Hippo�� ���ݷ�+1, ü��+1 
	if (!enemy_survive) change(1, 1);
}

// �ڳ��� Ŭ����
Elephant::Elephant(unsigned int iTeam) : Animal(4, 4, Animal::Elephant, iTeam) {
	this->ability_range = 3;
}
bool Elephant::Move(int ax, int ay, int bx, int by) const {
	// x�� �������� �̵� 
	if ((ay == by) && (myabs(ax - bx) == 1)) return Animal::Move(ax, ay, bx, by);
	// y�� �������� �̵� 
	if ((ax == bx) && (myabs(ay - by) == 1)) return Animal::Move(ax, ay, bx, by);
	// �밢�� �������� �̵� 
	if ((myabs(ax - bx) == 1) && (myabs(ay - by) == 1)) return Animal::Move(ax, ay, bx, by);
}
bool Elephant::Attack(int ax, int ay, int bx, int by) const {
	if ((myabs(ax - bx) <= 1) || (myabs(ay - by) <= 1)) return true;

	return false;
}
/* Attack�Լ��� ���ϰ��� true�̸� �ڳ��� ���� ������ ���̹Ƿ�
   own_ability�Լ� ���� */
void Elephant::own_ability(Board& pBoard, int ax, int ay) {
	//���� �� �ڽ��� �߽����� 3*3 �ȿ� �ִ� ��� ��(�Ʊ� �� ����) ü��-1
	int newRow;
	int newCol;
	pair<int, int> findAllyElephant;
		// �ֺ� 8ĭ Ȯ��
		for (int i = -1; i <= 1; ++i) {
			for (int j = -1; j <= 1; ++j) {
				newRow = ax + i;
				newCol = ay + j;

				// ��ȿ�� ���� ���� �ִ��� Ȯ��
				if (newRow >= 0 && newRow < 8 && newCol >= 0 && newCol < 8) {
					if (pBoard.GetAnimal(newRow, newCol) != nullptr) { // ���� ó��
						findAllyElephant = make_pair(newRow, newCol);
					}
				}
			}
		}
	findAllyElephant.first = newRow; // x��ǥ
	findAllyElephant.second = newCol; // y��ǥ
	pBoard.GetAnimal(newRow, newCol)->change(-1, 0); //ü�� -1 
}
