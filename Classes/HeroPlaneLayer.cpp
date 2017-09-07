#include "HeroPlaneLayer.h"
#include "BulletLayer.h"
#include "HeroPlaneSprite.h"

using namespace cocos2d;

HeroPlaneSprite* HeroPlaneLayer::hero_plane_sprite = nullptr;

bool HeroPlaneLayer::init() {
	if (!Layer::init()) {
		return false;
	}
	auto visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	hero_plane_sprite = HeroPlaneSprite::getInstance();
	this->addChild(hero_plane_sprite);
	hero_plane_sprite->setPosition(visibleSize.width / 2 + origin.x, origin.y + 30);
	//启动飞机动画
	Animation * animation = Animation::create();
	SpriteFrame * spriteFrame1 = SpriteFrame::create("hero1.png", Rect(0, 0, 45, 46));                    //优化可以用 SpriteFrameCache用法查Api
	SpriteFrame * spriteFrame2 = SpriteFrame::create("hero1f.png", Rect(0, 0, 45, 46));
	animation->addSpriteFrame(spriteFrame1);
	animation->addSpriteFrame(spriteFrame2);
	animation->setDelayPerUnit(0.15f);
	Animate * animate = Animate::create(animation);

	hero_plane_sprite->runAction(RepeatForever::create(animate));//执行动画

	//¼üÅÌ¼àÌý
	auto listener = EventListenerKeyboard::create();

	listener->onKeyPressed = [this](EventKeyboard::KeyCode code, Event *e) {
		switch (code) {
		case EventKeyboard::KeyCode::KEY_LEFT_ARROW:
			key[0] = 1;
			break;
		case EventKeyboard::KeyCode::KEY_RIGHT_ARROW:
			key[1] = 1;
			break;
		case EventKeyboard::KeyCode::KEY_UP_ARROW:
			key[2] = 1;
			break;
		case EventKeyboard::KeyCode::KEY_DOWN_ARROW:
			key[3] = 1;
			break;
		default:
			break;
		}
	};

	listener->onKeyReleased = [this](EventKeyboard::KeyCode code, Event *e) {
		switch (code) {
		case EventKeyboard::KeyCode::KEY_LEFT_ARROW:
			key[0] = 0;
			break;
		case EventKeyboard::KeyCode::KEY_RIGHT_ARROW:
			key[1] = 0;
			break;
		case EventKeyboard::KeyCode::KEY_UP_ARROW:
			key[2] = 0;
			break;
		case EventKeyboard::KeyCode::KEY_DOWN_ARROW:
			key[3] = 0;
			break;
		default:
			break;
		}
	};

	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);

	scheduleUpdate();


	return true;
}

void HeroPlaneLayer::controlPlaneByKeyboard(int i) {
	float x = 0;
	float y = 0;
	switch (i) {
	case 0:
		x = -5;
		break;
	case 1:
		x = 5;
		break;
	case 2:
		y = 5;
		break;
	case 3:
		y = -5;
		break;
	default:
		break;
	}

	auto visibleSize = Director::getInstance()->getVisibleSize();
	auto origin = Director::getInstance()->getVisibleOrigin();


	auto *move = MoveTo::create(0.02f, Point(hero_plane_sprite->getPositionX() + x, hero_plane_sprite->getPositionY() + y));

	hero_plane_sprite->runAction(move);
}


void HeroPlaneLayer::update(float delta) {
	auto visibleSize = Director::getInstance()->getVisibleSize();
	//auto hero_plane_sprite = getChildByTag(3);
	
		if (hero_plane_sprite->getPositionX() < hero_plane_sprite->getContentSize().width / 2 + 75) {
			key[0] = 0;
		}
		if (hero_plane_sprite->getPositionX() > visibleSize.width - hero_plane_sprite->getContentSize().width / 2 + 90) {
			key[1] = 0;
		}
		if (hero_plane_sprite->getPositionY() > visibleSize.height - hero_plane_sprite->getContentSize().height / 2) {
			key[2] = 0;
		}
		if (hero_plane_sprite->getPositionY() < hero_plane_sprite->getContentSize().height / 2) {
			key[3] = 0;
		}


	for (int i = 0; i < 4; i++) {
		if (key[i] == 1)
			controlPlaneByKeyboard(i);
	}
}

HeroPlaneSprite* HeroPlaneLayer::getHeroPointer()
{
	return hero_plane_sprite;
}
