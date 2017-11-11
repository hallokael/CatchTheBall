#include "MenuScene.h"
#include "GameScene.h"
#include "SuScene.h"
#include "ThrowScene.h"
#pragma once
Scene* MenuScene::createScene()
{
	auto scene = Scene::create();

	auto layer = MenuScene::create();
	scene->addChild(layer);

	return scene;
}

bool MenuScene::init()
{
	auto listener1 = EventListenerKeyboard::create();
	listener1->onKeyReleased = [](EventKeyboard::KeyCode key, Event*)
	{
		if (EventKeyboard::KeyCode::KEY_RETURN == key || EventKeyboard::KeyCode::KEY_ESCAPE == key || EventKeyboard::KeyCode::KEY_BACKSPACE == key)
		{
			Director::getInstance()->end();
		}
	};
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener1, this);
	dispatcher = this->getEventDispatcher();
	listener = EventListenerTouchOneByOne::create();
	listener->onTouchBegan = CC_CALLBACK_2(MenuScene::onTouchBegan, this);
	// 触摸开始  
	listener->onTouchMoved = CC_CALLBACK_2(MenuScene::onTouchMoved, this);
	// 触摸移动 
	dispatcher->addEventListenerWithSceneGraphPriority(listener, this);
	if (!Layer::init())
	{
		return false;
	}

	initBG();
	initMenu();
	scheduleUpdate(); 
	return true;
}

void MenuScene::initBG()
{
	auto spr = Sprite::create("BG.jpg");
	spr->setScaleX(Director::getInstance()->getWinSize().width/1795); 
	spr->setScaleY(Director::getInstance()->getWinSize().height/2320); 
	spr->setPosition(Point(Director::getInstance()->getWinSize().width / 2, Director::getInstance()->getWinSize().height / 2));
	this->addChild(spr);

	mypat = CCParticleSystemQuad::create("NewParticle2_1.plist");
	this->addChild(mypat);

	// 流星精灵Sprtie     
	star = Sprite::create("ball.png");
	// 流星拖尾MotionStreak  
	streak = MotionStreak::create(0.5f, 1, 28, Color3B::WHITE, "steak.png");

	//待定
	//streak->setFastMode(false); 
	//streak = MotionStreak::create(0.5f, 1, 10, Color3B::RED, "ball.png");  
	streak->setPosition(star->getPosition());
	// 设置拖尾streak的位置  
	this->addChild(streak);

	star->setAnchorPoint(Point(0.5, 0.5));
	streak->setAnchorPoint(Point(0.5, 0.5));
	mypat->setAnchorPoint(Point(0.5, 0.5));
	star->setPosition(Director::getInstance()->getWinSize().width / 2+100, Director::getInstance()->getWinSize().height / 2+200);
	this->addChild(star);
	this->addChild(streak);
}
void MenuScene::initMenu()
{
	auto item_0 = MenuItemImage::create("PZ.png", "PZZ.png", CC_CALLBACK_1(MenuScene::menuCallback, this));
	auto item_1 = MenuItemImage::create("SC.png", "SCC.png", CC_CALLBACK_1(MenuScene::menuCallback, this));
	auto item_2 = MenuItemImage::create("SZ.png", "SZS.png", CC_CALLBACK_1(MenuScene::menuCallback, this));
	auto item_3 = MenuItemImage::create("CJ.png", "CJJ.png", CC_CALLBACK_1(MenuScene::menuCallback, this));
	auto item_4 = MenuItemImage::create("TZ.png", "TZZ.png", CC_CALLBACK_1(MenuScene::menuCallback, this));
	item_0->setTag(TAG_GAME);
	item_1->setTag(TAG_SU);
	item_2->setTag(TAG_OPTION);
	item_3->setTag(TAG_ACH);
	item_4->setTag(TAG_THROW);

	auto menu = Menu::create(item_0, item_1, item_4, NULL);
	menu->alignItemsVerticallyWithPadding(60);
	this->addChild(menu);
}
void MenuScene::menuCallback(Ref *sender)
{
	auto item = (MenuItem*)sender;

	switch (item->getTag())
	{
	case TAG_GAME:
	{
		auto scene = TransitionFadeTR::create(0.5, GameScene::createScene());
		Director::getInstance()->replaceScene(scene);
	}
		break;
	case TAG_SU:
	{
		auto scene = TransitionFadeTR::create(0.5, SuScene::createScene());
		Director::getInstance()->replaceScene(scene);
	}
		break;
	case TAG_THROW:
	{
		auto scene = TransitionFadeTR::create(0.5, ThrowScene::createScene());
		Director::getInstance()->replaceScene(scene);
	}
		break; 
	}
}
bool MenuScene::onTouchBegan(Touch* pTouch, Event* pEvent)
{

	// 获取触摸点位置    
	Vec2 pos = pTouch->getLocation();
	// 设置位置    
	star->setPosition(pos);


	// 删除所有活动条带段  
	//streak->reset();
	return true;
}
void MenuScene::onTouchMoved(Touch* pTouch, Event* pEvent)
{

	Vec2 pos = pTouch->getLocation();
	// 触摸移动的偏移量   
	Vec2 delta = pTouch->getDelta();
	// 设置位置    
	star->setPosition(star->getPosition() + delta);
}
void MenuScene::update(float dt)
{
	streak->setPosition(star->getPosition());
	mypat->setPosition(star->getPosition());
}
