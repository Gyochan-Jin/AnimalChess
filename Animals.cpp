#include "Animals.h"
#include "Board.h"
#include <utility>
#include <string>

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


void Cow::own_ability(int ability_range, int hp) {
	//피격 시 자신을 중심으로 3*3 안에 있는 아군에게 공격력+1/체력+1 => change(1, 1) 이용하기

	pair<int, int> findAllyCow(int ax, int ay) {
		// 주변 8칸 확인
		for (int i = -1; i <= 1; ++i) {
			for (int j = -1; j <= 1; ++j) {
				int newRow = ax + i;
				int newCol = ay + j;

				// 유효한 범위 내에 있는지 확인
				if (newRow >= 0 && newRow < 8 && newCol >= 0 && newCol < 8) {
					// 아군 말이 있는지 확인
					if (board[newRow][newCol].team == board[ax][ay].team) {
						return make_pair(newRow, newCol);
					}
				}
			}
		}
		// 주변에 아군 말이 없으면 (-1, -1)을 반환
		return make_pair(-1, -1);
	}

	pair<int, int> Coord = findAllyCow(int ax, int ay);
	int newRow = Coord.first; //아군위치 x좌표
	int newCol = Coord.second; //아군위치 y좌표
	pBoard[newRow][newCol].change(1, 1); //아군 공격력 +1
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


void Duck::own_ability(int ability_range) {
	//자신을 중심으로 3*3 안에 있는 아군이 피격 시 해당 아군의 체력+1 => change(1, 0) 이용하기
	pair<int, int> findAllyDuck(int ax, int ay, int hp, int enemy_attack_damage) {
		// 주변 8칸 확인
		for (int i = -1; i <= 1; ++i) {
			for (int j = -1; j <= 1; ++j) {
				int newRow = ax + i;
				int newCol = ay + j;

				// 유효한 범위 내에 있는지 확인
				if (newRow >= 0 && newRow < 8 && newCol >= 0 && newCol < 8) {
					// 아군 말이 있는지 확인
					if (board[newRow][newCol].team == board[ax][ay].team) {
						return make_pair(newRow, newCol);
					}
				}
			}
		}

		// 주변에 아군 말이 없으면 (-1, -1)을 반환
		return make_pair(-1, -1);
	}

	pair<int, int> Coord = findAllyDuck(int ax, int ay);
	int AllyX = Coord.first;
	int AllyY = Coord.Second;
	bool isgetDamage(int hp, int enemy_attack_damage) {
		int newhp = hp - enemy_attack_damage;
		return newhp <= 0;
	}
	if (Coord.first != -1 && Coord.second != -1)
	{
		if (isgetDamage(pBoard[AllyX][AllyY].hp, enemy_attack_Damage))
		{
			pBoard[AllyX][AllyY].change(1, 0); //아군 체력 +1
		}
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
void Frog::own_ability(int ability_range) {
	/*자신과 같은 라인(x축, y축)에 있는 아군의 공격력 + 1
	x축과 y축에 말이 있는지 확인
	그 말이 아군이라면 => change(0,1) 이용하기  */
	pair<int, int> AllyCheck(int ax, int ay) {
		// 주변 확인
		for (int i = -4; i <= 4; ++i)
		{
			int newX = ax + i;
			// 유효한 범위 내에 있는지 확인
			if (newX >= 0 && newX < 8)
			{
				// x축에 아군 말이 있는지 확인
				if (pBoard[newX][ay].team == pBoard[ax][ay].team)
				{
					return make_pair(newX, ay); //아군말 좌표 반환
				}
			}
			int newY = ay + i;
			// 유효한 범위 내에 있는지 확인
			if (newY >= 0 && newY < 8)
			{
				// y축에 아군 말이 있는지 확인
				if (pBoard[ax][newY].team == pBoard[ax][ay].team)
				{
					return make_pair(ax, newY);
				}
			}
		}
		return make_pair(-1, -1);
	}
	pair<int, int> Coord = AllyCheck(int ax, int ay);
	if (Coord.first != -1 && Coord.second != -1)
	{
		pBoard[AllyX][AllyY].change(0, 1); //아군 공격력 +1
	}
}


// 토끼 클래스 
Rabbit::Rabbit(unsigned int iTeam) : Animal(2, 2, Animal::Rabbit, iTeam){
	// 코드 없음 
}
bool Rabbit::Move(int ax, int ay, int bx, int by) const{
	// x축 방향으로 이동 
	if((ay == by) && (myabs(ax - bx) == 2)) return Animal::Move(ax, ay, bx, by);
	// y축 방향으로 이동 
	if((ax == bx) && (myabs(ay - by) == 2)) return Animal::Move(ax, ay, bx, by);
	// 대각선 방향으로 이동 
	if((myabs(ax - bx) == 2) && (myabs(ay - by) == 2)) return Animal::Move(ax, ay, bx, by);
}
bool Rabbit::Attack(int ax, int ay, int bx, int by) const{
	if((myabs(ax - bx) <= 2) || (myabs(ay - by) <= 2)){
		if(((myabs(ax - bx) == 1) && (myabs(ay - by) == 2)) || ((myabs(ay - by) == 1) && (myabs(ax - bx) == 2))){
			return false;
		}
		return true;
	}

	return false;
}

// 돼지 클래스 
Pig::Pig(unsigned int iTeam) : Animal(3, 2, Animal::Pig, iTeam){
	this->ability_range = 5;
}
bool Pig::Move(int ax, int ay, int bx, int by) const{
	// x축 방향으로 이동 
	if((ay == by) && (myabs(ax - bx) == 1)) return Animal::Move(ax, ay, bx, by);
	// y축 방향으로 이동 
	if((ax == bx) && (myabs(ay - by) == 1)) return Animal::Move(ax, ay, bx, by);
	// 대각선 방향으로 이동 
	if((myabs(ax - bx) == 1) && (myabs(ay - by) == 1)) return Animal::Move(ax, ay, bx, by);
}
bool Pig::Attack(int ax, int ay, int bx, int by) const{
	if((myabs(ax - bx) <= 1) || (myabs(ay - by) <= 1)) return true;
	
	return false;
}
// if((turn % 3)== 0) Pig::own_ability(ability_range);
void Pig::own_ability(int ability_range){
	//3의 배수 턴마다 자신을 중심으로 5*5 안에 있는 모든 말(적의 말 포함)에게 체력 +1 => change(1, 0) 이용하기 
}

// 하마 클래스 
Hippo::Hippo(unsigned int iTeam) : Animal(4, 3, Animal::Hippo, iTeam){
	// 코드 없음 
}
bool Hippo::Move(int ax, int ay, int bx, int by) const{
	// x축 방향으로 이동 
	if((ay == by) && (myabs(ax - bx) == 1)) return Animal::Move(ax, ay, bx, by);
	// y축 방향으로 이동 
	if((ax == bx) && (myabs(ay - by) == 1)) return Animal::Move(ax, ay, bx, by);
	// 대각선 방향으로 이동 
	if((myabs(ax - bx) == 1) && (myabs(ay - by) == 1)) return Animal::Move(ax, ay, bx, by);
}
bool Hippo::Attack(int ax, int ay, int bx, int by) const{
	if((myabs(ax - bx) <= 1) || (myabs(ay - by) <= 1)) return true;
	
	return false;
}
void Hippo::own_ability(bool enemy_survive){
	//만약 공격한 상대의 hp가 0이하가 되어 survive가 false가 되면 공격력+1, 체력+1 
	if(!enemy_survive) change(1, 1); 
}

// 코끼리 클래스
Elephant::Elephant(unsigned int iTeam) : Animal(4, 4, Animal::Elephant, iTeam){
	this->ability_range = 3;
}
bool Elephant::Move(int ax, int ay, int bx, int by) const{
	// x축 방향으로 이동 
	if((ay == by) && (myabs(ax - bx) == 1)) return Animal::Move(ax, ay, bx, by);
	// y축 방향으로 이동 
	if((ax == bx) && (myabs(ay - by) == 1)) return Animal::Move(ax, ay, bx, by);
	// 대각선 방향으로 이동 
	if((myabs(ax - bx) == 1) && (myabs(ay - by) == 1)) return Animal::Move(ax, ay, bx, by);
}
bool Elephant::Attack(int ax, int ay, int bx, int by) const{
	if((myabs(ax - bx) <= 1) || (myabs(ay - by) <= 1)) return true;
	
	return false;
}
/* Attack함수의 리턴값이 true이면 코끼리 말이 공격한 것이므로
   own_ability함수 실행 */ 
void Elephant::own_ability(int ability_range){
	//공격 시 자신을 중심으로 3*3 안에 있는 모든 말(아군 말 포함) 체력-1
}