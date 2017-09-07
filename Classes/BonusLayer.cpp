#include "BonusLayer.h"
#include "stage.h"
static Sprite * bonus_pointer = nullptr;

bool BonusLayer::init() {
	if (!Layer::init()) {
		return false;
	}
	this->schedule([&](float dt) {createHpBonus(); }, 15, 1, 20, "schedulerKey1");  //每一关都只各自出两个道具包
	this->schedule([&](float dt) {createClearBonus(); }, 15, 1, 30, "schedulerKey2");  
	return true;
}

void BonusLayer::createHpBonus()
{
	auto winSize = Director::getInstance()->getWinSize();

	bonus_pointer = Sprite::create("kit1.png");
	createBonusBody();
	bonus_pointer->setTag(9);
	this->addChild(bonus_pointer);

	bonus_pointer->setPosition(rand () % 360 + 60, winSize.height);
	auto Move = MoveTo::create(4.0f, Vec2 (bonus_pointer->getPositionX(), 0));
	auto actionDone = CallFuncN::create(CC_CALLBACK_1(BonusLayer::bonusRemove, this));
	Sequence* sequence = Sequence::create(Move, actionDone, nullptr);
	bonus_pointer->runAction(sequence);
}

void BonusLayer::createClearBonus()
{
	auto winSize = Director::getInstance()->getWinSize();

	bonus_pointer = Sprite::create("HelloWorld.png");
	createBonusBody();
	bonus_pointer->setTag(11);
	this->addChild(bonus_pointer);

	bonus_pointer->setPosition(rand() % 360 + 60, winSize.height);
	auto Move = MoveTo::create(4.0f, Vec2(bonus_pointer->getPositionX(), 0));
	auto actionDone = CallFuncN::create(CC_CALLBACK_1(BonusLayer::bonusRemove, this));
	Sequence* sequence = Sequence::create(Move, actionDone, nullptr);
	bonus_pointer->runAction(sequence);
}

void BonusLayer::bonusRemove(Node* pNode) {
	if (NULL == pNode) {
		return;
	}
	Sprite* bonus = (Sprite*)pNode;
	bonus->removeFromParentAndCleanup(true);
	this->removeChild(bonus, true);
}

void BonusLayer::createBonusBody()
{
	auto bonusBody = PhysicsBody::createBox(bonus_pointer->getContentSize());        //创建物理实体
	bonusBody->setContactTestBitmask(0x0003);
	bonusBody->setCategoryBitmask(0x0002);
	bonusBody->setCollisionBitmask(0x0001);
	bonusBody->setGravityEnable(false);
	bonus_pointer->setPhysicsBody(bonusBody);
}
