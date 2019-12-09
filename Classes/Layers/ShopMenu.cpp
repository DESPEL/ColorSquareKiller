#include "ShopMenu.h"

USING_NS_CC;

ShopMenu::ShopMenu() {

}

ShopMenu::~ShopMenu() {

}

bool ShopMenu::init() {
	Size visibleSize = Director::getInstance()->getVisibleSize();

	if (!Layer::init())
		return false;
	// prevent clicks on lower layers (main menu)
	auto listener = EventListenerTouchOneByOne::create();
	listener->setSwallowTouches(true);
	listener->onTouchBegan = [](Touch* touch, Event* event)->bool { return true; };
	this->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, this);
	
	// make bg darker
	auto bg = cocos2d::LayerColor::create(Color4B(0, 0, 0, 125));
	this->addChild(bg);
	
	// close store btn
	ui::Button* closebtn = ui::Button::create();

	closebtn->loadTextures(
		"buttons/green_boxCross.png",
		"buttons/green_boxCross.png"
	);

	auto touch_handler = [&](cocos2d::Ref* ref, cocos2d::ui::Widget::TouchEventType evt)
	{
		if (evt == cocos2d::ui::Widget::TouchEventType::ENDED) {
			cocos2d::log("shop closed");
			this->close();
		}
	};
	Utils::resizeButton(closebtn, { 75, 75 });
	closebtn->addTouchEventListener(touch_handler);
	closebtn->setPosition({ 
		/*x=*/visibleSize.width - 100, 
		/*y=*/visibleSize.height - 100 });
	this->addChild(closebtn);
	
	
	// end
	ui::Button* upgradebtn = ui::Button::create();

	upgradebtn->loadTextures(
		"buttons/yellow_button00.png",
		"buttons/yellow_button01.png"
	);
	upgradebtn->setTitleText("Buy 1dps for Gold: 10");
	upgradebtn->setTitleFontName("arial");

	upgradebtn->setTitleFontSize(44.0f);
	Utils::resizeButton(upgradebtn, { 500, 100 });
	const auto buy_handler = [&](cocos2d::Ref* ref, cocos2d::ui::Widget::TouchEventType evt)
	{
		if (evt == cocos2d::ui::Widget::TouchEventType::ENDED)
		{
			if (Currency::canTakeMoney(10)) {
				Currency::takeMoney(10);
				UserData::setBaseDPS(UserData::getBaseDPS() + 1);
			}
		}
	};
	upgradebtn->addTouchEventListener(buy_handler);
	upgradebtn->setAnchorPoint(Vec2(0.0f, 1.0f));
	upgradebtn->setPosition({ 50 , visibleSize.height - 150 });
	this->addChild(upgradebtn);


	// buy dpc
	ui::Button* dpcbtn = ui::Button::create();

	dpcbtn->loadTextures(
		"buttons/yellow_button00.png",
		"buttons/yellow_button01.png"
	);
	dpcbtn->setTitleText("Buy 1dpc for Gold: 10");
	dpcbtn->setTitleFontName("arial");

	dpcbtn->setTitleFontSize(44.0f);
	Utils::resizeButton(dpcbtn, { 500, 100 });
	const auto buy_handler2 = [&](cocos2d::Ref* ref, cocos2d::ui::Widget::TouchEventType evt)
	{
		if (evt == cocos2d::ui::Widget::TouchEventType::ENDED)
		{
			if (Currency::canTakeMoney(10)) {
				Currency::takeMoney(10);
				UserData::setBaseDamage(UserData::getBaseDamage() + 1);
			}
		}
	};
	dpcbtn->addTouchEventListener(buy_handler2);
	dpcbtn->setAnchorPoint(Vec2(0.0f, 1.0f));
	dpcbtn->setPosition({ 50 , visibleSize.height - 350 });
	this->addChild(dpcbtn);
	
	return true;
}

void ShopMenu::close(Ref* sender)
{
	this->removeFromParentAndCleanup(true);
}