#pragma once
#ifndef __GAME_SCENE2_H__
#define __GAME_SCENE2_H__

#include "cocos2d.h"

class GameScene2 : public cocos2d::Scene
{
public:
	static cocos2d::Scene* createScene();

	virtual bool init();
	virtual void onEnter();
	void planeBomb(cocos2d::Vec2 vec, int tag);    //飞机爆炸动画
	void bombRemove(Node * sprite); //飞机爆炸动画播放完之后的回调函数
	
	// implement the "static create()" method manually
	CREATE_FUNC(GameScene2);

};
#endif // __GAME_SCENE2_H__
