#include "BossLayer.h"
#include "GameScene.h"
#include "stage.h"
#include "HeroPlaneLayer.h"

bool BossLayer::init() {
	if (!Layer::init()) {
		return false;
	}

	scheduleUpdate();
	return true;
}
void BossLayer::update(float delta) {
	if (stage::x == 1) { //Boss已死
		this->unscheduleAllSelectors();
		Boss_pointer = nullptr;
	}
	else
	{
		if (stage::score >= 9000 && stage::s == 0) {  //若没有Boss就先创建
			BossCreate(stage::stageNumber);
		}
		else if(stage::score >= 9000 && stage::s == 1){
			if (stage::stageNumber == 1 || stage::stageNumber == 2) {
				this->schedule(schedule_selector(BossLayer::BossMove),0.01);
				this->schedule(schedule_selector(BossLayer::bossTakeFire), 2);
			}
			else if (stage::stageNumber == 3) {
				this->schedule(schedule_selector(BossLayer::BossMove2), 0.01);
				this->schedule(schedule_selector(BossLayer::bossTakeFire), 2);
			}
		}
	}
}

void BossLayer::BossCreate(int num) {
	//if (stage::score >= 9000) {
		switch (num)
		{
		case 1:
			Boss_pointer = Sprite::create("Boss4.png");
			createBossBody();
			Boss_pointer->setTag(7);
			Boss_pointer->setPosition(Vec2(Director::getInstance()->getVisibleSize().width / 2 + 100, Director::getInstance()->getVisibleSize().height - Boss_pointer->getContentSize().height / 2 + 150));
			this->addChild(Boss_pointer);
			stage::s = 1;
			break;

		case 2:
			Boss_pointer = Sprite::create("Boss2.png");
			createBossBody();
			Boss_pointer->setTag(7);
			Boss_pointer->setPosition(Vec2(Director::getInstance()->getVisibleSize().width / 2 + 100, Director::getInstance()->getVisibleSize().height - Boss_pointer->getContentSize().height / 2 + 150));
			this->addChild(Boss_pointer);
			stage::s = 1;
			break;
			
		case 3:
			Boss_pointer = Sprite::create("Boss3.png");
			createBossBody();
			Boss_pointer->setTag(7);
			Boss_pointer->setPosition(Vec2(Director::getInstance()->getVisibleSize().width / 2 + 100, Director::getInstance()->getVisibleSize().height - Boss_pointer->getContentSize().height / 2 + 150));
			this->addChild(Boss_pointer);
			stage::s = 1;
			break;

		default:
			break;
		}
	//}
}

void BossLayer::BossMove(float f) {
	auto up_border = Director::getInstance()->getVisibleSize().height - Boss_pointer->getContentSize().height + 40;
	auto left_border = Boss_pointer->getContentSize().width / 2 + 120;
	auto right_border = Director::getInstance()->getVisibleSize().width - Boss_pointer->getContentSize().width / 2 + 95;
	//顶到屏幕上方就下移
	if (Boss_pointer->getPositionY() > up_border) 
	{
		Boss_pointer->setPositionY(Boss_pointer->getPositionY() - 1);
	}

	else {
		if (isRight) { //向右移
			if (Boss_pointer->getPositionX() < right_border)
			{
				Boss_pointer->setPositionX(Boss_pointer->getPositionX() + 1);
			}
			else {
				isRight = false;
			}
		}
		else { //向左移
			if (Boss_pointer->getPositionX() > left_border) 
			{
				Boss_pointer->setPositionX(Boss_pointer->getPositionX() - 1);
			}
			else
			{
				isRight = true;
			}
		}
	}
}

