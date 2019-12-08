#include "Enemy.h"

USING_NS_CC;

Enemy* Enemy::create(int hp) {
	Enemy* enemy = Enemy::create();
	enemy->initWithFile("white.png");
	enemy->setContentSize(Size(500, 500));
	GLubyte r = cocos2d::RandomHelper::random_int(0, 255);
	GLubyte g = cocos2d::RandomHelper::random_int(0, 255);
	GLubyte b = cocos2d::RandomHelper::random_int(0, 255);
	enemy->setColor({ r, g, b });
	log("enemy created");
	enemy->maxHP = hp;
	enemy->hp = hp;
	return enemy;
}

bool Enemy::init() {
	return true;
}