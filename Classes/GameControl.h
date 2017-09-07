#pragma once
#ifndef _GAME_CONTROL_H_
#define _GAME_CONTROL_H_

#include "cocos2d.h"

using namespace cocos2d;

class GameControl : public cocos2d::Layer {
public:
	CREATE_FUNC(GameControl);
	virtual bool init();
	void update(float);
	void pauseMenuCallback(Ref *);
	void resumeMenuCallback(Ref *);
	void restartMenuCallback(Ref *);
	void backMenuCallback(Ref *);
	void nextMenuCallback(Ref *);
	void passMenu(float);
	void gameOver(float);
private:
	ProgressTimer *life_bar;
	Label *score2;
	Menu *menu_back;
	Menu *menu_back2;
	Menu *menu_back3;
	Menu *menu_restart;
	Menu *menu_restart2;
	Menu *menu_pause;
	Menu *menu_resume;
	Menu *menu_next;
	MenuItemSprite *item_back;
	MenuItemSprite *item_back2;
	MenuItemSprite *item_back3;
	MenuItemSprite *item_restart;
	MenuItemSprite *item_restart2;
	MenuItemSprite *item_pause;
	MenuItemSprite *item_resume;
	MenuItemSprite *item_next;
	
};

#endif