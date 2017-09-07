#pragma once
#ifndef _Bullet_Layer_
#define _Bullet_Layer_

#include <string>
#include "cocos2d.h"
using namespace cocos2d;

class BulletLayer :public cocos2d::Layer {
public:
	virtual bool init();
	CREATE_FUNC(BulletLayer);

	virtual void update(float delta);

	void bulletCreate(float);
	void bulletMove(float);

private:
	cocos2d::Vector<cocos2d::Sprite *> bulletList;
	int s = 0;//判断我机子弹是否产生的参数
};

#endif