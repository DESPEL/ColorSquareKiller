#pragma once

#include "cocos2d.h"

#include "utils.h"
#include "ui/CocosGUI.h"

class BoostersMenu : public cocos2d::Layer
{
public:
	BoostersMenu();
	~BoostersMenu();

	bool init();

	CREATE_FUNC(BoostersMenu);

	void close(cocos2d::Ref* sender = nullptr);
};

