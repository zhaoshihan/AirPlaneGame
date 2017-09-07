#pragma once
#ifndef __HERO_PLANE_LAYER_H__
#define __HERO_PLANE_LAYER_H__

#include "HeroPlaneSprite.h"
#include "cocos2d.h"

class HeroPlaneLayer :public cocos2d::Layer {
public:
	virtual bool init();
	CREATE_FUNC(HeroPlaneLayer);
	void controlPlaneByKeyboard(int i);
	virtual void update(float delta);

	static HeroPlaneSprite* getHeroPointer();

private:
	int key[4] = { 0,0,0,0 };
	static HeroPlaneSprite* hero_plane_sprite;
};

#endif //__HERO_PLANE_LAYER_H__