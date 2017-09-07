#include "BulletLayer.h"
#include "HeroPlaneLayer.h"
#include "HeroPlaneSprite.h"

bool BulletLayer::init() {
	if (!Layer::init()) {
		return false;
	}

	auto listener = EventListenerKeyboard::create();
	listener->onKeyPressed = [this](EventKeyboard::KeyCode code, Event *e) {
		if (code == EventKeyboard::KeyCode::KEY_Z)
			s = 1;
	};
	listener->onKeyReleased = [this](EventKeyboard::KeyCode code, Event *e) {
		if (code == EventKeyboard::KeyCode::KEY_Z)
			s = 0;
	};
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);

	scheduleUpdate();

	return true;
}

void BulletLayer::update(float delta) {
	if (s == 1) {
		this->schedule(schedule_selector(BulletLayer::bulletCreate), 0.1);
		this->schedule(schedule_selector(BulletLayer::bulletMove), 0.01);
	}
	if (s == 0)
		this->unschedule(schedule_selector(BulletLayer::bulletCreate));
}

void BulletLayer::bulletCreate(float f) {
	auto plane_position = HeroPlaneLayer::getHeroPointer()->getPosition();
	Sprite* bullet = Sprite::create("bullet1.png");
	bullet->setPosition(plane_position.x, plane_position.y + 20);
	bullet->setTag(4);
	auto bulletBody = PhysicsBody::createBox(bullet->getContentSize());
	bulletBody->setContactTestBitmask(0x0002);
	bulletBody->setCategoryBitmask(0x0005);
	bulletBody->setCollisionBitmask(0x0002);
	bulletBody->setGravityEnable(false);
	bullet->setPhysicsBody(bulletBody);
	this->addChild(bullet);
	this->bulletList.pushBack(bullet);

}

void BulletLayer::bulletMove(float f) {
	for (int i = 0; i < bulletList.size(); i++)
	{
		auto bullet = bulletList.at(i);
		bullet->setPositionY(bullet->getPositionY() + 3);
		//如果该子弹已经超出屏幕范围，则移除它
		if (bullet->getPositionY() > Director::getInstance()->getVisibleSize().height) {
			bullet->removeFromParent(); //从层中移除
			bulletList.eraseObject(bullet);//从记录所有子弹的vector中移除
										   //移除后上一个对象会移到当前这个对象的位置，实际还是当前这个i，所以要i--才能访问到下一个对象
			i--;
		}
	}
}