#pragma once
#ifndef __BG_LAYER_H__
#define __BG_LAYER_H__

#include "cocos2d.h"

class BgLayer :public cocos2d::Layer
{
public:
	void bg1_Move(float);
	void bg2_Move(float);
	//��дinit()����
	virtual bool init();

	//ͨ���꺯����дcreate()����  
	//�꺯��CREATE_FUNC()����cocosԴ�ļ�CCPlatformMacros.h�п��� 
	CREATE_FUNC(BgLayer);

};

#endif //__BG_LAYER_H__