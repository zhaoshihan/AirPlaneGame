#pragma execution_character_set("utf-8")
#include "GameScene.h"
#include "EnemyLayer.h"
#include "HeroPlaneLayer.h"
#include "SimpleAudioEngine.h"
#include "BulletLayer.h"
#include "BgLayer.h"
#include "BossLayer.h"
#include "GameControl.h"
#include "stage.h"
#include "GameScene2.h"
#include "BonusLayer.h"

USING_NS_CC;
using namespace CocosDenshion;
static EnemyLayer* enemy_layer_pointer = nullptr;
Scene* GameScene::createScene()
{
	auto scene = Scene::createWithPhysics();
	auto layer = GameScene::create();
	scene->addChild(layer);
	return scene;
}

bool GameScene::init() {
	//////////////////////////////
	// 1. super init first
	if (!Scene::init())
	{
		return false;
	}
	//关卡1的背景音乐
	auto Bgm2 = SimpleAudioEngine::getInstance();
	Bgm2->preloadBackgroundMusic("bgMusic2.wav");
	Bgm2->playBackgroundMusic("bgMusic2.wav", true);
	Bgm2->setBackgroundMusicVolume(0.5);
	//²åÈë±³¾°
	auto bg_layer = BgLayer::create();
	this->addChild(bg_layer, 0);

	//²åÈëÖ÷½Ç·É»ú
	auto hero_plane_layer = HeroPlaneLayer::create();
	this->addChild(hero_plane_layer, 1);

	//²åÈë×Óµ¯
	auto bullet_layer = BulletLayer::create();
	this->addChild(bullet_layer, 1);

	//²åÈëµÐ»ú
	enemy_layer_pointer = EnemyLayer::create();
	this->addChild(enemy_layer_pointer, 1);

	auto Boss_layer = BossLayer::create();
	this->addChild(Boss_layer, 1);

	auto bonus_layer = BonusLayer::create();
	this->addChild(bonus_layer, 1);

	auto Game_Control = GameControl::create();
	this->addChild(Game_Control, 2);

	return true;

}

void GameScene::onEnter()
{
	Scene::onEnter();            //注意层的生命周期相关的函数一定要先调用父类的，否则会无效。
	
	auto listener = EventListenerPhysicsContact::create();                //创建一个监听器

	listener->onContactBegin = [=](PhysicsContact& contact)        //这里使用了个lambda，可以理解为匿名函数
	{
		auto spriteA = (Sprite *)contact.getShapeA()->getBody()->getNode();                //获取到节点是我们最关心的事
		auto spriteB = (Sprite *)contact.getShapeB()->getBody()->getNode();
		if (spriteA!=nullptr&&spriteB!=nullptr) {
			int tag1 = spriteA->getTag();
			int tag2 = spriteB->getTag();
			Vec2 vec1 = spriteA->getPosition();
			Vec2 vec2 = spriteB->getPosition();
			/*现写明所用tag值如下：
			我机本身：3；
			我机子弹：4；
			敌机本身：5；
			敌机子弹：6；
			生命道具包：9；
			清屏道具包：11；
			Boss本身: 7;
			Boss子弹: 13,14;
			*/
			//敌机和子弹碰撞
			if (tag1 * tag2 == 20)  //敌机5 子弹4 我机3
			{
				stage::score += 100;
				//音乐添加
				//加分，如果是104则是小敌机500分，105是大敌机1000分
				//启动粒子特效
				auto * system = ParticleSystemQuad::create("particle_texture.plist");    //使用自定义的粒子特效，就一个以plict为后缀的xml文件

				if (tag1 == 5)
				{
					//移除敌机和子弹
					spriteA->removeFromParent();
					spriteB->removeFromParent();
					system->setPosition(vec1);
					//启动动画
					this->planeBomb(vec1, tag1);
				}
				else
				{
					spriteA->removeFromParent();
					spriteB->removeFromParent();

					//启动动画
					system->setPosition(vec2);
					this->planeBomb(vec2, tag2);
				}
			}

			//Boss与子弹碰撞
			else if (tag1 * tag2 == 28) {
				stage::BossHp -= 200;
				auto * system = ParticleSystemQuad::create("particle_texture.plist");
				if (stage::BossHp <= 0) {
					stage::score += 1000;
					if (tag1 == 7) {
						stage::x = 1;
						spriteA->removeFromParent();
						spriteB->removeFromParent();
						this->planeBomb(vec1, tag1);
						system->setPosition(vec1);
					}
					else {
						stage::x = 1;
						spriteA->removeFromParent();
						spriteB->removeFromParent();
						this->planeBomb(vec2, tag2);
						system->setPosition(vec2);
					}
				}
			}

			//敌机与我机碰撞
			else if (tag1 * tag2 == 15)
			{
				//stage::Hp -= 50;
				//修改游戏状态为结束状态3

				    //停止所有的定时器(参数控制)
				if (tag1 == 3)        //游戏结束逻辑
				{
					this->planeBomb(vec2, tag2);
					this->planeBomb(vec1, tag1);
					spriteB->removeFromParent();
				}
				else
				{
					this->planeBomb(vec1, tag1);
					this->planeBomb(vec2, tag2);
					spriteA->removeFromParent();
				}
				//使用UserDefault存储些用户数据分数，用法比较简单，map的使用方法，
				UserDefault * userDefault = UserDefault::getInstance();
				int topScore = userDefault->getIntegerForKey("topScore");
				if (topScore < stage::score)
				{
					userDefault->setIntegerForKey("topScore", stage::score);
				}
				else
					userDefault->setIntegerForKey("topScore", topScore);
				userDefault->setIntegerForKey("currentScore", stage::score);
			}

			//敌机子弹与我机碰撞
			else if (tag1*tag2 == 18) {
				//stage::Hp -= 10;
				if (tag1 == 3) {
					this->planeBomb(vec1, tag1);
					spriteB->removeFromParent();
				}
				else {
					this->planeBomb(vec2, tag2);
					spriteA->removeFromParent();
				}
			}

			//Boss子弹与我机碰撞
			else if(tag1*tag2==39||tag1*tag2==42) {
				//stage::Hp -= 20;
				if (tag1 == 3) {
					this->planeBomb(vec1, tag1);
					spriteB->removeFromParent();
				}
				else {
					this->planeBomb(vec2, tag2);
					spriteA->removeFromParent();
				}
			}

			//我机吃生命包
			else if (tag1*tag2 == 27) {
				stage::Hp = 100;
				if (tag1 == 3) {
					spriteB->removeFromParent();
				}
				else {
					spriteA->removeFromParent();
				}
			}

			//我机吃清屏包
			else if (tag1*tag2 == 33) {
				int enemy_num = enemy_layer_pointer->getChildrenCount();
				stage::score += 100 * enemy_num;
				enemy_layer_pointer->removeAllChildrenWithCleanup(true);
				enemy_layer_pointer->getEnemyList().clear();
				if (tag1 == 3) {
					spriteB->removeFromParent();
				}
				else {
					spriteA->removeFromParent();
				}
			}

			else {}        //这里处理了敌机和敌机碰撞的bug
		}

		return true;
	};

	//注册监听器
	EventDispatcher * eventDispatcher = Director::getInstance()->getEventDispatcher();
	eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);

}

