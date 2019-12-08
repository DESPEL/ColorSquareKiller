#pragma once

#include "cocos2d.h"

class Enemy : public cocos2d::Sprite
{
public:
	int hp;
	int maxHP;

	bool init();
	// TODO: Enemy with sprite file and other things

	// random square enemy
	static Enemy* create(int hp);
	CREATE_FUNC(Enemy);

	~Enemy() {
		cocos2d::log("enemy deleted");
	}
};

