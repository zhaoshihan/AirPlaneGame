#pragma once
#ifndef _Enemy_Layer_
#define _Enemy_Layer_

#include"cocos2d.h"
#include "EnemySprite.h"
using namespace cocos2d;

class EnemyLayer :public cocos2d::Layer {
public:
	virtual bool init();
	//void enemyMove(float);
	virtual void update(float delta); //重写update,调度各类飞机产生

	void enemyCreate(float);  //直线下落
	void enemy_lCreate(int); //左贝塞尔曲线
	void enemy_rCreate(int); 
	void enemy_xCreate1(int); //左上到右下斜线
	void enemy_xCreate2(int);
	void enemy_vCreate(int);//阵列


	void enemyRemove(Node*); //这是敌机action结束操作
	void takeFire(float);
	void enemyBulletRemove(Node *);

	void judgeDamage(Node *, int); //这是敌机碰撞伤害操作

	cocos2d::Vector<EnemySprite *> getEnemyList();
	CREATE_FUNC(EnemyLayer);

private:
	cocos2d::Vector<EnemySprite *> enemyList; //初步定是按敌机类型储存，是不是占用空间太多呢？
};

#endif