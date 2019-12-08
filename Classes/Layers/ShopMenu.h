#pragma once

#include "cocos2d.h"

#include "Utils.h"
#include "ui/CocosGUI.h"

class ShopMenu : public cocos2d::Layer
{
public:
	ShopMenu();
	~ShopMenu();

	bool init();

	CREATE_FUNC(ShopMenu);

	void close(cocos2d::Ref* sender = nullptr);
};
