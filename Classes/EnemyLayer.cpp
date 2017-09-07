#include "EnemyLayer.h"
#include "HeroPlaneLayer.h"
#include "stage.h"

bool EnemyLayer::init() {
	if (!Layer::init()) {
		return false;
	}

	this->schedule(schedule_selector(EnemyLayer::takeFire), 2);

	scheduleUpdate();  //分场景调度敌机出现
	
	return true;
}

//敌机一律改tag=5
void EnemyLayer::enemyCreate(float f)
{
	auto winSize = Director::getInstance()->getWinSize();
	int random = rand() % 2 + 1;
	auto enemy = EnemySprite::createEnemySprite(random); 

	enemy->setPosition(Vec2( rand() % 280 + 100, winSize.height + enemy->getContentSize().height));//随机在屏幕最上方的出现敌机
	enemy->setTag(5);

	this->addChild(enemy);
	this->enemyList.pushBack(enemy);

	auto Move = MoveTo::create(5.0f, Vec2(enemy->getPositionX(), 0));
	auto actionDone = CallFuncN::create(CC_CALLBACK_1(EnemyLayer::enemyRemove, this));
	Sequence* sequence = Sequence::create(Move, actionDone, nullptr);
	enemy->runAction(sequence);
}

void EnemyLayer::enemy_lCreate(int num) {
	auto enemy_l = EnemySprite::createEnemySprite(num);
	enemy_l->setTag(5);
	enemy_l->setRotation(-90);
	enemy_l->setPosition(Vec2(0, 280));

	this->addChild(enemy_l);
	this->enemyList.pushBack(enemy_l);

	//设置贝塞尔曲线参数
	ccBezierConfig tr1;
	tr1.endPosition = Vec2(0, 10);//终点
	tr1.controlPoint_1 = Vec2(250, 300);//控制点1
	tr1.controlPoint_2 = Vec2(240, 100);//控制点2

	//创建运行的贝塞尔曲线
	ActionInterval* bezierForward1 = BezierTo::create(3.f, tr1);
	ActionInterval *forwardBy1 = RotateBy::create(3.f, 180);
	Spawn* spawn1 = Spawn::create(bezierForward1, forwardBy1, NULL);

	//飞机执行完动作后移除
	auto actionDone = CallFuncN::create(
	CC_CALLBACK_1(EnemyLayer::enemyRemove, this));

	//连续动作
	Sequence* sequence1 = Sequence::create(spawn1, actionDone, NULL);
	enemy_l->runAction(sequence1);
}

void EnemyLayer::enemy_rCreate(int num) {
	Size winSize = Director::getInstance()->getWinSize();
	auto enemy_r = EnemySprite::createEnemySprite(num);
	enemy_r->setRotation(90);
	enemy_r->setPosition(Vec2(winSize.width, 280));
	enemy_r->setTag(5);
	this->addChild(enemy_r);
	this->enemyList.pushBack(enemy_r);
	//设置贝塞尔曲线参数
	ccBezierConfig tr2;
	tr2.endPosition = Vec2(winSize.width, 10);//终点
	tr2.controlPoint_1 = Vec2(winSize.width - 250, 300);//控制点1
	tr2.controlPoint_2 = Vec2(winSize.width - 240, 100);//控制点2
														//创建运行的贝塞尔曲线
	ActionInterval* bezierForward2 = BezierTo::create(3.f, tr2);
	ActionInterval *forwardBy2 = RotateBy::create(3.f, -180);
	Spawn* spawn2 = Spawn::create(bezierForward2, forwardBy2, NULL);
	//飞机执行完动作后移除
	auto actionDone = CallFuncN::create(CC_CALLBACK_1(EnemyLayer::enemyRemove, this));
	//连续动作
	Sequence* sequence2 = Sequence::create(spawn2, actionDone, NULL);
	enemy_r->runAction(sequence2);
}

void EnemyLayer::enemy_xCreate1(int num)
{
	Size winSize = Director::getInstance()->getWinSize();
	//生成精灵  
	auto enemy = EnemySprite::createEnemySprite(num);
	enemy->setTag(5);

	float height = enemy->getContentSize().height;
	float width = enemy->getContentSize().width;
	enemy->setRotation(-52);
	enemy->setPosition(Vec2(0, winSize.height + height));
	this->addChild(enemy);
	this->enemyList.pushBack(enemy);

	//速度 时间
	float v = 50;
	float l = winSize.height;
	float t = l / v;

	auto Move = MoveBy::create(t, Point(winSize.width, -winSize.height - 2 * height));
	auto actionDone = CallFuncN::create(CC_CALLBACK_1(EnemyLayer::enemyRemove, this));
	Sequence* sequence = Sequence::create(Move, actionDone, NULL);
	enemy->runAction(sequence);
}

