#include "MainScene.h"

USING_NS_CC;
using namespace gsl;

Scene* MainScene::createScene() {
	return MainScene::create();
}

bool MainScene::init() {
	if (!Scene::init())
		return false;

	const Vec2 origin = Director::getInstance()->getVisibleOrigin();
	const Size visibleSize = Director::getInstance()->getVisibleSize();

	const not_null<Label*> label = Label::createWithSystemFont("Main Scene", "Arial", 80);
	label->setPosition(visibleSize / 2);
	this->addChild(label);

	const not_null<Sprite*> background = Sprite::create();
	background->initWithFile("images/background1.jpg");
	background->setAnchorPoint({ 0.5f, 0.5f });
	background->setPosition(visibleSize / 2);
	background->setZOrder(std::numeric_limits<int32_t>::min());
	background->setOpacity(static_cast<GLubyte>(150));
	
	this->addChild(background);


	// create gui buttons
	createShopButton();
	createUpgradesButton();
	createBoostersButton();
	createDeleteDataButton();

	// labels
	hpLabel = Label::createWithSystemFont("hp: xxx", "Arial", 48);
	hpLabel->setAnchorPoint({ 0.5f, 0.5f });
	hpLabel->setPosition(visibleSize.width / 2, 100);
	this->addChild(hpLabel);

	moneyLabel = Label::createWithSystemFont("Gold: xxxx", "Arial", 48);
	moneyLabel->setAnchorPoint({ 0.0f, 0.5f });
	moneyLabel->setPosition({ 50, visibleSize.height - 250 });
	this->addChild(moneyLabel);

	gemsLabel = Label::createWithSystemFont("Gems: xxxx", "Arial", 48);
	gemsLabel->setAnchorPoint({ 0.0f, 0.5f });
	gemsLabel->setPosition({ 50, visibleSize.height - 350 });
	this->addChild(gemsLabel);

	dpsLabel = Label::createWithSystemFont("DPS: xxxx", "Arial", 48);
	dpsLabel->setAnchorPoint({ 0.0f, 0.5f });
	dpsLabel->setPosition({ 50, visibleSize.height - 450 });
	this->addChild(dpsLabel);

	damageLabel = Label::createWithSystemFont("DPC: xxxx", "Arial", 48);
	damageLabel->setAnchorPoint({ 0.0f, 0.5f });
	damageLabel->setPosition({ 50, visibleSize.height - 550 });
	this->addChild(damageLabel);

	waveLabel = Label::createWithSystemFont("wave: xxxx", "Arial", 48);
	waveLabel->setAnchorPoint({ 0.0f, 0.5f });
	waveLabel->setPosition({ 100 + 300 * 3 + 25 * 3 , visibleSize.height - 100 });
	this->addChild(waveLabel);

	// test enemy
	addEnemy();

	this->hpBar = ui::LoadingBar::create("hpbarfill.png");
	const not_null<Sprite*> hpborder = Sprite::create();
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

void MainScene::enemyBounty() {
	// idk but ok
	Currency::addMoney(pow(1.0125,UserData::getWave()));
}

void MainScene::attackEnemy(double dmg) {
	if (dmg < 0)
		throw "Cannot take negative damage";
	this->enemy->hp -= dmg;
	if (this->enemy->hp <= 0) {
		enemyBounty();
		UserData::nextWave();
		this->enemy->removeFromParentAndCleanup(true);
		this->addEnemy();
	}
}


void MainScene::addEnemy() {
	const Size visibleSize = Director::getInstance()->getVisibleSize();

	this->enemy = Enemy::create(static_cast<double>(ENEMY_BASE_HP) *pow(1.013, UserData::getWave()));
	this->enemy->setPosition(visibleSize / 2);
	this->addChild(this->enemy);
	const auto listener = EventListenerTouchOneByOne::create();
	listener->setSwallowTouches(true);

	listener->onTouchBegan = [&](Touch* touch, Event* event) {
		const Vec2 position = touch->getLocation();
		const Rect hitbox = this->enemy->getBoundingBox();

		if (hitbox.containsPoint(position)) {
			attackEnemy(UserData::getDamage());
			log("enemy touched");
			return true;
		}

		return false;
	};

	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this->enemy);
}

