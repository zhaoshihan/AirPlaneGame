#ifndef _BONUS_LAYER_H_
#define  _BONUS_LAYER_H_

#include "cocos2d.h"

using namespace cocos2d;

class BonusLayer : public cocos2d::Layer
{
public:
	virtual bool init();
	void createHpBonus();
	void createClearBonus();
	void bonusRemove(Node *);
	CREATE_FUNC(BonusLayer);

	void createBonusBody();
};
#endif	//_BONUS_LAYER_H_