void EnemyLayer::enemy_xCreate2(int num)
{
	Size winSize = Director::getInstance()->getWinSize();
	//生成精灵  
	auto enemy = EnemySprite::createEnemySprite(num);
	enemy->setTag(5);

	float height = enemy->getContentSize().height;
	float width = enemy->getContentSize().width;
	enemy->setRotation(-52);
	enemy->setPosition(Vec2(0, winSize.height + height));
	this->addChild(enemy);
	this->enemyList.pushBack(enemy);

	//速度 时间
	float v = 50;
	float l = winSize.height;
	float t = l / v;

	auto Move = MoveBy::create(t, Point(-winSize.width, -winSize.height - 2 * height));
	auto actionDone = CallFuncN::create(CC_CALLBACK_1(EnemyLayer::enemyRemove, this));
	Sequence* sequence = Sequence::create(Move, actionDone, NULL);
	enemy->runAction(sequence);
}

void EnemyLayer::enemy_vCreate(int num)
{
	Size winSize = Director::getInstance()->getWinSize();
	//生成精灵  
	auto enemy1 = EnemySprite::createEnemySprite(num);
	enemy1->setTag(5);
	//2
	auto enemy2 = EnemySprite::createEnemySprite(num);
	enemy2->setTag(5);
	//3
	auto enemy3 = EnemySprite::createEnemySprite(num);
	enemy3->setTag(5);
	//4
	auto enemy4 = EnemySprite::createEnemySprite(num);
	enemy4->setTag(5);
	//5
	auto enemy5 = EnemySprite::createEnemySprite(num);
	enemy5->setTag(5);

	//得到精灵宽和高  
	float height = enemy1->getContentSize().height;
	float width = enemy1->getContentSize().width;

	//设置位置  
	enemy1->setPosition(Vec2(winSize.width / 2, winSize.height + height));
	enemy2->setPosition(Vec2(winSize.width / 2 - width - 15, winSize.height + 1.5 * height));
	enemy3->setPosition(Vec2(winSize.width / 2 + width + 15, winSize.height + 1.5 * height));
	enemy4->setPosition(Vec2(winSize.width / 2 - 2 * width - 30, winSize.height + 2 * height));
	enemy5->setPosition(Vec2(winSize.width / 2 + 2 * width + 30, winSize.height + 2 * height));

	//层中加入精灵  
	this->addChild(enemy1);
	this->enemyList.pushBack(enemy1);
	this->addChild(enemy2);
	this->enemyList.pushBack(enemy2);
	this->addChild(enemy3);
	this->enemyList.pushBack(enemy3);
	this->addChild(enemy4);
	this->enemyList.pushBack(enemy4);
	this->addChild(enemy5);
	this->enemyList.pushBack(enemy5);

	//计算飞行时间  
	float v = 50;//运行速度，可以自己控制，每秒所走的像素  
	float l = winSize.height;
	float t = l / v;//实际飞行的时间  

	//从飞机处开始运行到屏幕底部  
	auto Move1 = MoveBy::create(t, Point(0, -winSize.height - 2.5 *height));
	auto Move2 = MoveBy::create(t, Point(0, -winSize.height - 2.5 * height));
	auto Move3 = MoveBy::create(t, Point(0, -winSize.height - 2.5 *height));
	auto Move4 = MoveBy::create(t, Point(0, -winSize.height - 2.5 * height));
	auto Move5 = MoveBy::create(t, Point(0, -winSize.height - 2.5 * height));

	//子弹执行完动作后进行函数回调，调用移除函数  
	auto actionDone = CallFuncN::create(CC_CALLBACK_1(EnemyLayer::enemyRemove, this));

	//连续动作  
	Sequence* sequence1 = Sequence::create(Move1, actionDone, NULL);
	Sequence* sequence2 = Sequence::create(Move2, actionDone, NULL);
	Sequence* sequence3 = Sequence::create(Move3, actionDone, NULL);
	Sequence* sequence4 = Sequence::create(Move4, actionDone, NULL);
	Sequence* sequence5 = Sequence::create(Move5, actionDone, NULL);

	// 开始跑动
	enemy1->runAction(sequence1);
	enemy2->runAction(sequence2);
	enemy3->runAction(sequence3);
	enemy4->runAction(sequence4);
	enemy5->runAction(sequence5);
}

