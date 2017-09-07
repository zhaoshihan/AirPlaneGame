#ifndef _ENEMY_SPRITE_H_
#define  _ENEMY_SPRITE_H_

#include "cocos2d.h"

using namespace cocos2d;

class EnemySprite : public cocos2d::Sprite
{
public:
	static EnemySprite* create(const std::string & filename);
	bool initWithMyParams(const std::string& filename); //这两个函数负责subclass原先的CCSprite::create();

	static EnemySprite* createEnemySprite(int);
	static void createEnemyBody(); //所有的敌机都使用同一种物理属性
	int getHPValue();

private:
	int hp_val;
};
#endif	//_ENEMY_SPRITE_H_
