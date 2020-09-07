#include "pokemon.h"

PokemonBase::PokemonBase(PokemonType type)
{
	_type = type;

	//standard attribute
	_baseAtk = 10;
	_baseDef = 5;
	_baseHp = 25;
	_baseSpeed = 10;

	//type talent
	switch (type)
	{
	case ATK:
		_baseAtk += 3;
		break;
	case DEF:
		_baseDef += 3;
		break;
	case HP:
		_baseHp += 10;
		break;
	case SPE:
		_baseSpeed += 5;
		break;
	default:
		break;
	}
}

string PokemonBase::skillName(int n) const
{
	if (n >= 0 && n <= 3)
	{
		return _skillName[n];
	}
	return "";
}

string PokemonBase::skillDscp(int n) const
{
	if (n >= 0 && n <= 3)
	{
		return _skillDscp[n];
	}
	return "";
}

int PokemonBase::pp(int n) const
{
	if (n >= 0 && n <= 2)
	{
		return _pp[n];
	}
	return 0;
}

int PokemonBase::expCurve(int level) const
{
	if (level <= 15 && level >= 2)
	{
		return _expCurve[level - 2];
	}
	return 0;
}

bool PokemonBase::dodge(int attacker, int aim) const
{
	if ((attacker + f(40)) / 80 - aim / 150 < 0)
	{
		dbout << "Miss!\n";
		return true;
	}
	return false;
}

Pokemon::Pokemon(const PokemonBase& race, const string& name) : _race(race)
{
	if (!name.length())
	{
		_name = _race.raceName(); //use race name as default name
	}
	else
	{
		_name = name;
	}

	//add some random factor
	_atk = _race.baseAtk() + f(3);
	_def = _race.baseDef() + f(2);
	_maxHp = _hp = _race.baseHp() + f(5);
	_speed = _race.baseSpeed() + f(3);

	_lv = 1;
	_exp = 0;

	for (int i = 0; i < 3; ++i)
	{
		_cpp[i] = _race.pp(i);
	}

	//output info
	dbout << "Init " << _name << " from " << _race.raceName() << endl
		<< "Type: " << raceType() << endl
		<< "Atk: " << _atk << endl
		<< "Def: " << _def << endl
		<< "MaxHp: " << _maxHp << endl
		<< "Speed: " << _speed << endl
		<< "LV: " << _lv << endl
		<< "Exp: " << _exp << endl;
	//output skill
	dbout << "Skills:\n";
	for (int i = 0; i < 4; ++i)
	{
		dbout << "	Name: " << _race.skillName(i) << endl;
		dbout << "	Description: " << _race.skillDscp(i) << endl;
		if (i)
		{
			dbout << "	PP: " << _race.pp(i - 1) << endl;
		}
		else
		{
			dbout << "	PP: infinity\n";
		}
	}
	dbout << endl;
}

string Pokemon::raceType() const
{
	switch (_race.type())
	{
	case ATK:
		return "High Attack";
	case HP:
		return "High HP";
	case DEF:
		return "High Defence";
	case SPE:
		return "High Speed";
	default:
		break;
	}
	return "";
}

int Pokemon::cpp(int n) const
{
	if (n >= 0 || n <= 2)
	{
		return _cpp[n];
	}
	return 0;
}

void Pokemon::changeAtk(int count)
{
	_catk += count;
	if (_catk < 1)
		_catk = 1;

	if (count > 0)
	{
		dbout << _name << "'s Attack +" << count << endl;
	}
	else
	{
		dbout << _name << "'s Attack " << count << endl;
	}

	dbout << _name << "'s Attack becomes " << _catk << endl
		<< endl;
}

void Pokemon::changeDef(int count)
{
	_cdef += count;
	if (_cdef < 1)
		_cdef = 1;

	if (count > 0)
	{
		dbout << _name << "'s Defence +" << count << endl;
	}
	else
	{
		dbout << _name << "'s Defence " << count << endl;
	}
	dbout << _name << "'s Defence becomes " << _cdef << endl
		<< endl;
}

void Pokemon::changeSpeed(int count)
{
	_cspeed += count;
	if (_cspeed < 1)
		_cspeed = 1;

	if (count > 0)
	{
		dbout << _name << "'s Speed +" << count << endl;
	}
	else
	{
		dbout << _name << "'s Speed " << count << endl;
	}
	dbout << _name << "'s Speed becomes " << _cspeed << endl
		<< endl;
}