void MainScene::update(float delta) {

	// attack enemy (dps)
	attackEnemy(UserData::getDPS() * delta);

	// update hp;
	std::string newHp = "hp: " + std::to_string((int)this->enemy->hp) + 
						"/" + std::to_string((int)this->enemy->maxHP);

	hpBar->setPercent(this->enemy->hp / this->enemy->maxHP * 100);
	this->hpLabel->setString(newHp);

	// update money and gems
	this->moneyLabel->setString("Gold: " + std::to_string(Currency::getMoney()));
	this->gemsLabel->setString("Gems: " + std::to_string(Currency::getGems()));

	// update dps and dpc
	this->dpsLabel->setString("DPS: " + std::to_string(UserData::getDPS()));
	this->damageLabel->setString("DPC: " + std::to_string(UserData::getDamage()));

	// udate wave
	this->waveLabel->setString("Wave: " + std::to_string(UserData::getWave()));
	this->waveLabel->setString("Enemy: " + std::to_string(UserData::getEnemyNumber()) +
		"/" + std::to_string(UserData::getEnemiesPerWave()) +
		" Round:" + std::to_string(UserData::getRoundNumber()));
}


void MainScene::createDeleteDataButton() {
	const Size visibleSize = Director::getInstance()->getVisibleSize();

	not_null<ui::Button*> shopbtn = ui::Button::create();

	shopbtn->loadTextures(
		"buttons/red_button00.png",
		"buttons/red_button01.png"
	);
	shopbtn->setTitleText("Erase data");
	shopbtn->setTitleFontName("arial");

	shopbtn->setTitleFontSize(44.0f);
	Utils::resizeButton(shopbtn, { 300, 100 });
	const auto touch_handler = [&](Ref* ref, ui::Widget::TouchEventType evt)
	{
		if (evt == cocos2d::ui::Widget::TouchEventType::ENDED)
		{
			attackEnemy(1E50);
			log("data cleared");
			UserDefault::getInstance()->deleteValueForKey(MONEY_KEY);
			UserDefault::getInstance()->deleteValueForKey(GEMS_KEY);
			UserDefault::getInstance()->deleteValueForKey(BASE_DAMAGE_KEY);
			UserDefault::getInstance()->deleteValueForKey(MULTIPLIER_KEY);
			UserDefault::getInstance()->deleteValueForKey(CRIT_CHANCE_KEY);
			UserDefault::getInstance()->deleteValueForKey(CRIT_MULTIPLIER_KEY);
			UserDefault::getInstance()->deleteValueForKey(BASE_DPS_KEY);
			UserDefault::getInstance()->deleteValueForKey(MULTIPLIER_DPS_KEY);
			UserDefault::getInstance()->deleteValueForKey(ROUND_KEY);
			UserDefault::getInstance()->deleteValueForKey(ENEMY_KEY);
			UserDefault::getInstance()->deleteValueForKey(WAVE_KEY);
			UserDefault::getInstance()->deleteValueForKey(NUM_ENEMIES_KEY);
		}
	};
	shopbtn->addTouchEventListener(touch_handler);
	shopbtn->setAnchorPoint(Vec2(0.0f, 1.0f));
	shopbtn->setPosition({ visibleSize.width - 325, visibleSize.height - 50 });
	this->addChild(shopbtn);
}

void MainScene::createBoostersButton() {
	const Size visibleSize = Director::getInstance()->getVisibleSize();

	const not_null<ui::Button*> upgradebtn = ui::Button::create();

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
	const Size visibleSize = Director::getInstance()->getVisibleSize();

	const not_null<ui::Button*> upgradebtn = ui::Button::create();

	upgradebtn->loadTextures(
		"buttons/green_button00.png",
		"buttons/green_button01.png"
	);
	upgradebtn->setTitleText("Upgrades");
	upgradebtn->setTitleFontName("arial");

	upgradebtn->setTitleFontSize(44.0f);
	Utils::resizeButton(upgradebtn, { 300, 100 });
	const auto touch_handler = [&](Ref* ref, ui::Widget::TouchEventType evt)
	{
		if (evt == ui::Widget::TouchEventType::ENDED)
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
	const Size visibleSize = Director::getInstance()->getVisibleSize();

	const not_null<ui::Button*> shopbtn = ui::Button::create();

	shopbtn->loadTextures(
		"buttons/green_button00.png",
		"buttons/green_button01.png"
	);
	shopbtn->setTitleText("Shop");
	shopbtn->setTitleFontName("arial");

	shopbtn->setTitleFontSize(44.0f);
	Utils::resizeButton(shopbtn, { 300, 100 });
	const auto touch_handler = [&](Ref* ref, ui::Widget::TouchEventType evt)
	{
		if (evt == ui::Widget::TouchEventType::ENDED)
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