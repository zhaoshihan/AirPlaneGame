#pragma once
#ifndef __SCENE1_H__
#define __SCENE1_H__
#include "cocos2d.h"

USING_NS_CC;

class Scene1 :public cocos2d::Layer {
public:
	virtual bool init();
	static cocos2d::Scene* scene();
	void menuGoToGameScene(Ref*);
	void menuGoToStage(Ref*);
	void menuEnd(Ref*);
	CREATE_FUNC(Scene1);

};
#endif // !__SCENE1_H__