bool Pokemon::changeHp(int count)
{
	_hp += count;

	if (_hp > _maxHp)
		_hp = _maxHp;
	if (_hp < 0)
		_hp = 0;

	if (count > 0)
	{
		dbout << _name << " restores " << count << "HP!\n";
	}
	else
	{
		dbout << _name << " takes " << -count << " damage!\n";
	}
	if (!_hp)
	{
		dbout << _name << " is down!\n\n";
		return true;
	}
	else
	{
		dbout << _name << "'s HP becomes " << _hp << endl
			<< endl;
	}
	return false;
}

void Pokemon::restoreAll()
{
	_hp = _maxHp;
	_catk = _atk;
	_cdef = _def;
	_cspeed = _speed;
	for (int i = 0; i < 3; ++i)
	{
		_cpp[i] = _race.pp(i);
	}
}

bool Pokemon::gainExp(int count)
{
	if (_lv == 15)
		return false;

	if (count <= 0)
		count = 1;

	_exp += count;

	dbout << _name << " gains " << count << " exp!\n";
	dbout << "Now " << _name << " has " << _exp << " exp\n"
		<< endl;

	bool LV_UP = false;
	while (_lv < 15 && _exp > _race.expCurve(_lv + 1))
	{
		//level-up!
		LV_UP = true;
		++_lv;
		dbout << "Level Up!\n";
		dbout << _name << "'s now LV" << _lv << "!\n"
			<< endl;

		//increase attributes
		int atk, def, maxHp, speed;
		atk = 4 + f(1);
		def = 2 + f(1);
		maxHp = 8 + f(2);
		speed = 5 + f(1);

		//race talent
		switch (_race.type())
		{
		case ATK:
			atk += 3;
			break;
		case HP:
			maxHp += 5;
			break;
		case DEF:
			def += 3;
			break;
		case SPE:
			speed += 3;
			break;
		default:
			break;
		}

		_atk += atk;
		_def += def;
		_maxHp += maxHp;
		_speed += speed;

		dbout << "Atk: " << _atk - atk << "->" << _atk << "!\n";
		dbout << "Def: " << _def - def << "->" << _def << "!\n";
		dbout << "MaxHP: " << _maxHp - maxHp << "->" << _maxHp << "!\n";
		dbout << "Speed: " << _speed - speed << "->" << _speed << "!\n\n";
	}

	if (LV_UP)
		return true;

	return false; //default
}

bool Pokemon::attack(Pokemon& aim, bool autoFight)
{
	int skillIndex = 0;
	if (autoFight)
	{
		//judge usable skill by LV and PP
		bool usable[3];
		int usableCount = 1;				//can use simple attack by default
		for (int i = 0; i < 3; ++i) //get all usable skill
		{
			if (_lv >= (i + 1) * 5 && _cpp[i])
			{
				usable[i] = true;
				++usableCount;
			}
		}
		//get a random skill
		int use = rand() % usableCount;
		//find the skill
		if (!use)
			skillIndex = 0;
		else
		{
			for (int i = 0; i < 3; ++i)
			{
				if (usable[i])
				{
					--use;
					if (!use)
					{
						skillIndex = i + 1;
						break;
					}
				}
			}
		}
		if (skillIndex > 0)
			--_cpp[skillIndex - 1]; //consume pp
		return _race.attack(*this, aim, skillIndex);
	}

	//manual fight, get skillIndex
	dbout << _name << ", your turn!\n";
	dbout << "Choose a skill to attack!\n";
	int space = 0; //count space
	for (int i = 0; i * 5 <= _lv; ++i)
	{
		if (skillName(i).length() > space)
			space = skillName(i).length();
	}
	space += 4;
	for (int i = 0; i * 5 <= _lv; ++i)
	{
		dbout << "	" << i + 1 << ": " << skillName(i);
		//print PP
		if (i)
		{
			dbout << '(';
			if (_cpp[i - 1] < 10)
			{
				dbout << ' ';
			}
			dbout << _cpp[i - 1] << '/';
			if (_race.pp(i - 1) < 10)
			{
				dbout << ' ';
			}
			dbout << _race.pp(i - 1) << ')';
		}
		for (int j = 0; j < space - skillName(i).length(); ++j)
			dbout << " ";
		if (!i)
		{
			dbout << "       ";
		}
		dbout << skillDscp(i) << endl;
	}
	dbout << "Please input a number: ";
	dbin >> skillIndex;
	dbin.clear();
	dbin.sync();
	dbin.ignore();
	dbout << endl;
	//attack
	--skillIndex;
	if (skillIndex < 0 || skillIndex > 3)
		skillIndex = 0;
	if (skillIndex * 5 <= _lv && _cpp[skillIndex - 1]) //check again by LV and PP
	{
		--_cpp[skillIndex - 1]; //consume PP
		return _race.attack(*this, aim, skillIndex);
	}

	return _race.attack(*this, aim, 0);
}

