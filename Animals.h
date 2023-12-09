#pragma once

#include "Animal.h"

class Cow : public Animal {
private:
	int ability_range; // 능력범위
public:
	Cow(unsigned int iTeam);
	bool Move(int ax, int ay, int bx, int by) const;
	bool Attack(int ax, int ay, int bx, int by) const;
	void own_ability(int ability_range, int hp, int ax, int ay);
};
class Duck : public Animal {
private:
	int ability_range; // 능력범위
public:
	Duck(unsigned int iTeam);
	bool Move(int ax, int ay, int bx, int by) const;
	bool Attack(int ax, int ay, int bx, int by) const;
	void own_ability(int ability_range, int ax, int ay);
};
class Frog : public Animal {
private:
	int ability_range; // 능력범위
public:
	Frog(unsigned int iTeam);
	bool Move(int ax, int ay, int bx, int by) const;
	bool Attack(int ax, int ay, int bx, int by) const;
	void own_ability(int ability_range, int ax, int ay);
};

class Rabbit : public Animal{		
	public:
		Rabbit(unsigned int iTeam);
		bool Move(int ax, int ay, int bx, int by) const;
		bool Attack(int ax, int ay, int bx, int by) const; 
};

class Pig : public Animal{
	private:
		int ability_range; // 능력범위
	public:
		Pig(unsigned int iTeam);
		bool Move(int ax, int ay, int bx, int by) const;
		bool Attack(int ax, int ay, int bx, int by) const;
		void own_ability(int ability_range, int ax, int ay);
};

class Hippo : public Animal{
	public:
		Hippo(unsigned int iTeam);
		bool Move(int ax, int ay, int bx, int by) const;
		bool Attack(int ax, int ay, int bx, int by) const;
		void own_ability(bool enemy_survive);
};

class Elephant : public Animal{
	private:
		int ability_range; // 능력범위
	public:
		Elephant(unsigned int iTeam);
		bool Move(int ax, int ay, int bx, int by) const;
		bool Attack(int ax, int ay, int bx, int by) const;
		void own_ability(int ability_range, int ax, int ay);
};
