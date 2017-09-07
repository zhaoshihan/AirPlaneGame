#ifndef _ENEMY_SPRITE_H_
#define  _ENEMY_SPRITE_H_

#include "cocos2d.h"

using namespace cocos2d;

class EnemySprite : public cocos2d::Sprite
{
public:
	static EnemySprite* create(const std::string & filename);
	bool initWithMyParams(const std::string& filename); //��������������subclassԭ�ȵ�CCSprite::create();

	static EnemySprite* createEnemySprite(int);
	static void createEnemyBody(); //���еĵл���ʹ��ͬһ����������
	int getHPValue();

private:
	int hp_val;
};
#endif	//_ENEMY_SPRITE_H_
