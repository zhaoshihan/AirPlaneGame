#pragma once
#ifndef _HERO_PLANE_SPRITE_H_
#define _HERO_PLANE_SPRITE_H_

#include <string>
#include "cocos2d.h"

using namespace cocos2d;

class HeroPlaneSprite : public cocos2d::Sprite {
public:

	static HeroPlaneSprite* getInstance();

	int getHp() {
		return hp;
	}

private:
	int hp;
};

#endif