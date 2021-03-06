#include <iostream>
#include "battlecontroller.h"
#include <ctime>

using namespace std;

int main()
{
	srand(time(NULL));
	cout << "Welcome to the WORLD of POKEMON!.\n";
	Race<0> race1;
	Race<1> race2;
	Race<2> race3;
	Race<3> race4;

	Pokemon pokemon1(race3, "pokemon1");
	Pokemon pokemon2(race4, "pokemon2");

	pokemon1.gainExp(1000);
	pokemon2.gainExp(1000);
	BattleController battle(pokemon1, pokemon2, false); //manual fight
	battle.start();
	return 0;
}