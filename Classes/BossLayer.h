#pragma once
#ifndef _Boss_Layer_
#define _Boss_Layer_

#include"cocos2d.h"
using namespace cocos2d;

class BossLayer :public cocos2d::Layer {
public:
	virtual bool init();
	virtual void update(float); //�ܵ���Boss���ຯ����ʡȥ������ʱ�������ж�

	void BossCreate(int); //���ֱ�ʾÿ�ص�Boss

	void BossMove(float); //һ����Boss�����ƶ���ʽ
	void BossMove2(float); //������Boss�����ƶ���ʽ

	void bossTakeFire(float);
	void bossBulletRemove(Node *);
    CREATE_FUNC(BossLayer);
	void bulletCreate(float);

	void createBossBody();

private:
	bool isRight = true; //Ĭ��Boss��ʼʱ�����ƶ�
	Sprite * Boss_pointer=NULL;
};

#endif