#pragma once

#include "cocos2d.h"

#include "Macros.h"

class UserData
{
	static cocos2d::UserDefault* playerData;
public:

	static double getDPS();
	static double getBaseDPS();
	static void setBaseDPS(double DPS);

	static double getDPSMultiplier();
	static void setDPSMultiplier(double mult);
	
	static double getDamage();
	static double getBaseDamage();
	static void setBaseDamage(double dmg);
	
	static double getDamageMultiplier();
	static void setDamageMultiplier(double mult);

	static double getCritChance();
	static void setCritChance(double mult);

	static double getCritDamage();
	static double getCritMultiplier();
	static void setCritMultiplier(double mult);

	static int getWave();
	static void nextWave();

	static void setEnemiesPerWave(int amount);
	static int getEnemiesPerWave();

	static int getEnemyNumber();
	static void setEnemyNumber(int number);

	static void nextRound();
	static int getRoundNumber();

};

