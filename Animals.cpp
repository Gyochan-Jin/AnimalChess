#include "Animals.h"
#include "Board.h"
#include <utility>
#include <string>
#include <stdbool.h>

using namespace std;

// 절댓값을 구하는 간단한 매크로
#define myabs(x) ((x) < 0 ? -(x) : (x))

//소 클래스
Cow::Cow(unsigned int iTeam) : Animal(5, 3, Animal::Cow, iTeam) {
	this->ability_range = 5;
}
bool Cow::Move(int ax, int ay, int bx, int by) const {
	// x축 방향으로 이동 
	if ((ay == by) && (myabs(ax - bx) == 1)) return Animal::Move(ax, ay, bx, by);
	// y축 방향으로 이동 
	if ((ax == bx) && (myabs(ay - by) == 1)) return Animal::Move(ax, ay, bx, by);
	// 대각선 방향으로 이동 
	if ((myabs(ax - bx) == 1) && (myabs(ay - by) == 1)) return Animal::Move(ax, ay, bx, by);
}
bool Cow::Attack(int ax, int ay, int bx, int by) const {
	if ((myabs(ax - bx) <= 1) || (myabs(ay - by) <= 1)) return true;

	return false;
}


void Cow::own_ability(Board& pBoard, int ax, int ay) {
	//피격 시 자신을 중심으로 3*3 안에 있는 아군에게 공격력+1/체력+1 => change(1, 1) 이용하기
	int newRow;
	int newCol;
	pair<int, int> findAllyCow; 
		// 주변 8칸 확인
		for (int i = -1; i <= 1; ++i) 
		{
			for (int j = -1; j <= 1; ++j) 
			{
				newRow = ax + i;
				newCol = ay + j;

				// 유효한 범위 내에 있는지 확인
				if (newRow >= 0 && newRow < 8 && newCol >= 0 && newCol < 8) {
					// 아군 말이 있는지 확인
					if (pBoard.GetAnimal(newRow, newCol)->Team == pBoard.GetAnimal(ax, ay)->Team) {
						findAllyCow = make_pair(newRow, newCol);
					}
				}
			}
		}
	findAllyCow.first = newRow; //아군위치 x좌표
	findAllyCow.second = newCol; //아군위치 y좌표
	pBoard.GetAnimal(newRow, newCol)->change(1, 1); //아군 공격력 +1
}

//오리 클래스
Duck::Duck(unsigned int iTeam) : Animal(3, 1, Animal::Duck, iTeam) {
	this->ability_range = 5;
}
bool Duck::Move(int ax, int ay, int bx, int by) const {
	// x축 방향으로 이동 
	if ((ay == by) && (myabs(ax - bx) == 1)) return Animal::Move(ax, ay, bx, by);
	// y축 방향으로 이동 
	if ((ax == bx) && (myabs(ay - by) == 1)) return Animal::Move(ax, ay, bx, by);
	// 대각선 방향으로 이동 
	if ((myabs(ax - bx) == 1) && (myabs(ay - by) == 1)) return Animal::Move(ax, ay, bx, by);
}
bool Duck::Attack(int ax, int ay, int bx, int by) const {
	if ((myabs(ax - bx) <= 1) || (myabs(ay - by) <= 1)) return true;

	return false;
}


