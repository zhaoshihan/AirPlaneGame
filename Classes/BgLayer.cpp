#include "BgLayer.h"
#include"stage.h"
using namespace cocos2d;

bool BgLayer::init()
{
	if (!Layer::init()) {
		return false;
	}

	auto visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	//ÐÇ¿Õ±³¾°£º
	if (stage::stageNumber == 1) {
		auto bg1_down = Sprite::create("bg1.png");
		bg1_down->setPosition(Vec2(origin.x + visibleSize.width / 2, 0));
		bg1_down->setName("bg1_down");
		bg1_down->setAnchorPoint(Vec2(0.5, 0));
		this->addChild(bg1_down, 0);

		auto bg1_up = Sprite::create("bg1.png");
		bg1_up->setPosition(Vec2(origin.x + visibleSize.width / 2, bg1_down->getPositionY() + bg1_down->getContentSize().height));
		bg1_up->setName("bg1_up");
		bg1_up->setAnchorPoint(Vec2(0.5, 0));
		this->addChild(bg1_up, 0);

		auto bg2_up = Sprite::create("bg2.png");
		bg2_up->setPosition(Vec2(origin.x, origin.y + visibleSize.height));
		bg2_up->setName("bg2_up");
		bg2_up->setAnchorPoint(Vec2(0, 0));
		this->addChild(bg2_up, 1);
	}
	else if (stage::stageNumber == 2) {
		auto bg1_down = Sprite::create("bg3.png");
		bg1_down->setPosition(Vec2(origin.x + visibleSize.width / 2, 0));
		bg1_down->setName("bg1_down");
		bg1_down->setAnchorPoint(Vec2(0.5, 0));
		this->addChild(bg1_down, 0);

		auto bg1_up = Sprite::create("bg3.png");
		bg1_up->setPosition(Vec2(origin.x + visibleSize.width / 2, bg1_down->getPositionY() + bg1_down->getContentSize().height));
		bg1_up->setName("bg1_up");
		bg1_up->setAnchorPoint(Vec2(0.5, 0));
		this->addChild(bg1_up, 0);

		auto bg2_up = Sprite::create("bg2.png");
		bg2_up->setPosition(Vec2(origin.x, origin.y + visibleSize.height));
		bg2_up->setName("bg2_up");
		bg2_up->setAnchorPoint(Vec2(0, 0));
		this->addChild(bg2_up, 1);
	}
	else if (stage::stageNumber == 3) {
		auto bg1_down = Sprite::create("bg7.png");
		bg1_down->setPosition(Vec2(origin.x + visibleSize.width / 2, 0));
		bg1_down->setName("bg1_down");
		bg1_down->setAnchorPoint(Vec2(0.5, 0));
		this->addChild(bg1_down, 0);

		auto bg1_up = Sprite::create("bg7.png");
		bg1_up->setPosition(Vec2(origin.x + visibleSize.width / 2, bg1_down->getPositionY() + bg1_down->getContentSize().height));
		bg1_up->setName("bg1_up");
		bg1_up->setAnchorPoint(Vec2(0.5, 0));
		this->addChild(bg1_up, 0);

		auto bg2_up = Sprite::create("bg8.png");
		bg2_up->setPosition(Vec2(origin.x, origin.y + visibleSize.height));
		bg2_up->setName("bg2_up");
		bg2_up->setAnchorPoint(Vec2(0, 0));
		this->addChild(bg2_up, 1);
		
	}

	this->schedule(schedule_selector(BgLayer::bg1_Move), 0.01);
	this->schedule(schedule_selector(BgLayer::bg2_Move), 0.01);

	return true;
}

void BgLayer::bg1_Move(float f)
{
	auto bg1_down = this->getChildByName("bg1_down");
	auto bg1_up = this->getChildByName("bg1_up");
	if (bg1_up->getPositionY() + bg1_up->getContentSize().height <= Director::getInstance()->getVisibleSize().height) {
		bg1_down->setPositionY(Director::getInstance()->getVisibleSize().height - bg1_down->getContentSize().height);
	}
	bg1_down->setPositionY(bg1_down->getPositionY() - 1);
	bg1_up->setPositionY(bg1_down->getPositionY() + bg1_down->getContentSize().height);
}

void BgLayer::bg2_Move(float f)
{
	auto bg2_up = this->getChildByName("bg2_up");
	float speed = 0.5;
	float y = bg2_up->getPositionY();
	int glview_height = Director::getInstance()->getVisibleSize().height;
	int graph_height = bg2_up->getContentSize().height;
	bg2_up->setPositionY(y - speed);
	if (y <= -graph_height) {
		bg2_up->setPositionY(glview_height);
	}

}