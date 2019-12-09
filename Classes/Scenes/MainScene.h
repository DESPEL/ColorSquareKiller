#pragma once

#include "cocos2d.h"

#include "ui/CocosGUI.h"

#include "Utils.h"

// gui
#include "Layers/ShopMenu.h"
#include "Layers/UpgradesMenu.h"
#include "Layers/BoostersMenu.h"

#include "Player/Currency.h"
#include "Player/Data.h"

// others
#include "Enemy.h"
#include "Macros.h"

class MainScene : public cocos2d::Scene
{
	void createShopButton();
	void createUpgradesButton();
	void createBoostersButton();
	void createDeleteDataButton();

	void attackEnemy(double dmg);
	void addEnemy();
	void enemyBounty();

	Enemy* enemy = nullptr;
	cocos2d::ui::LoadingBar* hpBar = nullptr;

	cocos2d::Label* waveLabel;
	cocos2d::Label* hpLabel;

	cocos2d::Label* moneyLabel;
	cocos2d::Label* gemsLabel;

	cocos2d::Label* dpsLabel;
	cocos2d::Label* damageLabel;

public:
	static cocos2d::Scene* createScene();
	virtual bool init();

	CREATE_FUNC(MainScene);

	void update(float delta) override;
};