void GameScene::planeBomb(Vec2 vec, int tag)//爆炸效果
{
	float timeDelay = 0.1;
	Vector<SpriteFrame*> animationframe;
	if (tag == 5)  //只保留这个
	{
		for (int i = 1; i < 7; i++)
		{
			auto string = cocos2d::__String::createWithFormat("boom%d.png", i);
			SpriteFrame * sf = SpriteFrame::create(string->getCString(), Rect(0, 0, 38, 38));
			animationframe.pushBack(sf);
		}
	}

	else if (tag == 7)  //Boss1动画帧
	{
		for (int i = 1; i < 7; i++)
		{
			auto string = cocos2d::__String::createWithFormat("BoomX%d.png", i);
			SpriteFrame * sf = SpriteFrame::create(string->getCString(), Rect(0, 0, 105, 105));
			animationframe.pushBack(sf);
		}
	}
	else            //我机爆炸就游戏结束了，给个潇洒的特写，将动画延迟到0.5秒一帧
	{
		timeDelay = 0.5;
		for (int i = 1; i < 7; i++)
		{
			auto string = cocos2d::__String::createWithFormat("boom%d.png", i);
			SpriteFrame * sf = SpriteFrame::create(string->getCString(), Rect(0, 0, 38, 38));
			animationframe.pushBack(sf);
		}
	}
	Animation * ani = Animation::createWithSpriteFrames(animationframe, timeDelay);
	auto blanksprite = Sprite::create();
	blanksprite->setTag(tag);
	//参数中的回调函数会在动画播放完后调用
	Action * act = Sequence::create(Animate::create(ani), CCCallFuncN::create(blanksprite, callfuncN_selector(GameScene::bombRemove)), NULL);
	this->addChild(blanksprite);
	blanksprite->setPosition(vec);
	blanksprite->runAction(act);
}

//移除动画
void GameScene::bombRemove(Node * sprite)//删除自己
{
	sprite->removeFromParentAndCleanup(true);
	if (sprite->getTag() == 3)            //当移除了我机爆炸的动画，那就是游戏结束了。
	{
		/*SimpleAudioEngine::getInstance()->stopBackgroundMusic("sounds/game_music.wav");*/
		//游戏结束逻辑
	}
}