void EnemyLayer::enemyRemove(Node* pNode) {
	if (NULL == pNode) {
		return;
	}
	EnemySprite * plane = (EnemySprite *)pNode;
	plane->removeFromParentAndCleanup(true);
	this->enemyList.eraseObject(plane);
	delete plane;
}

//负责调度各类敌机出现
//左右机创建时 不再随机下落敌机!!!!!!
void EnemyLayer::update(float delta) {
	if (stage::s == 1) {
		//Boss出现后敌机不再出现
		this->unscheduleAllSelectors();
	}
	else
	{
		this->schedule(schedule_selector(EnemyLayer::enemyCreate), 0.5);
		auto score = stage::score;
		switch (stage::stageNumber)
		{
		case 1: //第一关的敌机场景设计，下同
			if (score >= 500 && score <= 1200) {
				this->unschedule(schedule_selector(EnemyLayer::enemyCreate));
				this->schedule([&](float dt) {enemy_lCreate(1);}, 0.5f, 0, 0, "schedulerKey1"); 
			}
			else if (score >= 1200 && score <= 1800) {
				this->unschedule(schedule_selector(EnemyLayer::enemyCreate));
				this->schedule([&](float dt) {enemy_rCreate(1); }, 0.5f, 0, 0, "schedulerKey2");
			}
			else if (score >= 2500 && score <= 3200) {
				this->unschedule(schedule_selector(EnemyLayer::enemyCreate));
				this->schedule([&](float dt) {enemy_lCreate(2); }, 0.5f, 0, 0, "schedulerKey3");
			}
			else if (score >= 3500 && score <= 4300) {
				this->unschedule(schedule_selector(EnemyLayer::enemyCreate));
				this->schedule([&](float dt) {enemy_rCreate(2); }, 0.5f, 0, 0, "schedulerKey4");
			}
			else if (score >= 5500 && score <= 6200) {
				this->unschedule(schedule_selector(EnemyLayer::enemyCreate));
				this->schedule([&](float dt) {enemy_lCreate(1); enemy_rCreate(2); }, 0.5f, 0, 0, "schedulerKey5");
			}
			else if (score >= 6700 && score <= 7300) {
				this->unschedule(schedule_selector(EnemyLayer::enemyCreate));
				this->schedule([&](float dt) {enemy_lCreate(2); enemy_rCreate(1); }, 0.5f, 0, 0, "schedulerKey6");
			}
			break;

		case 2:
			if (score >= 500 && score <= 1200) {
				this->unschedule(schedule_selector(EnemyLayer::enemyCreate));
				this->schedule([&](float dt) {enemy_lCreate(4); }, 0.5f, 0, 0, "schedulerKey1");
			}
			else if (score >= 1200 && score <= 1800) {
				this->unschedule(schedule_selector(EnemyLayer::enemyCreate));
				this->schedule([&](float dt) {enemy_rCreate(4); }, 0.5f, 0, 0, "schedulerKey2");
			}
			else if (score >= 2500 && score <= 3200) {
				this->schedule([&](float dt) {enemy_xCreate1(7); }, 0.5f, 0, 0, "schedulerKey3");
			}
			else if (score >= 3500 && score <= 4200) {
				this->schedule([&](float dt) {enemy_xCreate2(7); }, 0.5f, 0, 0, "schedulerKey4");
			}
			else if (score >= 6000 && score <= 6600) {
				this->unschedule(schedule_selector(EnemyLayer::enemyCreate));
				this->schedule([&](float dt) {enemy_lCreate(5); enemy_rCreate(5); }, 0.5f, 0, 0, "schedulerKey5");
			}
			else if (score >= 6900 && score <= 7500) {
				this->schedule([&](float dt) {enemy_xCreate2(7); }, 0.5f, 0, 0, "schedulerKey6");
			}
			else if (score >= 7600 && score <= 8300) {
				this->schedule([&](float dt) {enemy_xCreate1(7); }, 0.5f, 0, 0, "schedulerKey7");
			}
			break;

		case 3:
			if (score >= 500 && score <= 700) {
				this->schedule([&](float dt) {enemy_vCreate(8); }, 0.5f, 0, 0, "schedulerKey1");
			}
			else if (score >= 1600 && score <= 1800) {
				this->schedule([&](float dt) {enemy_vCreate(6); }, 0.5f, 0, 0, "schedulerKey2");
			}
			else if (score >= 2300 && score <= 3000) {
				this->unschedule(schedule_selector(EnemyLayer::enemyCreate));
				this->schedule([&](float dt) {enemy_lCreate(7); }, 0.5f, 0, 0, "schedulerKey3");
			}
			else if (score >= 3300 && score <= 4000) {
				this->unschedule(schedule_selector(EnemyLayer::enemyCreate));
				this->schedule([&](float dt) {enemy_rCreate(7); }, 0.5f, 0, 0, "schedulerKey4");
			}
			else if (score >= 4500 && score <= 5100) {
				this->schedule([&](float dt) {enemy_xCreate1(4); enemy_xCreate2(4); }, 0.5f, 0, 0, "schedulerKey5");
			}
			else if (score >= 6000 && score <= 6600) {
				this->schedule([&](float dt) {enemy_xCreate1(5); enemy_xCreate2(5); }, 0.5f, 0, 0, "schedulerKey6");
			}
			else if (score >= 7000 && score <= 8000) {
				this->unschedule(schedule_selector(EnemyLayer::enemyCreate));
				this->schedule([&](float dt) {enemy_lCreate(6); enemy_rCreate(6); }, 0.5f, 0, 0, "schedulerKey7");
			}
			break;

		default:
			break;
		}
	}
}

