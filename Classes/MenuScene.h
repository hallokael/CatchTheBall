#ifndef __MENU_SCENE_H__
#define __MENU_SCENE_H__

#include "cocos2d.h"

#pragma once
USING_NS_CC;

#define TAG_GAME 1
#define TAG_SU 2
#define TAG_OPTION 3
#define TAG_ACH 4
#define TAG_THROW 5

class MenuScene : public Layer
{
public:

double PTM_RATIO = 30;
int Gra = -100;
cocos2d::Size winSize;
	static Scene* createScene();
	cocos2d::EventListenerTouchOneByOne* listener;
	bool onTouchBegan(Touch* pTouch, Event* pEvent);
	void onTouchMoved(Touch* pTouch, Event* pEvent);
	virtual bool init();
	void update(float dt) override;
	CREATE_FUNC(MenuScene);

	void initBG();
	void initMenu();
	void Re1_1(); 
	void menuCallback(Ref *sender);
	Sprite* spr1;
	Sprite* spr2;
	Sprite* spr3;
	Sprite* spr4;
	ParticleSystem* mypat;
	cocos2d::EventDispatcher* dispatcher;
private:
	Sprite* star;
	// Á÷ÐÇ¾«Áé    
	MotionStreak* streak;
	// ÍÏÎ²
};

#endif