bool Pokemon::takeDamage(int n)
{
	if (n < 10)
		n = 10;
	return changeHp(-n);
}

int f(int n)
{
	return rand() % (2 * n + 1) - n;
}

template <>
Race<0>::Race() : PokemonBase(ATK)
{
	_raceName = "Charmander";
	_expCurve[0] = 5;
	for (int i = 1; i < 14; ++i)
	{
		_expCurve[i] = _expCurve[i - 1] + 5 * i;
	}
	_skillName[0] = "Scratch";
	_skillName[1] = "Growl";
	_skillName[2] = "Ember";
	_skillName[3] = "Flamethrower";
	_skillDscp[0] = "Basic Attack.";
	_skillDscp[1] = "Ignore Your Opponent's Defence!";
	_skillDscp[2] = "Increase Your Attack!";
	_skillDscp[3] = "Lots Of Damage!!!!!!!!";
	_pp[0] = 10;
	_pp[1] = 3;
	_pp[2] = 5;
}

template <>
bool Race<0>::attack(Pokemon& attacker, Pokemon& aim, int skillIndex) const
{
	dbout << attacker.name() << " uses " << attacker.skillName(skillIndex) << "!\n";

	switch (skillIndex)
	{
	case 1:
	{
		if (dodge(attacker.cspeed(), aim.cspeed()))
			return false;

		int dmg = attacker.catk() + attacker.lv() * 2 - aim.cdef() / 2 + f(4);
		return aim.takeDamage(dmg);

		break;
	}
	case 2:
		attacker.changeAtk(attacker.atk() / 8);
		break;
	case 3: 
	{
		if (dodge(attacker.cspeed(), aim.cspeed()))
			return false;

		int dmg = attacker.catk() * 1.5 - aim.cdef() + 8 + f(4 + attacker.lv());
		return aim.takeDamage(dmg);

		break;
	}
	default:
	{
		
		if (dodge(attacker.cspeed(), aim.cspeed()))
			return false;

		int dmg = attacker.catk() - aim.cdef() + f(4);
		return aim.takeDamage(dmg);

		break;
	}
	} //switch
	return false;
}

template <>
Race<1>::Race() : PokemonBase(HP)
{
	_raceName = "Bulbasaur";
	_expCurve[0] = 5;
	for (int i = 1; i < 14; ++i)
	{
		_expCurve[i] = _expCurve[i - 1] + 5 * i;
	}
	_skillName[0] = "Tackle";
	_skillName[1] = "Synthesis";
	_skillName[2] = "Leech Seed";
	_skillName[3] = "Razor Leaf";
	_skillDscp[0] = "Basic Attack.";
	_skillDscp[1] = "Restore Health-Point!";
	_skillDscp[2] = "Restore Health-Point & Cause Some Damage!";
	_skillDscp[3] = "Lots Of Damage!!!!!!!!";
	_pp[0] = 5;
	_pp[1] = 10;
	_pp[2] = 5;
}

template <>
bool Race<1>::attack(Pokemon& attacker, Pokemon& aim, int skillIndex) const
{
	dbout << attacker.name() << " uses " << attacker.skillName(skillIndex) << "!\n";

	switch (skillIndex)
	{
	case 1: 
	{
		attacker.changeHp(attacker.catk() / 2 + attacker.cdef() + f(4));
		break;
	}
	case 2: 
	{
		if (dodge(attacker.cspeed(), aim.cspeed()))
			return false;

		int dmg = attacker.catk() + f(4 + attacker.lv());
		if (dmg < 10)
			dmg = 10;
		attacker.changeHp(dmg);
		return aim.takeDamage(dmg);
		break;
	}
	case 3: 
	{
		if (dodge(attacker.cspeed(), aim.cspeed()))
			return false;

		int dmg = attacker.catk() * 2 - aim.cdef() + f(3 + attacker.lv());
		return aim.takeDamage(dmg);

		break;
	}
	default:
	{
		//simple attack
		if (dodge(attacker.cspeed(), aim.cspeed()))
			return false;

		int dmg = attacker.catk() - aim.cdef() + f(4);
		return aim.takeDamage(dmg);

		break;
	}
	} //switch
	return false;
}

