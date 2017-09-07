#include "GameControl.h"
#include "HeroPlaneSprite.h"
#include "GameScene.h"
#include "HelloWorldScene.h"
#include <string>
#include "stage.h"
#include "GameScene2.h"
#include "GameScene3.h"
#include "SimpleAudioEngine.h"
#include "Scene1.h"
using namespace cocos2d;
using namespace CocosDenshion;
bool GameControl::init() {
	if (!Layer::init()) {
		return false;
	}
	auto visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	//血条
	auto life = Sprite::create("Hp2.png");
	life->setPosition(Vec2(origin.x, origin.y + visibleSize.height));
	life->setAnchorPoint(Vec2(0, 1));
	this->addChild(life, 0);

	this->life_bar = ProgressTimer::create(Sprite::create("Hp1.png"));
	this->life_bar->setType(ProgressTimerType::BAR);
	this->life_bar->setPosition(Vec2(origin.x, origin.y + visibleSize.height));
	this->life_bar->setAnchorPoint(Vec2(0, 1));
	this->life_bar->setMidpoint(Vec2(0, 0));//？？？
	this->life_bar->setBarChangeRate(Vec2(1, 0));//？？？
	this->life_bar->setPercentage(100);
	this->addChild(life_bar, 1);

	//暂停
	this->item_pause = MenuItemSprite::create(Sprite::create("pause.png"), Sprite::create("pause.png"), CC_CALLBACK_1(GameControl::pauseMenuCallback, this));
	this->menu_pause = Menu::createWithItem(item_pause);
	this->addChild(menu_pause, 1);
	this->menu_pause->setPosition(visibleSize.width + 66, visibleSize.height - this->item_pause->getContentSize().height / 2);

	//分数
	auto score1 = Label::createWithTTF("Score:", "plantc.ttf", 13);
	this->addChild(score1, 1);
	score1->setAnchorPoint(Vec2(0, 1));
	score1->setPosition(Director::getInstance()->getWinSize().width / 2, Director::getInstance()->getWinSize().height);

	this->score2 = Label::createWithTTF("0", "plantc.ttf", 13);
	this->addChild(score2, 1);
	this->score2->setAnchorPoint(Vec2(0, 1));
	this->score2->setPosition(Director::getInstance()->getWinSize().width / 2 + 40, Director::getInstance()->getWinSize().height);
	//更新

	schedule(schedule_selector(GameControl::gameOver), 0.1);
	schedule(schedule_selector(GameControl::passMenu), 3);
	scheduleUpdate();
	return true;
}

void GameControl::update(float dt) {
	int hp = stage::Hp;
	//ProgressTo *p_progress = ProgressTo::create(2.0f, hp/100);
	//this->life_bar->runAction(p_progress);
	this->life_bar->setPercentage(hp);


	score2->setString(std::to_string(stage::score));

}

void GameControl::resumeMenuCallback(Ref *r) {
	Director::getInstance()->resume();
	item_pause->setVisible(true);
	item_pause->setEnabled(true);
	this->removeChildByTag(10);
}

void GameControl::restartMenuCallback(Ref *r) {
	if (stage::stageNumber == 1) {
		stage::score = 0;
		stage::Hp = 100;
		stage::BossHp = 2000;
		stage::x = 0;
		stage::s = 0;
		Director::getInstance()->replaceScene(GameScene::createScene());
		Director::getInstance()->resume();
	}
	if (stage::stageNumber == 2) {
		stage::score = 0;
		stage::Hp = 100;
		stage::BossHp = 2000;
		stage::x = 0;
		stage::s = 0;
		Director::getInstance()->replaceScene(GameScene2::createScene());
		Director::getInstance()->resume();
	}
	if (stage::stageNumber == 3) {
		stage::score = 0;
		stage::Hp = 100;
		stage::BossHp = 2000;
		stage::x = 0;
		stage::s = 0;
		Director::getInstance()->replaceScene(GameScene3::createScene());
		Director::getInstance()->resume();
	}

}

void GameControl::backMenuCallback(Ref *) {
	stage::stageNumber = 1;
	stage::score = 0;
	stage::Hp = 100;
	stage::BossHp = 2000;
	stage::x = 0;
	stage::s = 0;
	Director::getInstance()->replaceScene(Scene1::scene());
	Director::getInstance()->resume();
}

