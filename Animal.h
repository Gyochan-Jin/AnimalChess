#pragma once

class Animal{
	private:
		int hp; // 체력 
		int attack_damage; // 공격력 
		bool survive; // 생존여부 확인 
		unsigned int iType;
		unsigned int iTeam;
	public:
		enum{
			Cow = 1,
			Duck = 2,
			Frog = 3,
			Rabbit = 4,
			Pig = 5,
			Hippo = 6,
			Elephant = 7
		};
		
		enum{
			player1 = 0,
			player2 = 1
		};
	
	protected:
		Animal(int hp, int attack_damage, unsigned int iType, unsigned int iTeam);
	
	public:
		Animal(const Animal &animal);		
		virtual bool Move(int ax, int ay, int bx, int by) const;
		virtual bool Attack(int ax, int ay, int bx, int by) const;
		// 공격한 상대방 말의 공격력만큼 데미지를 입는 함수 
		void damaged(int attack_damage);
		// 말의 능력 중 hp와 공격력을 변화시키는 능력을 구현한 함수(소, 오리, 개구리, 돼지, 하마) 
		void change(int hp, int attack_damage);
		int get_attack_damage();
		const int get_attack_damage() const;
		bool get_survive();
		int get_hp();
		const int get_hp() const;
		unsigned int get_team();
		unsigned int get_type();
		
	public:
		const unsigned int &Type = iType;
		const unsigned int &Team = iTeam;
};
