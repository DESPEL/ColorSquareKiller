#pragma once

#include "cocos2d.h"

#include "Macros.h"

class Currency
{
	static cocos2d::UserDefault* userData;
	Currency();
public:

	static double getMoney();
	static void addMoney(double increase);
	static bool takeMoney(double amount);
	static bool canTakeMoney(double amount);

	static double getGems();
	static void addGems(double increase);
	static bool takeGems(double amount);
	static bool canTakeGems(double amount);
};