void Duck::own_ability(Board& pBoard, int ax, int ay) {
	//자신을 중심으로 3*3 안에 있는 아군이 피격 시 해당 아군의 체력+1 => change(1, 0) 이용하기
	int newRow;
	int newCol;
	pair<int, int> findAllyDuck;
		// 주변 8칸 확인
		for (int i = -1; i <= 1; ++i) 
		{
			for (int j = -1; j <= 1; ++j) 
			{
				newRow = ax + i;
				newCol = ay + j;
				// 유효한 범위 내에 있는지 확인
				if (newRow >= 0 && newRow < 8 && newCol >= 0 && newCol < 8)
				{
					// 아군 말이 있는지 확인
					if (pBoard.GetAnimal(newRow, newCol) != nullptr) { // 예외 처리
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
		pBoard.GetAnimal(findAllyDuck.first, findAllyDuck.second)->change(1, 0); //아군 체력 +1
	}
}

//개구리 클래스
Frog::Frog(unsigned int iTeam) : Animal(2, 1, Animal::Frog, iTeam) {
	this->ability_range = 5;
}
bool Frog::Move(int ax, int ay, int bx, int by) const {
	// x축 방향으로 이동 
	if ((ay == by) && (myabs(ax - bx) == 1)) return Animal::Move(ax, ay, bx, by);
	// y축 방향으로 이동 
	if ((ax == bx) && (myabs(ay - by) == 1)) return Animal::Move(ax, ay, bx, by);
	// 대각선 방향으로 이동 
	if ((myabs(ax - bx) == 1) && (myabs(ay - by) == 1)) return Animal::Move(ax, ay, bx, by);
}
bool Frog::Attack(int ax, int ay, int bx, int by) const {
	if ((myabs(ax - bx) <= 1) || (myabs(ay - by) <= 1)) return true;

	return false;
}
void Frog::own_ability(Board& pBoard, int ax, int ay) {
	/*자신과 같은 라인(x축, y축)에 있는 아군의 공격력 + 1
	x축과 y축에 말이 있는지 확인
	그 말이 아군이라면 => change(0,1) 이용하기  */
	pair<int, int> FindAllyFrog;
		// 주변 확인
		for (int i = -4; i <= 4; ++i)
		{
			int newX = ax + i;
			// 유효한 범위 내에 있는지 확인
			if (newX >= 0 && newX < 8)
			{
				// x축에 아군 말이 있는지 확인
				if (pBoard.GetAnimal(newX, ay) != nullptr) { // 예외 처리
					if (pBoard.GetAnimal(newX, ay)->Team == pBoard.GetAnimal(ax, ay)->Team)
					{
						FindAllyFrog = make_pair(newX, ay); //아군말 좌표 반환
					}
				}
			}
			int newY = ay + i;
			// 유효한 범위 내에 있는지 확인
			if (newY >= 0 && newY < 8)
			{
				// y축에 아군 말이 있는지 확인
				if (pBoard.GetAnimal(ax, newY) != nullptr) { // 예외 처리
					if (pBoard.GetAnimal(ax, newY)->Team == pBoard.GetAnimal(ax, ay)->Team)
					{
						FindAllyFrog = make_pair(ax, newY);
					}
				}
			}
		}

	if (FindAllyFrog.first != -1 && FindAllyFrog.second != -1)
	{
		pBoard.GetAnimal(FindAllyFrog.first, FindAllyFrog.second)->change(0, 1); //아군 공격력 +1
	}
}


// 토끼 클래스 
Rabbit::Rabbit(unsigned int iTeam) : Animal(2, 2, Animal::Rabbit, iTeam) {
	// 코드 없음 
}
bool Rabbit::Move(int ax, int ay, int bx, int by) const {
	// x축 방향으로 이동 
	if ((ay == by) && (myabs(ax - bx) == 2)) return Animal::Move(ax, ay, bx, by);
	// y축 방향으로 이동 
	if ((ax == bx) && (myabs(ay - by) == 2)) return Animal::Move(ax, ay, bx, by);
	// 대각선 방향으로 이동 
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

// 돼지 클래스 
Pig::Pig(unsigned int iTeam) : Animal(3, 2, Animal::Pig, iTeam) {
	this->ability_range = 5;
}
bool Pig::Move(int ax, int ay, int bx, int by) const {
	// x축 방향으로 이동 
	if ((ay == by) && (myabs(ax - bx) == 1)) return Animal::Move(ax, ay, bx, by);
	// y축 방향으로 이동 
	if ((ax == bx) && (myabs(ay - by) == 1)) return Animal::Move(ax, ay, bx, by);
	// 대각선 방향으로 이동 
	if ((myabs(ax - bx) == 1) && (myabs(ay - by) == 1)) return Animal::Move(ax, ay, bx, by);
}
bool Pig::Attack(int ax, int ay, int bx, int by) const {
	if ((myabs(ax - bx) <= 1) || (myabs(ay - by) <= 1)) return true;

	return false;
}
// if((turn % 3)== 0) Pig::own_ability(ability_range);
void Pig::own_ability(Board& pBoard, int ax, int ay) {
	//3의 배수 턴마다 자신을 중심으로 5*5 안에 있는 모든 말(적의 말 포함)에게 체력 +1 => change(1, 0) 이용하기 
	int newRow;
	int newCol;
	pair<int, int> findAllyPig;
		// 주변 8칸 확인
		for (int i = -2; i <= 2; ++i) {
			for (int j = -2; j <= 2; ++j) 
			{
				newRow = ax + i;
				newCol = ay + j;

				// 유효한 범위 내에 있는지 확인
				if (newRow >= 0 && newRow < 8 && newCol >= 0 && newCol < 8) {
					if (pBoard.GetAnimal(newRow, newCol) != nullptr) { // 예외 처리
						findAllyPig = make_pair(newRow, newCol);
					}
				}
			}
		}

	findAllyPig.first = newRow; //x좌표
	findAllyPig.second = newCol; //y좌표
	pBoard.GetAnimal(newRow, newCol)->change(1, 0); // 체력+1 
}

// 하마 클래스 
Hippo::Hippo(unsigned int iTeam) : Animal(4, 3, Animal::Hippo, iTeam) {
	// 코드 없음 
}
bool Hippo::Move(int ax, int ay, int bx, int by) const {
	// x축 방향으로 이동 
	if ((ay == by) && (myabs(ax - bx) == 1)) return Animal::Move(ax, ay, bx, by);
	// y축 방향으로 이동 
	if ((ax == bx) && (myabs(ay - by) == 1)) return Animal::Move(ax, ay, bx, by);
	// 대각선 방향으로 이동 
	if ((myabs(ax - bx) == 1) && (myabs(ay - by) == 1)) return Animal::Move(ax, ay, bx, by);
}
bool Hippo::Attack(int ax, int ay, int bx, int by) const {
	if ((myabs(ax - bx) <= 1) || (myabs(ay - by) <= 1)) return true;

	return false;
}
// Hippo가 공격한 다음에 own_ability(공격한 상대의 survive); 실행 
void Hippo::own_ability(bool enemy_survive) {
	//만약 공격한 상대의 hp가 0이하가 되어 survive가 false가 되면 Hippo의 공격력+1, 체력+1 
	if (!enemy_survive) change(1, 1);
}

// 코끼리 클래스
Elephant::Elephant(unsigned int iTeam) : Animal(4, 4, Animal::Elephant, iTeam) {
	this->ability_range = 3;
}
bool Elephant::Move(int ax, int ay, int bx, int by) const {
	// x축 방향으로 이동 
	if ((ay == by) && (myabs(ax - bx) == 1)) return Animal::Move(ax, ay, bx, by);
	// y축 방향으로 이동 
	if ((ax == bx) && (myabs(ay - by) == 1)) return Animal::Move(ax, ay, bx, by);
	// 대각선 방향으로 이동 
	if ((myabs(ax - bx) == 1) && (myabs(ay - by) == 1)) return Animal::Move(ax, ay, bx, by);
}
bool Elephant::Attack(int ax, int ay, int bx, int by) const {
	if ((myabs(ax - bx) <= 1) || (myabs(ay - by) <= 1)) return true;

	return false;
}
/* Attack함수의 리턴값이 true이면 코끼리 말이 공격한 것이므로
   own_ability함수 실행 */
void Elephant::own_ability(Board& pBoard, int ax, int ay) {
	//공격 시 자신을 중심으로 3*3 안에 있는 모든 말(아군 말 포함) 체력-1
	int newRow;
	int newCol;
	pair<int, int> findAllyElephant;
		// 주변 8칸 확인
		for (int i = -1; i <= 1; ++i) {
			for (int j = -1; j <= 1; ++j) {
				newRow = ax + i;
				newCol = ay + j;

				// 유효한 범위 내에 있는지 확인
				if (newRow >= 0 && newRow < 8 && newCol >= 0 && newCol < 8) {
					if (pBoard.GetAnimal(newRow, newCol) != nullptr) { // 예외 처리
						findAllyElephant = make_pair(newRow, newCol);
					}
				}
			}
		}
	findAllyElephant.first = newRow; // x좌표
	findAllyElephant.second = newCol; // y좌표
	pBoard.GetAnimal(newRow, newCol)->change(-1, 0); //체력 -1 
}