//敌机火控：
void EnemyLayer::takeFire(float delta)
{
	auto visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();
	auto hero_position = HeroPlaneLayer::getHeroPointer()->getPosition();
	for (auto it = enemyList.begin(); it != enemyList.end(); it++)
	{
	auto enemy = *it;
	auto enemy_position = enemy->getPosition();
		//auto enemy_position = EnemyLayer::getEnemyPosition();

		if (enemy->isRunning() && enemy_position.y > hero_position.y) {
			//生成子弹精灵  
			auto enemy_bullet = Sprite::create("bullet2.png");
			enemy_bullet->setTag(6);
			auto enemyBody_bullet = PhysicsBody::createBox(enemy_bullet->getContentSize());
			enemyBody_bullet->setContactTestBitmask(0x0003);
			enemyBody_bullet->setCategoryBitmask(0x0002);
			enemyBody_bullet->setCollisionBitmask(0x0001);
			enemyBody_bullet->setGravityEnable(false);
			enemy_bullet->setPhysicsBody(enemyBody_bullet);
			enemy_bullet->setPosition(Vec2(enemy_position.x, enemy_position.y));
			this->addChild(enemy_bullet);

			float distance_x = hero_position.x - enemy_position.x;
			float distance_y = hero_position.y - enemy_position.y;
			//速度 时间
			float speed = 100;
			float distance = sqrt(distance_x * distance_x + distance_y * distance_y);
			float time = distance / speed;

			auto Move = MoveTo::create(time, Vec2(hero_position));
			auto actionDone = CallFuncN::create(CC_CALLBACK_1(EnemyLayer::enemyBulletRemove, this));
			Sequence* sequence = Sequence::create(Move, actionDone, nullptr);
			enemy_bullet->runAction(sequence);
			}
		}
}

void EnemyLayer::enemyBulletRemove(Node* pNode) {
	if (NULL == pNode) {
		return;
	}
	Sprite* bullet = (Sprite*)pNode;
	bullet->removeFromParentAndCleanup(true);
	this->removeChild(bullet, true);
}

cocos2d::Vector<EnemySprite *> EnemyLayer::getEnemyList()
{
	return  enemyList;
}

void EnemyLayer::judgeDamage(Node * pNode, int type)
{
	if (NULL == pNode) {
		return;
	}
	//EnemySprite * enemy_plane = (EnemySprite *)pNode;
	//int hp_val = enemy_plane->getHPValue();
	//if (hp_val <= 0) {
	//	enemy_plane->removeFromParentAndCleanup(true);
	//	this->enemyList.eraseObject(enemy_plane);
	//}
}