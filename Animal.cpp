#include "Animal.h"

Animal::Animal(int hp, int attack_damage, unsigned int iType, unsigned int iTeam)
	: iType(iType), iTeam(iTeam) {
	this->hp = hp;
	this->attack_damage = attack_damage;
	this->survive = true;
}

Animal::Animal(const Animal &animal)
	: iType(animal.Type), iTeam(animal.Team) {
	// 코드 없음 
}

bool Animal::Move(int ax, int ay, int bx, int by) const {
	// 모든 말은 8칸 내에서 움직일 수 있다.
	// 자기 자신이 있는 곳은 이동할 수 없다.
	return (!(ax < 0 || ax >= 8 || ay < 0 || ay >= 8)) && (!(ax == bx && ay == by));
}

bool Animal::Attack(int ax, int ay, int bx, int by) const {
	return Animal::Move(ax, ay, bx, by);
}

void Animal::damaged(int attack_damage){
	this->hp -= attack_damage;
	if(hp <= 0) survive = false;
}

void Animal::change(int hp, int attack_damage){
	this->hp += hp;
	this->attack_damage += attack_damage;
	if(hp <= 0) survive = false;
}

int Animal::get_attack_damage(){
	return attack_damage;
}

bool Animal::get_survive(){
	return survive;
}
