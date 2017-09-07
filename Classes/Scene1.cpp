#include "HelloWorldScene.h"
#include "Scene1.h"
#include "GameScene.h"
#include "StageSelect.h"
#include "stage.h"

USING_NS_CC;
Scene* Scene1::scene() {
	Scene *scene = Scene::create();
	Scene1 *layer = Scene1::create();
	scene->addChild(layer);
	return scene;
}

bool Scene1::init() {
	auto visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	ParticleSystem* m_emitter;
	m_emitter = new ParticleSystemQuad();
	m_emitter->setTotalParticles(100);
	m_emitter = ParticleMeteor::create();
	m_emitter->setPosition(Director::getInstance()->getWinSize().width / 5 * 4, Director::getInstance()->getWinSize().height / 4);

	m_emitter->setStartSize(15);

	m_emitter->setDuration(-1);
	this->addChild(m_emitter, 2);

	auto bg = Sprite::create("startscene.jpg");
	bg->setPosition(Vec2(Director::getInstance()->getWinSize().width / 2, Director::getInstance()->getWinSize().height / 2));
	this->addChild(bg);

	auto startItem = MenuItemImage::create("start.png", "start.png", CC_CALLBACK_1(Scene1::menuGoToGameScene, this));
	startItem->setPosition(Vec2(Director::getInstance()->getWinSize().width / 5 * 3, Director::getInstance()->getWinSize().height / 4 * 3));

	auto stageItem = MenuItemImage::create("stage.png", "stage.png", CC_CALLBACK_1(Scene1::menuGoToStage, this));
	stageItem->setPosition(Vec2(Director::getInstance()->getWinSize().width / 5 * 3, Director::getInstance()->getWinSize().height / 4 * 3 - startItem->getContentSize().height * 2));

	auto closeItem = MenuItemImage::create("exit_a.png", "exit_a.png", CC_CALLBACK_1(Scene1::menuEnd, this));
	closeItem->setPosition(Vec2(Director::getInstance()->getWinSize().width / 5 * 3, Director::getInstance()->getWinSize().height / 4 * 3 - startItem->getContentSize().height * 4));

	Menu* pMenu = Menu::create(closeItem, startItem, stageItem, NULL);
	pMenu->setPosition(Vec2::ZERO);
	this->addChild(pMenu);

	return true;
}

void Scene1::menuGoToGameScene(Ref* r) {
	stage::stageNumber = 1;
	stage::score = 0;
	stage::Hp = 100;
	stage::BossHp = 2000;
	stage::x = 0;
	stage::s = 0;
	auto scene = GameScene::createScene();
	auto gameScene = TransitionSlideInR::create(1.0f, scene);
	Director::getInstance()->replaceScene(gameScene);

}

void Scene1::menuGoToStage(Ref* r) {
	auto scene = StageSelect::createScene();
	auto selectScene = TransitionSlideInB::create(1.0f, scene);
	Director::getInstance()->replaceScene(selectScene);

}

void  Scene1::menuEnd(Ref* r) {
	Director::getInstance()->end();
}