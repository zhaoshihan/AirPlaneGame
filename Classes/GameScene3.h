#pragma once
#ifndef __GAME_SCENE3_H__
#define __GAME_SCENE3_H__

#include "cocos2d.h"

class GameScene3 : public cocos2d::Scene
{
public:
	static cocos2d::Scene* createScene();

	virtual bool init();
	virtual void onEnter();
	void planeBomb(cocos2d::Vec2 vec, int tag);    //�ɻ���ը����
	void bombRemove(Node * sprite);                         //�ɻ���ը����������֮��Ļص�����
															// implement the "static create()" method manually
	CREATE_FUNC(GameScene3);

};
#endif // __GAME_SCENE3_H__