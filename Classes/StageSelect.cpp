#include "StageSelect.h"
#include "GameScene.h"
#include "GameScene2.h"
#include "GameScene3.h"
#include "Scene1.h"
#include "stage.h"

USING_NS_CC;

Scene* StageSelect::createScene()
{
	auto scene = Scene::create();
	auto layer = StageSelect::create();
	scene->addChild(layer);
	return scene;
}

bool StageSelect::init() {
	if (!Scene::init())
	{
		return false;
	}


	auto choosebg = Sprite::create("choosebg.png");
	this->addChild(choosebg, 0);
	choosebg->setPosition(Director::getInstance()->getWinSize().width / 2, Director::getInstance()->getWinSize().height / 2);

	auto stage1 = MenuItemImage::create("stage1.png", "stage1.png", CC_CALLBACK_1(StageSelect::GoToStage1, this));
	stage1->setPosition(Vec2(Director::getInstance()->getWinSize().width / 2, Director::getInstance()->getWinSize().height / 2 + 80));

	auto stage2 = MenuItemImage::create("stage2.png", "stage2.png", CC_CALLBACK_1(StageSelect::GoToStage2, this));
	stage2->setPosition(Vec2(Director::getInstance()->getWinSize().width / 2, Director::getInstance()->getWinSize().height / 2));

	auto stage3 = MenuItemImage::create("stage3.png", "stage3.png", CC_CALLBACK_1(StageSelect::GoToStage3, this));
	stage3->setPosition(Vec2(Director::getInstance()->getWinSize().width / 2, Director::getInstance()->getWinSize().height / 2 - 80));

	auto back = MenuItemImage::create("backx.png", "backx.png", CC_CALLBACK_1(StageSelect::back, this));
	back->setPosition(Vec2(Director::getInstance()->getVisibleOrigin().x + back->getContentSize().width / 2, Director::getInstance()->getWinSize().height - back->getContentSize().height / 2));

	Menu* menu = Menu::create(stage1, stage2, stage3, back, NULL);
	menu->setPosition(Vec2::ZERO);
	this->addChild(menu, 1);

	ParticleSystem* m_emitter;
	m_emitter = new ParticleSystemQuad();
	m_emitter->setTotalParticles(25);
	m_emitter = ParticleGalaxy::create();
	m_emitter->setPosition(Director::getInstance()->getWinSize().width / 4, Director::getInstance()->getWinSize().height / 4);
	m_emitter->setStartSize(12);
	m_emitter->setDuration(-1);
	this->addChild(m_emitter, 0);

	return true;
}

void StageSelect::GoToStage1(Ref*) {
	stage::stageNumber = 1;
	stage::score = 0;
	stage::Hp = 100;
	stage::BossHp = 2000;
	stage::x = 0;
	stage::s = 0;
	auto scene = GameScene::createScene();
	auto selectScene = TransitionSlideInT::create(1.0f, scene);
	Director::getInstance()->replaceScene(selectScene);
}

void StageSelect::GoToStage2(Ref*) {
	stage::stageNumber = 2;
	stage::score = 0;
	stage::Hp = 100;
	stage::BossHp = 2000;
	stage::x = 0;
	stage::s = 0;
	auto scene = GameScene2::createScene();
	auto selectScene = TransitionSlideInT::create(1.0f, scene);
	Director::getInstance()->replaceScene(selectScene);
}

void StageSelect::GoToStage3(Ref*) {
	stage::stageNumber = 3;
	stage::score = 0;
	stage::Hp = 100;
	stage::BossHp = 2000;
	stage::x = 0;
	stage::s = 0;
	auto scene = GameScene3::createScene();
	auto selectScene = TransitionSlideInT::create(1.0f, scene);
	Director::getInstance()->replaceScene(selectScene);
}

void StageSelect::back(Ref*) {
	auto scene = Scene1::scene();
	auto selectScene = TransitionSlideInT::create(1.0f, scene);
	Director::getInstance()->replaceScene(selectScene);
}