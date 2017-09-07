#pragma once
#ifndef __BG_LAYER_H__
#define __BG_LAYER_H__

#include "cocos2d.h"

class BgLayer :public cocos2d::Layer
{
public:
	void bg1_Move(float);
	void bg2_Move(float);
	//重写init()方法
	virtual bool init();

	//通过宏函数重写create()方法  
	//宏函数CREATE_FUNC()可在cocos源文件CCPlatformMacros.h中看到 
	CREATE_FUNC(BgLayer);

};

#endif //__BG_LAYER_H__