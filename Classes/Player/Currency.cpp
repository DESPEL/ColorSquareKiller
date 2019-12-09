#include "Currency.h"

USING_NS_CC;

UserDefault* Currency::userData  = UserDefault::getInstance();

double Currency::getMoney() {
	return userData->getDoubleForKey(MONEY_KEY);
}

void Currency::addMoney(double increase) {
	const double money = getMoney();
	if (money < 0) throw "Cannot add negative money";
	userData->setDoubleForKey(MONEY_KEY, money + increase);
}

bool Currency::takeMoney(double amount) {
	const double money = getMoney();
	if (amount < 0) 
		throw "Cannot take negative money";
	if (!canTakeMoney(amount)) 
		return false;
	userData->setDoubleForKey(MONEY_KEY, money - amount);
	return true;
}

bool Currency::canTakeMoney(double amount) {
	const double money = getMoney();
	if (money - amount < 0) return false;
	return true;
}



double Currency::getGems() {
	return userData->getDoubleForKey(GEMS_KEY);
}

void Currency::addGems(double increase) {
	const double gems = getGems();
	if (gems < 0) throw "Cannot add negative gems";
	userData->setDoubleForKey(GEMS_KEY, gems + increase);
}

bool Currency::takeGems(double amount) {
	const double gems = getGems();
	if (amount < 0)
		throw "Cannot take negative gems";
	if (!canTakeGems(amount))
		return false;
	userData->setDoubleForKey(GEMS_KEY, gems - amount);
	return true;
}

bool Currency::canTakeGems(double amount) {
	const double gems = getGems();
	if (gems - amount < 0) return false;
	return true;
}