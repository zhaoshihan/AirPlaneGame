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
		//������ӵ��Ѿ�������Ļ��Χ�����Ƴ���
		if (bullet->getPositionY() > Director::getInstance()->getVisibleSize().height) {
			bullet->removeFromParent(); //�Ӳ����Ƴ�
			bulletList.eraseObject(bullet);//�Ӽ�¼�����ӵ���vector���Ƴ�
										   //�Ƴ�����һ��������Ƶ���ǰ��������λ�ã�ʵ�ʻ��ǵ�ǰ���i������Ҫi--���ܷ��ʵ���һ������
			i--;
		}
	}
}