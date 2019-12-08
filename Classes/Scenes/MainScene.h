#pragma once

#include "cocos2d.h"

#include "ui/CocosGUI.h"

#include "Utils.h"

// gui
#include "Layers/ShopMenu.h"
#include "Layers/UpgradesMenu.h"
#include "Layers/BoostersMenu.h"

// data

// others
#include "Enemy.h"

class MainScene : public cocos2d::Scene
{
	void createShopButton();
	void createUpgradesButton();
	void createBoostersButton();

	void addEnemy();

	Enemy* enemy = nullptr;

	cocos2d::Label* hpLabel;

public:
	static cocos2d::Scene* createScene();
	virtual bool init();

	CREATE_FUNC(MainScene);

	void update(float delta) override;
};

