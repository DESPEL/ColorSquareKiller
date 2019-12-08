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

	
	return true;
}

void ShopMenu::close(Ref* sender)
{
	this->removeFromParentAndCleanup(true);
}