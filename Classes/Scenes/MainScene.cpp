#include "MainScene.h"

USING_NS_CC;

Scene* MainScene::createScene() {
	return MainScene::create();
}

bool MainScene::init() {
	if (!Scene::init())
		return false;

	Vec2 origin = Director::getInstance()->getVisibleOrigin();
	auto visibleSize = Director::getInstance()->getVisibleSize();

	auto label = Label::createWithSystemFont("Main Scene", "Arial", 80);
	label->setPosition(visibleSize / 2);
	this->addChild(label);

	auto background = Sprite::create();
	background->initWithFile("images/background1.jpg");
	background->setAnchorPoint({ 0.5f, 0.5f });
	background->setPosition(visibleSize / 2);
	background->setZOrder(std::numeric_limits<int32_t>::min());
	background->setOpacity(GLubyte(150));
	
	this->addChild(background);


	// create gui buttons
	createShopButton();
	createUpgradesButton();
	createBoostersButton();

	// labels
	hpLabel = Label::createWithSystemFont("hp: xxx", "Arial", 48);
	hpLabel->setAnchorPoint({ 0.5f, 0.5f });
	hpLabel->setPosition(visibleSize.width / 2, 100);
	this->addChild(hpLabel);

	// test enemy
	addEnemy();

	this->hpBar = ui::LoadingBar::create("hpbarfill.png");
	auto hpborder = Sprite::create();
	hpborder->initWithFile("hpbarborder.png");
	hpborder->setAnchorPoint({ 0.0f, 0.0f });
	hpBar->addChild(hpborder);

	// set the direction of the loading bars progress
	hpBar->setDirection(ui::LoadingBar::Direction::LEFT);
	hpBar->setPercent(100);
	hpBar->setPosition({ visibleSize.width / 2, 200 });
	this->addChild(hpBar);


	// update
	this->schedule(schedule_selector(MainScene::update));
}

void MainScene::addEnemy() {
	auto visibleSize = Director::getInstance()->getVisibleSize();

	this->enemy = Enemy::create(20);
	this->enemy->setPosition(visibleSize / 2);
	this->addChild(this->enemy);
	auto listener = EventListenerTouchOneByOne::create();
	listener->setSwallowTouches(true);

	listener->onTouchBegan = [&](Touch* touch, Event* event) {
		cocos2d::Vec2 position = touch->getLocation();
		cocos2d::Rect hitbox = this->enemy->getBoundingBox();

		if (hitbox.containsPoint(position)) {
			this->enemy->hp--;
			if (this->enemy->hp <= 0) {
				this->enemy->removeFromParentAndCleanup(true);
				this->addEnemy();
			}
			log("enemy touched");
			return true;
		}

		return false;
	};

	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this->enemy);
}

void MainScene::update(float delta) {
	// update hp;
	std::string newHp = "hp: " + std::to_string(this->enemy->hp) + 
						"/" + std::to_string(this->enemy->maxHP);

	hpBar->setPercent(this->enemy->hp / (float)this->enemy->maxHP * 100);
	this->hpLabel->setString(newHp);
}

void MainScene::createBoostersButton() {
	auto visibleSize = Director::getInstance()->getVisibleSize();

	ui::Button* upgradebtn = ui::Button::create();

	upgradebtn->loadTextures(
		"buttons/green_button00.png",
		"buttons/green_button01.png"
	);
	upgradebtn->setTitleText("Boosters");
	upgradebtn->setTitleFontName("arial");

	upgradebtn->setTitleFontSize(44.0f);
	Utils::resizeButton(upgradebtn, { 300, 100 });
	const auto touch_handler = [&](cocos2d::Ref* ref, cocos2d::ui::Widget::TouchEventType evt)
	{
		if (evt == cocos2d::ui::Widget::TouchEventType::ENDED)
		{
			log("boosters opened");
			this->addChild(BoostersMenu::create());
		}
	};
	upgradebtn->addTouchEventListener(touch_handler);
	upgradebtn->setAnchorPoint(Vec2(0.0f, 1.0f));
	upgradebtn->setPosition({ 50 + 300 * 2 + 25 * 2 , visibleSize.height - 50 });
	this->addChild(upgradebtn);
}

void MainScene::createUpgradesButton() {
	auto visibleSize = Director::getInstance()->getVisibleSize();

	ui::Button* upgradebtn = ui::Button::create();

	upgradebtn->loadTextures(
		"buttons/green_button00.png",
		"buttons/green_button01.png"
	);
	upgradebtn->setTitleText("Upgrades");
	upgradebtn->setTitleFontName("arial");

	upgradebtn->setTitleFontSize(44.0f);
	Utils::resizeButton(upgradebtn, { 300, 100 });
	const auto touch_handler = [&](cocos2d::Ref* ref, cocos2d::ui::Widget::TouchEventType evt)
	{
		if (evt == cocos2d::ui::Widget::TouchEventType::ENDED)
		{
			log("upgrades opened");
			this->addChild(UpgradesMenu::create());
		}
	};
	upgradebtn->addTouchEventListener(touch_handler);
	upgradebtn->setAnchorPoint(Vec2(0.0f, 1.0f));
	upgradebtn->setPosition({ 50 + 300 * 1 + 25 * 1, visibleSize.height - 50});
	this->addChild(upgradebtn);
}

void MainScene::createShopButton() {
	auto visibleSize = Director::getInstance()->getVisibleSize();

	ui::Button* shopbtn = ui::Button::create();

	shopbtn->loadTextures(
		"buttons/green_button00.png",
		"buttons/green_button01.png"
	);
	shopbtn->setTitleText("Shop");
	shopbtn->setTitleFontName("arial");

	shopbtn->setTitleFontSize(44.0f);
	Utils::resizeButton(shopbtn, { 300, 100 });
	const auto touch_handler = [&](cocos2d::Ref* ref, cocos2d::ui::Widget::TouchEventType evt)
	{
		if (evt == cocos2d::ui::Widget::TouchEventType::ENDED)
		{
			log("shop opened");
			this->addChild(ShopMenu::create());
		}
	};
	shopbtn->addTouchEventListener(touch_handler);
	shopbtn->setAnchorPoint(Vec2(0.0f, 1.0f));
	shopbtn->setPosition({ 50, visibleSize.height - 50 });
	this->addChild(shopbtn);
}