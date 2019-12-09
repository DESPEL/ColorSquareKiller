#include "Player/Data.h"

USING_NS_CC;

UserDefault* UserData::playerData = UserDefault::getInstance();

// DPS
double UserData::getDPS() {
	return getBaseDPS() * getDPSMultiplier();
}

double UserData::getBaseDPS() {
	return playerData->getDoubleForKey(BASE_DPS_KEY);
}

void UserData::setBaseDPS(double DPS) {
	playerData->setDoubleForKey(BASE_DPS_KEY, DPS);
}

double UserData::getDPSMultiplier() {
	const double dmgMultiplier = playerData->getDoubleForKey(MULTIPLIER_DPS_KEY);
	if (dmgMultiplier < 1.0)
		setDPSMultiplier(1.0);
	return playerData->getDoubleForKey(MULTIPLIER_DPS_KEY);
}

void UserData::setDPSMultiplier(double mult) {
	playerData->setDoubleForKey(MULTIPLIER_DPS_KEY, mult);
}

// Damage

double UserData::getDamage() {
	return getBaseDamage() * getDamageMultiplier();
}

double UserData::getBaseDamage() {
	double dmg = playerData->getDoubleForKey(BASE_DAMAGE_KEY);
	if (dmg < 1.0)
		setBaseDamage(1.0);
	return playerData->getDoubleForKey(BASE_DAMAGE_KEY);
}

void UserData::setBaseDamage(double dmg) {
	playerData->setDoubleForKey(BASE_DAMAGE_KEY, dmg);
}

double UserData::getDamageMultiplier() {
	double dmgMultiplier = playerData->getDoubleForKey(MULTIPLIER_KEY);
	if (dmgMultiplier < 1.0)
		setDamageMultiplier(1.0);
	return playerData->getDoubleForKey(MULTIPLIER_KEY);
}

void UserData::setDamageMultiplier(double mult) {
	playerData->setDoubleForKey(MULTIPLIER_KEY, mult);
}

// Crit

double UserData::getCritDamage() {
	return getDamage() * getCritMultiplier();
}

double UserData::getCritChance() {
	return playerData->getDoubleForKey(CRIT_CHANCE_KEY);
}

void UserData::setCritChance(double mult) {
	playerData->setDoubleForKey(CRIT_CHANCE_KEY, mult);
}

double UserData::getCritMultiplier() {
	return playerData->getDoubleForKey(CRIT_MULTIPLIER_KEY);
}

void UserData::setCritMultiplier(double mult) {
	playerData->setDoubleForKey(CRIT_MULTIPLIER_KEY ,mult);
}

int UserData::getWave() {
	return playerData->getIntegerForKey(WAVE_KEY);
}

void UserData::nextWave() {
	playerData->setIntegerForKey(WAVE_KEY, getWave() + 1);
}