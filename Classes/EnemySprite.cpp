#include "EnemySprite.h"

#include <cstring>
static EnemySprite * enemy_sprite_pointer = nullptr;

EnemySprite* EnemySprite::createEnemySprite(int num)
{
	auto string = cocos2d::__String::createWithFormat("enemy%d.png", num); //这两句只是为了规避case初始化错误，无实意
	switch (num){
	case 1:
		enemy_sprite_pointer = EnemySprite::create("enemy1.png");
		createEnemyBody();
		//enemy_sprite_pointer->hp_val = 100; //第一类敌机生命值,下同
		return enemy_sprite_pointer;
		break;

	case 2:
		enemy_sprite_pointer = EnemySprite::create("enemy2.png");
		createEnemyBody();
		return enemy_sprite_pointer;
		break;

	case 3:
		enemy_sprite_pointer = EnemySprite::create("enemy3.png");
		createEnemyBody();
		return enemy_sprite_pointer;
		break;

	case 4:
		enemy_sprite_pointer = EnemySprite::create("enemy4.png");
		createEnemyBody();
		return enemy_sprite_pointer;
		break;

	case 5:
		enemy_sprite_pointer = EnemySprite::create("enemy5.png");
		createEnemyBody();
		return enemy_sprite_pointer;
		break;

	case 6:
		enemy_sprite_pointer = EnemySprite::create("enemy6.png");
		createEnemyBody();
		return enemy_sprite_pointer;
		break;

	case 7:
		enemy_sprite_pointer = EnemySprite::create("enemy7.png");
		createEnemyBody();
		return enemy_sprite_pointer;
		break;

	case 8:
		enemy_sprite_pointer = EnemySprite::create("enemy8.png");
		createEnemyBody();
		return enemy_sprite_pointer;
		break;

	default:
		break;
	}
}

void EnemySprite::createEnemyBody()
{
	auto enemyBody = PhysicsBody::createBox(enemy_sprite_pointer->getContentSize());        //创建物理实体
	enemyBody->setContactTestBitmask(0x0003);
	enemyBody->setCategoryBitmask(0x0002);
	enemyBody->setCollisionBitmask(0x0001);
	enemyBody->setGravityEnable(false);
	enemy_sprite_pointer->setPhysicsBody(enemyBody);
}

//重写CCSprite::create(), 使其返回特定的子类型EnemySprite*
EnemySprite* EnemySprite::create(const std::string& filename)
{
	EnemySprite *myEnemySprite = new (std::nothrow) EnemySprite();
	if (myEnemySprite && myEnemySprite->initWithMyParams(filename))
	{
		myEnemySprite->autorelease();
		return myEnemySprite;
	}
	CC_SAFE_DELETE(myEnemySprite);
	return nullptr;
}

bool EnemySprite::initWithMyParams(const std::string& filename)
{
	if (!Sprite::initWithFile(filename)) {
		// failed to init with super class, bail out 
		return false;
	}
	return true;
}