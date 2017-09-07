#include "SimpleAudioEngine.h"
#include "HelloWorldScene.h"
#include "stage.h"
#include "GameScene.h"
#include "GameScene2.h"
#include "GameScene3.h"
#include "Scene1.h"


USING_NS_CC;
using namespace CocosDenshion;

Scene* HelloWorld::createScene()
{
	return HelloWorld::create();
}

// on "init" you need to initialize your instance
bool HelloWorld::init()
{
	//////////////////////////////
	// 1. super init first
	if (!Scene::init())
	{
		return false;
	}

	auto visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	auto Bgm1 = SimpleAudioEngine::getInstance();
	Bgm1->preloadBackgroundMusic("bgMusic1.wav");
	Bgm1->playBackgroundMusic("bgMusic1.wav", true);
	Bgm1->setBackgroundMusicVolume(0.5);
	
	LabelTTF* label = LabelTTF::create("click anywhere to start", "Comic Sans MS", 15);
	label->setPosition(Director::getInstance()->getWinSize().width / 2, Director::getInstance()->getWinSize().height / 5);
	addChild(label, 2);
	FadeTo* fadeto88 = FadeTo::create(1, 88);
	FadeTo* fadeto255 = FadeTo::create(2, 255);
	ActionInterval* fadeaction = Sequence::create(fadeto88, fadeto255, NULL);
	label->runAction(RepeatForever::create(fadeaction));

	auto sprite_2 = Sprite::create("title_1.png");
	sprite_2->setPosition(Vec2(Director::getInstance()->getWinSize().width / 2, Director::getInstance()->getWinSize().height / 3 * 2));
	this->addChild(sprite_2, 2);

	auto nodegrid = NodeGrid::create();
	auto sprite_1 = Sprite::create("galaxy_1.jpg");
	nodegrid->setPosition(Vec2(Director::getInstance()->getWinSize().width / 2, +Director::getInstance()->getWinSize().height / 2));
	nodegrid->addChild(sprite_1, 2);
	this->addChild(nodegrid);
	Director::getInstance()->setDepthTest(false);
	ActionInterval* rotate = RotateBy::create(200, 360);
	nodegrid->runAction(RepeatForever::create(rotate));


	auto startItem = MenuItemImage::create("blank.png", "blank.png", CC_CALLBACK_1(HelloWorld::menuNextScene, this));
	startItem->setPosition(Vec2(Director::getInstance()->getWinSize().width / 2, Director::getInstance()->getWinSize().height / 2));

	// 将菜单项添加到精灵里面
	auto menu = Menu::create(startItem, NULL);
	// 将菜单加入当前层
	menu->setPosition(Vec2::ZERO);
	this->addChild(menu, 1);

	

	return true;
}

void HelloWorld::menuNextScene(Ref*) {
	auto next = Scene1::scene();
	auto scene = TransitionCrossFade::create(1.0f, next);
	Director::getInstance()->replaceScene(scene);
}

