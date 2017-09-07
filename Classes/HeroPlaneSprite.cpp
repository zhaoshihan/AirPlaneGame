#include "HeroPlaneSprite.h"
#include "HeroPlaneLayer.h"
using namespace cocos2d;

static HeroPlaneSprite *hero_plane_sprite = nullptr;

HeroPlaneSprite* HeroPlaneSprite::getInstance() {
	auto plane = HeroPlaneSprite::create("hero1.png");
	hero_plane_sprite = static_cast<HeroPlaneSprite*>(plane);
	plane->setTag(3);
	auto planeBody = PhysicsBody::createBox(plane->getContentSize());
	planeBody->setContactTestBitmask(0x0003);            //Åö×²²âÊÔÑÚÂë
	planeBody->setCategoryBitmask(0x0001);                //Àà±ðÑÚÂë
	planeBody->setCollisionBitmask(0x0002);                 //Åö×²ÑÚÂë
	planeBody->setGravityEnable(false);                          //ÉèÖÃÖØÁ¦ÎÞÐ§
	plane->setPhysicsBody(planeBody);

	return hero_plane_sprite;
}