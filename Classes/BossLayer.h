#pragma once
#ifndef _Boss_Layer_
#define _Boss_Layer_

#include"cocos2d.h"
using namespace cocos2d;

class BossLayer :public cocos2d::Layer {
public:
	virtual bool init();
	virtual void update(float); //总调度Boss各类函数，省去各个计时器各自判断

	void BossCreate(int); //数字表示每关的Boss

	void BossMove(float); //一二关Boss具体移动方式
	void BossMove2(float); //第三关Boss具体移动方式

	void bossTakeFire(float);
	void bossBulletRemove(Node *);
    CREATE_FUNC(BossLayer);
	void bulletCreate(float);

	void createBossBody();

private:
	bool isRight = true; //默认Boss开始时向右移动
	Sprite * Boss_pointer=NULL;
};

#endif