template <>
Race<2>::Race() : PokemonBase(DEF)
{
	_raceName = "Squirtle";
	_expCurve[0] = 5;
	for (int i = 1; i < 14; ++i)
	{
		_expCurve[i] = _expCurve[i - 1] + 5 * i;
	}
	_skillName[0] = "Tackle";
	_skillName[1] = "Iron Defense";
	_skillName[2] = "Aqua Tail";
	_skillName[3] = "Hydro Pump";
	_skillDscp[0] = "Basic Attack.";
	_skillDscp[1] = "Increase Your Defence!";
	_skillDscp[2] = "Increase Your Attack & Cause Some Damage!";
	_skillDscp[3] = "Lots Of Damage!!!!!!!!";
	_pp[0] = 10;
	_pp[1] = 10;
	_pp[2] = 3;
}

template <>
bool Race<2>::attack(Pokemon& attacker, Pokemon& aim, int skillIndex) const
{
	dbout << attacker.name() << " uses " << attacker.skillName(skillIndex) << "!\n";

	switch (skillIndex)
	{
	case 1: 
	{
		attacker.changeDef(2);
		break;
	}
	case 2: 
	{
		attacker.changeAtk(2);
		if (dodge(attacker.cspeed(), aim.cspeed()))
			return false;

		int dmg = attacker.catk() - aim.cdef() + f(4 + attacker.lv());
		return aim.takeDamage(dmg);

		break;
	}
	case 3: 
	{
		if (dodge(attacker.cspeed(), aim.cspeed()))
			return false;

		int dmg = attacker.catk() * 2 - aim.cdef() + f(3 + attacker.lv());
		return aim.takeDamage(dmg);

		break;
	}
	default:
	{
		//simple attack
		if (dodge(attacker.cspeed(), aim.cspeed()))
			return false;

		int dmg = attacker.catk() - aim.cdef() + f(4);
		return aim.takeDamage(dmg);

		break;
	}
	} //switch
	return false;
}

template <>
Race<3>::Race() : PokemonBase(SPE)
{
	_raceName = "Pikachu";
	_expCurve[0] = 5;
	for (int i = 1; i < 14; ++i)
	{
		_expCurve[i] = _expCurve[i - 1] + 5 * i;
	}
	_skillName[0] = "Thunder Shock";
	_skillName[1] = "Double Team";
	_skillName[2] = "Discharge";
	_skillName[3] = "Thunderbolt";
	_skillDscp[0] = "Basic Attack.";
	_skillDscp[1] = "Increase Your Speed!";
	_skillDscp[2] = "Cause Some Damage!";
	_skillDscp[3] = "Lots Of Damage!!!!!!!!";
	_pp[0] = 5;
	_pp[1] = 10;
	_pp[2] = 5;
}

template <>
bool Race<3>::attack(Pokemon& attacker, Pokemon& aim, int skillIndex) const
{
	dbout << attacker.name() << " uses " << attacker.skillName(skillIndex) << "!\n";

	switch (skillIndex)
	{
	case 1: 
	{
		attacker.changeSpeed(attacker.speed() / 5);
		break;
	}
	case 2: 
	{
		if (dodge(attacker.cspeed(), aim.cspeed()))
			return false;

		int dmg = attacker.catk() + attacker.cspeed() / 4 - aim.cdef() + f(4 + attacker.lv());
		return aim.takeDamage(dmg);

		break;
	}
	case 3: 
	{
		if (dodge(attacker.cspeed(), aim.cspeed()))
			return false;

		int dmg = attacker.catk() * 2 - aim.cdef() + f(3 + attacker.lv());
		return aim.takeDamage(dmg);

		break;
	}
	default:
	{
		//simple attack
		if (dodge(attacker.cspeed(), aim.cspeed()))
			return false;

		int dmg = attacker.catk() - aim.cdef() + f(4);
		return aim.takeDamage(dmg);

		break;
	}
	} //switch
	return false;
}