void GameControl::nextMenuCallback(Ref *) {
	if (stage::stageNumber == 1) {
		SimpleAudioEngine::sharedEngine()->stopBackgroundMusic();//停止背景音乐，这是一个缺省参数函数，传参表示是否释放音乐文件 
		stage::stageNumber = 2;
		stage::score = 0;
		stage::Hp = 100;
		stage::BossHp = 2000;
		stage::x = 0;
		stage::s = 0;
		Director::getInstance()->replaceScene(GameScene2::createScene());
		Director::getInstance()->resume();
	}
	else  {
		SimpleAudioEngine::sharedEngine()->stopBackgroundMusic();//停止背景音乐，这是一个缺省参数函数，传参表示是否释放音乐文件 
		stage::stageNumber = 3;
		stage::score = 0;
		stage::Hp = 100;
		stage::BossHp = 2000;
		stage::x = 0;
		stage::s = 0;
		Director::getInstance()->replaceScene(GameScene3::createScene());
		Director::getInstance()->resume();
	}
}
void GameControl::pauseMenuCallback(Ref *r) {
	Director::getInstance()->pause();

	auto layer = Layer::create();
	this->addChild(layer);
	layer->setTag(10);

	//背景
	auto p_bg = Sprite::create("pausebg.png");
	p_bg->setPosition(Vec2(Director::getInstance()->getWinSize().width / 2, Director::getInstance()->getWinSize().height / 2));
	layer->addChild(p_bg, 0);
	//继续
	this->item_resume = MenuItemSprite::create(Sprite::create("resume.png"), Sprite::create("resume.png"), CC_CALLBACK_1(GameControl::resumeMenuCallback, this));
	this->menu_resume = Menu::createWithItem(item_resume);
	layer->addChild(menu_resume, 1);
	menu_resume->setPosition(Vec2(Director::getInstance()->getWinSize().width / 2 - 20, Director::getInstance()->getWinSize().height / 2));
	//重新开始
	this->item_restart = MenuItemSprite::create(Sprite::create("restart.png"), Sprite::create("restart.png"), CC_CALLBACK_1(GameControl::restartMenuCallback, this));
	this->menu_restart = Menu::createWithItem(item_restart);
	layer->addChild(menu_restart, 1);
	menu_restart->setPosition(Vec2(Director::getInstance()->getWinSize().width / 2 + 2, Director::getInstance()->getWinSize().height / 2));
	//返回主菜单
	this->item_back = MenuItemSprite::create(Sprite::create("back.png"), Sprite::create("back.png"), CC_CALLBACK_1(GameControl::backMenuCallback, this));
	this->menu_back = Menu::createWithItem(item_back);
	layer->addChild(menu_back, 1);
	menu_back->setPosition(Vec2(Director::getInstance()->getWinSize().width / 2 + 24, Director::getInstance()->getWinSize().height / 2));

	item_pause->setEnabled(false);
	item_pause->setVisible(false);
}
void GameControl::passMenu(float dt) {
	if (stage::score >= 10000) {
		auto passlayer = Layer::create();
		this->addChild(passlayer);
		passlayer->setTag(20);

		auto passbg = Sprite::create("passbg.png");
		passlayer->addChild(passbg);
		passbg->setPosition(Vec2(Director::getInstance()->getWinSize().width / 2, Director::getInstance()->getWinSize().height / 2));

		//ÏÂÒ»¹Ø
		this->item_next = MenuItemSprite::create(Sprite::create("next.png"), Sprite::create("next.png"), CC_CALLBACK_1(GameControl::nextMenuCallback, this));
		this->menu_next = Menu::createWithItem(item_next);
		passlayer->addChild(menu_next, 1);
		menu_next->setPosition(Vec2(Director::getInstance()->getWinSize().width / 2 - 5, Director::getInstance()->getWinSize().height / 2 + 5));

		//·µ»ØÖ÷²Ëµ¥
		this->item_back2 = MenuItemSprite::create(Sprite::create("back2.png"), Sprite::create("back2.png"), CC_CALLBACK_1(GameControl::backMenuCallback, this));
		this->menu_back2 = Menu::createWithItem(item_back2);
		passlayer->addChild(menu_back2, 1);
		menu_back2->setPosition(Vec2(Director::getInstance()->getWinSize().width / 2 - 5, Director::getInstance()->getWinSize().height / 2 - 20));
		this->item_pause->setVisible(false);
		this->item_pause->setEnabled(false);
	}
}
void GameControl::gameOver(float dt) {
	if (stage::Hp <= 0) {
		auto gameover = Layer::create();
		this->addChild(gameover);

		auto gameoverbg = Sprite::create("gameover.png");
		gameover->addChild(gameoverbg);
		gameoverbg->setPosition(Vec2(Director::getInstance()->getWinSize().width / 2, Director::getInstance()->getWinSize().height / 2));

		this->item_restart2 = MenuItemSprite::create(Sprite::create("restart2.png"), Sprite::create("restart2.png"), CC_CALLBACK_1(GameControl::restartMenuCallback, this));
		this->menu_restart2 = Menu::createWithItem(item_restart2);
		gameover->addChild(menu_restart2, 1);
		menu_restart2->setPosition(Vec2(Director::getInstance()->getWinSize().width / 2, Director::getInstance()->getWinSize().height / 2));

		this->item_back3 = MenuItemSprite::create(Sprite::create("back3.png"), Sprite::create("back3.png"), CC_CALLBACK_1(GameControl::backMenuCallback, this));
		this->menu_back3 = Menu::createWithItem(item_back3);
		gameover->addChild(menu_back3, 1);
		menu_back3->setPosition(Vec2(Director::getInstance()->getWinSize().width / 2, Director::getInstance()->getWinSize().height / 2 - 30));
		this->item_pause->setVisible(false);
		this->item_pause->setEnabled(false);
		unschedule(schedule_selector(GameControl::gameOver));
	}
}
