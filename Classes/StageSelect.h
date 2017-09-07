#pragma once
#ifndef __STAGE_SELECT_H__
#define __STAGE_SELECT_H__

#include "cocos2d.h"

class StageSelect : public cocos2d::Scene
{
public:
	virtual bool init();

	static cocos2d::Scene* createScene();

	CREATE_FUNC(StageSelect);

	void GoToStage1(Ref*);

	void GoToStage2(Ref*);

	void GoToStage3(Ref*);

	void back(Ref*);
};
#endif // __STAGE_SELECT_H__