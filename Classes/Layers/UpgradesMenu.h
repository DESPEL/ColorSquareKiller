#pragma once

#include "Utils.h"
#include "ui/CocosGUI.h"

class UpgradesMenu : public cocos2d::Layer
{
public:
	UpgradesMenu();
	~UpgradesMenu();

	bool init();

	CREATE_FUNC(UpgradesMenu);

	void close(cocos2d::Ref* sender = nullptr);
};

