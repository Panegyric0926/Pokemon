#pragma once

#include <string>
#include <stdlib.h>
#include <iostream>

using namespace std;

#define dbout cout
#define dbin cin

class Pokemon; //declaration

enum PokemonType
{
	ATK, //high attack
	HP,  //high HP
	DEF, //high defence
	SPE	 //high speed
};

class PokemonBase
{
protected: //all those attributes can be changed by derived classes
	string _raceName;
	PokemonType _type;
	int _baseAtk; //influenced by PokemonType
	int _baseDef;
	int _baseHp;
	int _baseSpeed;
	int _expCurve[14];	  //from LV2 to LV15
	string _skillName[4]; //one simple attack, 3 special skills
	string _skillDscp[4]; //skill description
	int _pp[3];			  //power point, simple attack has infinite pp

public:
	PokemonBase(PokemonType type);

	//getter
	string raceName() const { return _raceName; }
	PokemonType type() const { return _type; }
	int baseAtk() const { return _baseAtk; }
	int baseDef() const { return _baseDef; }
	int baseHp() const { return _baseHp; }
	int baseSpeed() const { return _baseSpeed; }
	string skillName(int n) const;
	string skillDscp(int n) const;
	int pp(int n) const;

	//about level-up
	int expCurve(int level) const; // 2 <= level <= 15

	//virtual methods
	virtual bool attack(Pokemon& attacker, Pokemon& aim, int skillIndex = 0) const = 0;

	bool dodge(int attacker, int aim) const;
};

class Pokemon
{
private:
	const PokemonBase& _race;
	string _name;
	int _atk;
	int _def;
	int _maxHp;
	int _speed;
	int _lv; //level
	int _exp;

	//in battle
	int _hp;
	int _catk; //current atk
	int _cdef;
	int _cspeed;
	int _cpp[3]; //power point

public:
	Pokemon(const PokemonBase& race, const string& name = "");

	//getter
	string name() const { return _name; }
	int atk() const { return _atk; }
	int def() const { return _def; }
	int maxHp() const { return _maxHp; }
	int speed() const { return _speed; }
	int lv() const { return _lv; }
	int exp() const { return _exp; }
	//race getter
	string raceName() const { return _race.raceName(); }
	string raceType() const;
	string skillName(int n) const { return _race.skillName(n); }
	string skillDscp(int n) const { return _race.skillDscp(n); }
	int pp(int i) const { return _race.pp(i); }

	//about battle
	void restoreAll();
	bool attack(Pokemon& aim, bool autoFight = true);
	bool takeDamage(int n);
	bool gainExp(int count); //return true if level-up
	//getter
	int catk() const { return _catk; }
	int cdef() const { return _cdef; }
	int hp() const { return _hp; }
	int cspeed() const { return _cspeed; }
	int cpp(int n) const;
	//setter
	void changeAtk(int count); //change current atk
	void changeDef(int count);
	void changeSpeed(int count);
	bool changeHp(int count); //return true if hp = 0
};

int f(int n); //get a random number from -n to n

template <int N>
class Race : public PokemonBase
{
public:
	Race();
	bool attack(Pokemon& attacker, Pokemon& aim, int skillIndex = 0) const;
};