void BossLayer::BossMove2(float f) {
	auto up_border = Director::getInstance()->getVisibleSize().height - Boss_pointer->getContentSize().height + 40;
	auto left_border = Boss_pointer->getContentSize().width / 2 + 40;
	auto right_border = Director::getInstance()->getVisibleSize().width - Boss_pointer->getContentSize().width / 2 + 95;
	//顶到屏幕上方就下移
	if (Boss_pointer->getPositionY() > up_border)
	{
		Boss_pointer->setPositionY(Boss_pointer->getPositionY() - 1);
	}

	else {
		if (isRight) { //向右移
			if (Boss_pointer->getPositionX() < right_border)
			{
				Boss_pointer->setPositionX(Boss_pointer->getPositionX() + 1);
			}
			else {
				isRight = false;
			}
		}
		else { //向左移
			if (Boss_pointer->getPositionX() > left_border)
			{
				Boss_pointer->setPositionX(Boss_pointer->getPositionX() - 1);
			}
			else
			{
				isRight = true;
			}
		}
	}
}

void BossLayer::bossTakeFire(float delta)
{
	auto visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();
	auto boss_position = Boss_pointer->getPosition();
	int random = rand() % 2 + 1;
	//散弹方式：
	if (random == 1) {
		this->unschedule(schedule_selector(BossLayer::bulletCreate));
		for (int i = 0; i < 9; i++)
		{
			auto boss_bullet = Sprite::create("bullet2.png");
			boss_bullet->setTag(13);
			auto enemyBody_bullet = PhysicsBody::createBox(boss_bullet->getContentSize());
			enemyBody_bullet->setContactTestBitmask(0x0003);
			enemyBody_bullet->setCategoryBitmask(0x0002);
			enemyBody_bullet->setCollisionBitmask(0x0001);
			enemyBody_bullet->setGravityEnable(false);
			boss_bullet->setPhysicsBody(enemyBody_bullet);

			boss_bullet->setPosition(Vec2(boss_position));
			this->addChild(boss_bullet);

			auto Move = MoveBy::create(3.0f, Vec2((i - 4) * 500, -960));
			auto actionDone = CallFuncN::create(CC_CALLBACK_1(BossLayer::bossBulletRemove, this));
			Sequence* sequence = Sequence::create(Move, actionDone, nullptr);
			boss_bullet->runAction(sequence);
		}
	}
	//连射方式
	else if (random == 2) {
		this->schedule(schedule_selector(BossLayer::bulletCreate), 0.1);
	}
}


void BossLayer::bossBulletRemove(Node* pNode) {
	if (NULL == pNode) {
		return;
	}
	Sprite* bullet = (Sprite*)pNode;
	bullet->removeFromParentAndCleanup(true);
	this->removeChild(bullet, true);
}

void BossLayer::bulletCreate(float f) {
	auto boss_position = Boss_pointer->getPosition();
	Sprite* bullet = Sprite::create("bullet1.png");
	bullet->setTag(14);
	bullet->setPosition(boss_position.x, boss_position.y - 20);
	auto bulletBody = PhysicsBody::createBox(bullet->getContentSize());
	bulletBody->setContactTestBitmask(0x0003);
	bulletBody->setCategoryBitmask(0x0002);
	bulletBody->setCollisionBitmask(0x0001);
	bulletBody->setGravityEnable(false);
	bullet->setPhysicsBody(bulletBody);
	this->addChild(bullet);
	auto Move = MoveBy::create(1.5f, Vec2(0, -960));
	auto actionDone = CallFuncN::create(CC_CALLBACK_1(BossLayer::bossBulletRemove, this));
	Sequence* sequence = Sequence::create(Move, actionDone, nullptr);
	bullet->runAction(sequence);
}

void BossLayer::createBossBody()
{
	auto BossBody = PhysicsBody::createBox(Boss_pointer->getContentSize());        //创建物理实体
	BossBody->setContactTestBitmask(0x0003);
	BossBody->setCategoryBitmask(0x0002);
	BossBody->setCollisionBitmask(0x0001);
	BossBody->setGravityEnable(false);
	Boss_pointer->setPhysicsBody(BossBody);
}