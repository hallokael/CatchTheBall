#include "MenuScene.h"
#include "ThrowScene.h"
#include <math.h>
#define PI acos( -1.0 )
USING_NS_CC;
void ThrowScene::Tech()
{
	auto spr = Sprite::create("bai.png");
	spr->setScale(5);
	spr->setPosition(winSize.width / 2, winSize.height / 2);
	this->addChild(spr);
	auto label_tech = Label::createWithSystemFont
		("投掷模式：\n拖动屏幕移动并释放小球，之后拖动屏幕划出木棒使小球消灭所有黑色木棒并不碰撞四周墙壁.\n右上角显示的是本关允许使用的木棒数量\n每章通过五关即可进入下一章", "", 40, Size(500, 400));
	label_tech->setPosition(winSize.width / 2, winSize.height / 2);
	label_tech->setColor(Color3B::BLACK);
	this->addChild(label_tech);
	auto item_0 = MenuItemImage::create("ZDL.png", "ZDLL.png", CC_CALLBACK_1(ThrowScene::First, this));
	Menu *menu = Menu::create(item_0, NULL);
	menu->alignItemsHorizontallyWithPadding(50);
	menu->setPosition(Point(Director::getInstance()->getWinSize().width / 2, Director::getInstance()->getWinSize().height * 1 / 4));
	menu->setVisible(true);
	this->addChild(menu);
}
Scene* ThrowScene::createScene()
{
	// 'scene' is an autorelease object
	auto scene = Scene::create();

	// 'layer' is an autorelease object
	auto layer = ThrowScene::create();

	// add layer as a child to scene
	scene->addChild(layer);

	// return the scene
	return scene;
}
bool ThrowScene::init()
{
	if (!Layer::init())
		return false;
	auto listener1 = EventListenerKeyboard::create();
	listener1->onKeyReleased = [this](EventKeyboard::KeyCode key, Event*)
	{
		if (EventKeyboard::KeyCode::KEY_RETURN == key || EventKeyboard::KeyCode::KEY_ESCAPE == key || EventKeyboard::KeyCode::KEY_BACKSPACE == key)
		{
			if (HaveChoose)
			{
				auto scene = TransitionFadeTR::create(0.5, ThrowScene::createScene());
				Director::getInstance()->replaceScene(scene);
			}
			else
			{
				auto scene = TransitionFadeTR::create(0.5, MenuScene::createScene());
				Director::getInstance()->replaceScene(scene);
			}
		}
	};
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener1, this);
	winSize = Director::getInstance()->getWinSize();
	chapter = UserDefault::getInstance()->getIntegerForKey("chapter", 1);
	//if (chapter < 1)
	//{
	//	UserDefault::getInstance()->setIntegerForKey("chapter", 1);
	//	UserDefault::getInstance()->flush();

	//}
	char s[15] = "chapter";
	char sp[5];
	sprintf(sp, "%d", chapter);
	strcat(s, sp);
	WinNum = UserDefault::getInstance()->getIntegerForKey(s, 0);
	// 注册单点触摸  
	dispatcher = this->getEventDispatcher();
	listener = EventListenerTouchOneByOne::create();
	listener->onTouchBegan = CC_CALLBACK_2(ThrowScene::onTouchBegan, this);
	// 触摸开始  
	listener->onTouchMoved = CC_CALLBACK_2(ThrowScene::onTouchMoved, this);
	listener->onTouchEnded = CC_CALLBACK_2(ThrowScene::onTouchEnded, this);
	// 触摸移动 
	dispatcher->addEventListenerWithSceneGraphPriority(listener, this);




	if (chapter < 1)
		chapter = 1;
	if (chapter > 6)
		chapter = 6;
	auto spr = Sprite::create("BG.jpg");
	spr->setScaleX(Director::getInstance()->getWinSize().width/1795); 
	spr->setScaleY(Director::getInstance()->getWinSize().height/2320); 
	spr->setPosition(Point(Director::getInstance()->getWinSize().width / 2, Director::getInstance()->getWinSize().height / 2));
	this->addChild(spr);
	auto spr1 = Sprite::create("bai.png", Rect(0, 0, 200, 200));
	spr1->setPosition(Point(Director::getInstance()->getWinSize().width / 2, Director::getInstance()->getWinSize().height / 2));
	spr1->setScale(5);
	this->addChild(spr1);
	//auto spr3 = Sprite::create("JT.png");
	////spr3->setColor(Color3B(255, 100, 255));
	//spr3->setPosition(Point(Director::getInstance()->getWinSize().width*4 / 5, 
	//	Director::getInstance()->getWinSize().height * 1 / 7));
	//spr3->setScale(1);
	//this->addChild(spr3);
	auto item_JT = MenuItemImage::create("JT.png", "JTT.png", CC_CALLBACK_1(ThrowScene::menuCallback, this));
	auto item_LJT = MenuItemImage::create("LJT.png", "LJTT.png", CC_CALLBACK_1(ThrowScene::menuCallback, this));
	auto item_1 = MenuItemImage::create("1.png", "11.png", CC_CALLBACK_1(ThrowScene::menuCallback, this));
	auto item_2 = MenuItemImage::create("2.png", "22.png", CC_CALLBACK_1(ThrowScene::menuCallback, this));
	auto item_3 = MenuItemImage::create("3.png", "33.png", CC_CALLBACK_1(ThrowScene::menuCallback, this));
	auto item_4 = MenuItemImage::create("4.png", "44.png", CC_CALLBACK_1(ThrowScene::menuCallback, this));
	auto item_5 = MenuItemImage::create("5.png", "55.png", CC_CALLBACK_1(ThrowScene::menuCallback, this));
	auto item_6 = MenuItemImage::create("6.png", "66.png", CC_CALLBACK_1(ThrowScene::menuCallback, this));
	auto item_7 = MenuItemImage::create("7.png", "77.png", CC_CALLBACK_1(ThrowScene::menuCallback, this));
	auto item_8 = MenuItemImage::create("8.png", "88.png", CC_CALLBACK_1(ThrowScene::menuCallback, this));
	auto item_9 = MenuItemImage::create("9.png", "99.png", CC_CALLBACK_1(ThrowScene::menuCallback, this));
	item_1->setTag(1);
	item_2->setTag(2);
	item_3->setTag(3);
	item_4->setTag(4);
	item_5->setTag(5);
	item_6->setTag(6);
	item_7->setTag(7);
	item_8->setTag(8);
	item_9->setTag(9);
	item_JT->setTag(11);
	item_LJT->setTag(12);
	auto meJT = Menu::create(item_JT, NULL);
	this->addChild(meJT);
	meJT->setPosition(Point(Director::getInstance()->getWinSize().width * 4 / 5,
		Director::getInstance()->getWinSize().height * 1 / 7));
	meJT->setOpacity(150);
	auto meLJT = Menu::create(item_LJT, NULL);
	this->addChild(meLJT);
	meLJT->setPosition(Point(Director::getInstance()->getWinSize().width * 1 / 5,
		Director::getInstance()->getWinSize().height * 1 / 7));
	//auto menu = Menu::create(item_1, item_2, item_3, NULL);
	//menu->alignItemsHorizontallyWithPadding(50); 
	//this->addChild(menu);
	auto menuu = Menu::create(item_1, item_2, item_3, item_4, item_5, item_6, item_7, item_8, item_9, NULL);

	menuu->alignItemsInColumns(1, 2, 3, 2, 1);
	//item_5->setPosition(-5000, -5000);
	this->addChild(menuu);



	auto item_10 = MenuItemImage::create("10.png", "100.png", CC_CALLBACK_1(ThrowScene::menuCallback, this));
	item_10->setTag(10);
	auto me10 = Menu::create(item_10, NULL);



	switch (chapter)
	{
	case 0:
		numberrr = Sprite::create("0.png");
		break;
	case 1:
		numberr = Sprite::create("1.png");
		break;
	case 2:
		numberr = Sprite::create("2.png");
		break;
	case 3:
		numberr = Sprite::create("3.png");
		break;
	case 4:
		numberr = Sprite::create("4.png");
		break;
	case 5:
		numberr = Sprite::create("5.png");
		break;
	case 6:
		numberr = Sprite::create("6.png");
		break;
	}


	for (int i = 1; i <= 10; i++)
	{
		char s[15] = "chapter";
		char sp[5];
		sprintf(sp, "%d", chapter);
		strcat(s, sp);
		sprintf(sp, "%d", i);
		strcat(s, sp);
		int Have = UserDefault::getInstance()->getIntegerForKey(s, 0);
		if (!Have)
		{
			switch (i)
			{
			case 1:
			{
				item_1->setOpacity(150);
			}
				break;
			case 2:
			{
				item_2->setOpacity(150);
			}
				break;
			case 3:
			{
				item_3->setOpacity(150);
			}
				break;
			case 4:
			{
				item_4->setOpacity(150);
			}
				break;
			case 5:
			{
				item_5->setOpacity(150);
			}
				break;
			case 6:
			{
				item_6->setOpacity(150);
			}
				break;
			case 7:
			{
				item_7->setOpacity(150);
			}
				break;
			case 8:
			{
				item_8->setOpacity(150);
			}
				break;
			case 9:
			{
				item_9->setOpacity(150);
			}
				break;
			case 10:
			{
				item_10->setOpacity(150);
			}
				break;
			}
		}
	}






	//auto sa = Sprite::create("bai.png");
	//sa->setPosition(winSize.width * 1 / 2, winSize.height * 1 / 7);
	//this->addChild(sa);
	//sa->setScale(0.6);
	numberr->setPosition(winSize.width * 1 / 2, winSize.height * 1 / 7);
	this->addChild(numberr);



	if (WinNum >= 5)
	{
		auto spr2 = Sprite::create("bai.png", Rect(0, 0, 200, 200));
		spr2->setColor(Color3B(255, 120 - 20 * chapter, 255));
		spr2->setPosition(Point(Director::getInstance()->getWinSize().width / 2, Director::getInstance()->getWinSize().height * 8 / 9));
		spr2->setScale(5);
		this->addChild(spr2);
		meJT->setOpacity(255);
		this->addChild(me10);
		me10->setPosition(Point(Director::getInstance()->getWinSize().width / 2,
			Director::getInstance()->getWinSize().height * 8 / 9));
	}
	if (chapter == 1)
		meLJT->setOpacity(150);
	if (chapter == 6)
		meJT->setOpacity(150);

	return true;
}
void ThrowScene::InitGameData()
{
	ShallDestory = 0;
	WallNumber = 0;
	AllowWallNumber = 0;
	Organ = 0;
	w = 0;
	t = 0;
	go = false;


	log("sadaw");
	auto spr = Sprite::create("BG.jpg");
	spr->setScaleX(Director::getInstance()->getWinSize().width/1795); 
	spr->setScaleY(Director::getInstance()->getWinSize().height/2320); 
	spr->setPosition(Point(Director::getInstance()->getWinSize().width / 2, Director::getInstance()->getWinSize().height / 2));
	this->addChild(spr);
	prespr = Sprite::create("wall.jpg", Rect(0, 0, 100, 5));
	prespr->setAnchorPoint(Point(0.5, 0.5));
	prespr->setOpacity(100);
	if (chapter == 4)
	{
		prespr->setColor(Color3B::RED);
	}
	if (chapter == 5)
	{
		prespr->setColor(Color3B::GREEN);
	}
	if (chapter == 6)
	{
		prespr->setColor(Color3B::GRAY);
	}
	this->addChild(prespr);
	gravity.Set(0, gra); //一个向下10单位的向量，作为重力减速度，Box2D中默认的单位是秒和米  
	mWorld = new b2World(gravity); // 创建一个有重力加速度的世界  
	b2BodyDef bodyDef;
	b2BodyDef bodyDef2;
	b2CircleShape bodyShape;
	b2PolygonShape bodyShape2;
	b2FixtureDef bodyFixture;
	b2FixtureDef HFixture;
	b2Body * bottomBorder;
	b2Body * bottomBorder2;
	b2PolygonShape borderShape; // 一个方形的形状  
	b2FixtureDef borderFixture; // 一个定制器  
	b2Body * HBorder1;
	b2Body * HBorder2;
	b2BodyDef HbodyDef;
	b2BodyDef HbodyDef2;
	b2Vec2 gravity;
	mypat = CCParticleSystemQuad::create("NewParticle2_1.plist");
	this->addChild(mypat);

	// 流星精灵Sprtie     
	star = Sprite::create("ball.png");
	star->setTag(2000005);
	// 流星拖尾MotionStreak  
	streak = MotionStreak::create(0.5f, 1, 28, Color3B::WHITE, "steak.png");

	//待定
	//streak->setFastMode(false); 
	//streak = MotionStreak::create(0.5f, 1, 10, Color3B::RED, "ball.png");  
	streak->setPosition(star->getPosition());
	// 设置拖尾streak的位置  
	this->addChild(streak);
	spr1 = Sprite::create("wall.jpg", Rect(0, 0, winSize.width, 10));
	spr2 = Sprite::create("wall.jpg", Rect(0, 0, winSize.width, 10));
	spr3 = Sprite::create("wall.jpg", Rect(0, 0, 10, winSize.height));
	spr4 = Sprite::create("wall.jpg", Rect(0, 0, 10, winSize.height));

	spr1->setPosition(0, 0);
	spr1->setAnchorPoint(Point(0, 0));
	spr2->setPosition(0, winSize.height - 10);
	spr2->setAnchorPoint(Point(0, 0));

	spr3->setPosition(0, 0);
	spr3->setAnchorPoint(Point(0, 0));
	spr4->setPosition(winSize.width - 10, 0);
	spr4->setAnchorPoint(Point(0, 0));
	spr1->setTag(1);
	spr2->setTag(2);
	spr3->setTag(3);
	spr4->setTag(4);
	this->addChild(spr1);
	this->addChild(spr2);
	this->addChild(spr3);
	this->addChild(spr4);

	//一个物体的定义  
	bodyDef.type = b2_staticBody; //物体的类型，不动的，坚硬的~ 可以把这样的物体当成地面  

	//定义地板  
	bodyDef.position.Set(0, -90 / PTM_RATIO); // 地板在0，0位置  
	borderShape.SetAsBox(winSize.width / PTM_RATIO, 100 / PTM_RATIO); //设置长度和高度，这里描述的地板就像是X轴，是一条线  
	borderFixture.shape = &borderShape;
	bottomBorder = mWorld->CreateBody(&bodyDef); //在世界中创建一个物体（地面） 
	bottomBorder->CreateFixture(&borderFixture);          //定制地面的形状 


	bodyDef2.type = b2_staticBody;
	bodyDef2.position.Set(0, winSize.height / PTM_RATIO + 90.0 / PTM_RATIO);
	bottomBorder2 = mWorld->CreateBody(&bodyDef2);
	bottomBorder2->CreateFixture(&borderFixture);


	bodyShape2.SetAsBox(100 / PTM_RATIO, winSize.height / PTM_RATIO); //设置长度和高度，这里描述的地板就像是X轴，是一条线  
	HFixture.shape = &bodyShape2;

	HbodyDef.type = b2_staticBody;
	HbodyDef.position.Set(-90.0 / PTM_RATIO, 0);
	HBorder1 = mWorld->CreateBody(&HbodyDef);
	HBorder1->CreateFixture(&HFixture);


	HbodyDef2.type = b2_staticBody;
	HbodyDef2.position.Set(winSize.width / PTM_RATIO + 90.0 / PTM_RATIO, 0);
	HBorder2 = mWorld->CreateBody(&HbodyDef2);
	HBorder2->CreateFixture(&HFixture);

	contactListener = new ContactListener();
	mWorld->SetContactListener(contactListener);

	star->setAnchorPoint(Point(0.5, 0.5));
	star->setPosition(winSize.width / 2, winSize.height / 2);
	GameData(chapter);
	switch (AllowWallNumber)
	{
	case 0:
		numberr = Sprite::create("0.png");
		break;
	case 1:
		numberr = Sprite::create("1.png");
		break;
	case 2:
		numberr = Sprite::create("2.png");
		break;
	case 3:
		numberr = Sprite::create("3.png");
		break;
	case 4:
		numberr = Sprite::create("4.png");
		break;
	case 5:
		numberr = Sprite::create("5.png");
		break;
	case 6:
		numberr = Sprite::create("6.png");
		break;
	case 7:
		numberr = Sprite::create("7.png");
		break;
	case 8:
		numberr = Sprite::create("8.png");
		break;
	case 9:
		numberr = Sprite::create("9.png");
		break;
	case 10:
		numberr = Sprite::create("10.png");
		break;
	}
	if (AllowWallNumber <= 10)
	{
		auto sa = Sprite::create("bai.png");
		sa->setPosition(winSize.width * 4 / 5, winSize.height * 4 / 5);
		this->addChild(sa);
		sa->setScale(0.6);
		numberr->setPosition(winSize.width * 4 / 5, winSize.height * 4 / 5);
		this->addChild(numberr);
	}

	this->addChild(star);
	scheduleUpdate();
	HaveChoose = 1;
	Th = UserDefault::getInstance()->getIntegerForKey("Th", 0);
	if (!Th)
	{
		Tech();
	}
}
bool ThrowScene::onTouchBegan(Touch* pTouch, Event* pEvent)
{
	if (HaveChoose == 0)
		return false;
	if (WallNumber >= AllowWallNumber && go)
		return false;
	if (go)
	{
		Start = pTouch->getLocation();
		return true;
	}
	// 获取触摸点位置    
	Vec2 pos = pTouch->getLocation();
	// 设置位置    
	star->setPosition(pos);
	// 删除所有活动条带段  
	streak->reset();
	return true;
}
void ThrowScene::onTouchMoved(Touch* pTouch, Event* pEvent)
{
	if (HaveChoose == 0)
		return;
	if (WallNumber >= AllowWallNumber && go)
		return;
	Vec2 pos = pTouch->getLocation();
	if (go)
	{

		double x = pos.x - Start.x;
		double y = pos.y - Start.y;
		double l = sqrt(x*x + y*y);
		if (abs(l) < eps)
		{
			return;
		}
		double si = y / l;
		double theta = asin(si) * 180 / PI;
		if (x < 0)
		{
			if (theta >= 0)
			{
				double temp = 90 - theta;
				theta = temp + 90;
			}
			if (theta < 0)
			{
				double temp = -90 - theta;
				theta = -90 + temp;
			}
		}
		prespr->setScaleX(l / 100);
		prespr->setPosition((Start + pos) / 2);

		prespr->setRotation(-theta);


		return;
	}
	// 触摸移动的偏移量   
	Vec2 delta = pTouch->getDelta();
	// 设置位置    
	if (!(delta.x == 0 && delta.y == 0))
		Delta = delta;
	star->setPosition(star->getPosition() + delta);
}
void ThrowScene::onTouchEnded(Touch* pTouch, Event* pEvent)
{
	if (!Th)
		return;
	if (HaveChoose == 0)
		return;
	if (WallNumber >= AllowWallNumber && go)
		return;
	if (w)
		return;
	if (go)
	{
		End = pTouch->getLocation();
		CreateWall();
		WallNumber++;
		prespr->setPosition(-5000, -5000);
		return;
	}
	Vec2 pos = pTouch->getLocation();
	if (pos.x<10 || pos.x>winSize.width - 10 || pos.y<10 || pos.y>winSize.height - 10)
		return;
	double x = Delta.x;
	double y = Delta.y;
	double l = sqrt(x*x + y*y);
	if (abs(l) < eps)
		return;
	double si = y / l;
	double co = x / l;
	bodyDef.type = b2_dynamicBody; //小球是可以动的  
	bodyDef.bullet = true;
	bodyDef.userData = star;    //这只是为了保存数据，可以通过物体找到对应的精灵  
	bodyDef.linearDamping = 0.0f; //初速度为0  
	bodyDef.position.Set(star->getPositionX() / PTM_RATIO, star->getPositionY() / PTM_RATIO); //初始位置  
	mBallBody = mWorld->CreateBody(&bodyDef); // 在Box2D世界中创建一个物体  
	b2Vec2 Speed;
	Speed.x = speed *(co);
	Speed.y = speed*(si);
	mBallBody->SetLinearVelocity(Speed);
	mBallBody->SetBullet(true);
	mBallBody->SetFixedRotation(true);
	//12.0f
	bodyShape.m_radius = 13.0f / PTM_RATIO;
	//小球的定制器  
	bodyFixture.density = 1;  // 密度  
	bodyFixture.shape = &bodyShape; //形状  
	bodyFixture.friction = 0.0f; //摩擦力，因为掉落过程中没有物体间的摩擦，所以没用  
	bodyFixture.restitution = 1.0f; //弹力，100%反弹~~~  
	mBallBody->CreateFixture(&bodyFixture);
	go = true;
	inittime = getMillSecond();
}
void ThrowScene::update(float dt)
{
	if (!go)
	{
		streak->setPosition(star->getPosition());
		mypat->setPosition(star->getPosition());
		return;
	}
	if (star->getTag() == 1)
		die();
	if (star->getTag() - 1000000 < 1000)
		DestoryWallWithTag(star->getTag() - 1000000);
	else if (star->getTag() - 1000000 < 100000)
		ChangeOrgan(star->getTag() - 1000000);
	Sprite* sprite = (Sprite*)mBallBody->GetUserData();
	mWorld->Step(timeStep, velocityIterations, positionIterations);
	b2Vec2 pos = mBallBody->GetPosition();
	double x = pos.x * PTM_RATIO;
	double y = pos.y * PTM_RATIO;
	sprite->setPosition(Point(x, y));
	float angle = mBallBody->GetAngle();
	sprite->setRotation(angle);
	streak->setPosition(star->getPosition());
	mypat->setPosition(star->getPosition());
}
void ThrowScene::CreateWall()
{
	wing = 1;
	double x = End.x - Start.x;
	double y = End.y - Start.y;
	double l = sqrt(x*x + y*y);
	if (abs(l) < eps)
	{
		return;
	}
	double si = y / l;
	double theta = asin(si) * 180 / PI;
	if (x < 0)
	{
		if (theta >= 0)
		{
			double temp = 90 - theta;
			theta = temp + 90;
		}
		if (theta < 0)
		{
			double temp = -90 - theta;
			theta = -90 + temp;
		}
	}
	auto spr = Sprite::create("wall.jpg", Rect(0, 0, l, 5));
	spr->setPosition((Start + End) / 2);
	spr->setAnchorPoint(Point(0.5, 0.5));
	spr->setRotation(-theta);
	spr->setTag(1001 + WallNumber);

	if (chapter == 4)
	{
		Organ++;
		spr->setTag(10001 + Organ);
		spr->setColor(Color3B::RED);
	}
	if (chapter == 5)
	{
		Organ++;
		spr->setTag(10201 + Organ);
		spr->setColor(Color3B::GREEN);
	}
	if (chapter == 6)
	{
		Organ++;
		spr->setTag(10401 + Organ);
		spr->setColor(Color3B::GRAY);
	}


	this->addChild(spr);
	double rad = theta*PI / 180;


	b2BodyDef WallDef;
	WallDef.type = b2_staticBody;
	double wx = (Start.x + End.x) / 2;
	double wy = (Start.y + End.y) / 2;
	WallDef.position.Set(wx / PTM_RATIO, wy / PTM_RATIO);
	WallDef.angle = rad *1.0f;
	WallDef.userData = spr;

	//mWorld->DestroyBody(mBallBody);
	b2Body* Wall = mWorld->CreateBody(&WallDef); //在世界中创建一个物体（地面）  

	b2PolygonShape WallShape;
	WallShape.SetAsBox(l / PTM_RATIO / 2, 5 / PTM_RATIO / 2); //设置长度和高度，这里描述的地板就像是X轴，是一条线  
	b2FixtureDef WallFixture;
	WallFixture.shape = &WallShape;
	Wall->CreateFixture(&WallFixture);          //定制地面的形状 
	//double xx = Delta.x;
	//double yy = Delta.y;
	//double ll = sqrt(xx*xx + yy*yy);
	//if (abs(ll) < eps)
	//	return;
	//sii = yy / ll;
	//coi = xx / ll;
	//bodyDef.position.Set(star->getPositionX() / PTM_RATIO, star->getPositionY() / PTM_RATIO); //初始位置  
	//mBallBody = mWorld->CreateBody(&bodyDef); // 在Box2D世界中创建一个物体  
	//b2Vec2 speed;
	//speed.x = 100.0f *(co);
	//speed.y = 100.0f*(si);
	//mBallBody->SetLinearVelocity(speed);
	//mBallBody->SetBullet(true);
	//mBallBody->SetFixedRotation(true);
	//12.0f
	//bodyShape.m_radius = 12.0f / PTM_RATIO;
	//小球的定制器  
	//bodyFixture.density = 1;  // 密度  
	//bodyFixture.shape = &bodyShape; //形状  
	//bodyFixture.friction = 0.0f; //摩擦力，因为掉落过程中没有物体间的摩擦，所以没用  
	//bodyFixture.restitution = 1.0f; //弹力，100%反弹~~~  
	//mBallBody->CreateFixture(&bodyFixture);
}
void ThrowScene::win()
{
	unscheduleUpdate();
	w = 1;
	wintime = getMillSecond();
	auto spr = Sprite::create("lan2.png");
	spr->setScaleY(1.2);
	auto a = FadeIn::create(0.5);
	spr->setOpacity(0);
	spr->runAction(a);
	spr->setPosition(winSize.width / 2, winSize.height / 2);
	auto sprr = Sprite::create("SL.png");
	//sprr->setOpacity(0);
	//sprr->runAction(a);
	sprr->setPosition(winSize.width / 2, winSize.height * 4 / 7);
	this->addChild(sprr, 1);
	this->addChild(spr);





	char s[15] = "chapter";

	char sp[5];
	sprintf(sp, "%d", chapter);

	strcat(s, sp);
	sprintf(sp, "%d", Mode);
	strcat(s, sp);
	int Have = UserDefault::getInstance()->getIntegerForKey(s, 0);
	if (Have == 0)
	{
		UserDefault::getInstance()->setIntegerForKey(s, 1);
		char ss[15] = "chapter";
		char sp[5];
		sprintf(sp, "%d", chapter);
		strcat(ss, sp);
		WinNum = UserDefault::getInstance()->getIntegerForKey(ss, 0);
		UserDefault::getInstance()->setIntegerForKey(ss, WinNum + 1);
	}

	char s1[15] = "MinTime";
	char s2[15] = "MinWall";
	sprintf(sp, "%d", chapter);
	strcat(s1, sp);
	sprintf(sp, "%d", Mode % 10);
	strcat(s1, sp);
	sprintf(sp, "%d", chapter);
	strcat(s2, sp);
	sprintf(sp, "%d", Mode % 10);
	strcat(s2, sp);

	MinTime = UserDefault::getInstance()->getDoubleForKey(s1, 10000000);
	MinWall = UserDefault::getInstance()->getIntegerForKey(s2, 5000);


	auto label_wall = Label::createWithSystemFont("", "", 30);
	label_wall->setPosition(winSize.width / 2, winSize.height / 2 - 40);
	label_wall->setColor(Color3B::BLACK);
	label_wall->setString(StringUtils::format("木棒:%d", WallNumber));
	this->addChild(label_wall);
	auto label_time = Label::createWithSystemFont("", "", 30);
	label_time->setPosition(winSize.width / 2, winSize.height / 2 - 80);
	label_time->setColor(Color3B::BLACK);
	Time = wintime - inittime;
	label_time->setString(StringUtils::format("时间:%lf", Time));
	this->addChild(label_time);

	if (WallNumber < MinWall)
	{
		MinWall = WallNumber;
		UserDefault::getInstance()->setIntegerForKey(s2, MinWall);
	}
	if (Time < MinTime)
	{
		MinTime = Time;
		UserDefault::getInstance()->setDoubleForKey(s1, MinTime);
	}
	auto label_minwall = Label::createWithSystemFont("", "", 30);
	label_minwall->setPosition(winSize.width / 2, winSize.height / 2 - 120);
	label_minwall->setColor(Color3B::BLACK);
	label_minwall->setString(StringUtils::format("最少木棒:%d", MinWall));
	this->addChild(label_minwall);
	auto label_mintime = Label::createWithSystemFont("", "", 30);
	label_mintime->setPosition(winSize.width / 2, winSize.height / 2 - 160);
	label_mintime->setColor(Color3B::BLACK);
	int weimT = wei(MinTime);
	int mTim = MinTime;
	label_mintime->setString(StringUtils::format("最短时间:%lf", MinTime));
	this->addChild(label_mintime);
	UserDefault::getInstance()->flush();
	WinMenu();
}
void ThrowScene::WinMenu()
{
	auto item_0 = MenuItemImage::create("CS.png", "CSS.png", CC_CALLBACK_1(ThrowScene::ReStart, this));
	auto item_1 = MenuItemImage::create("XYG.png", "XYG.png", CC_CALLBACK_1(ThrowScene::Next, this));
	auto item_2 = MenuItemImage::create("FH.png", "FHH.png", CC_CALLBACK_1(ThrowScene::Return, this));



	Menu *menu = Menu::create(item_0, item_1, NULL);
	Menu *menuq = Menu::create(item_2, NULL);
	menu->alignItemsHorizontallyWithPadding(50);
	menu->setPosition(Point(winSize.width / 2, 160));
	menu->setVisible(true);
	this->addChild(menu);
	menuq->alignItemsHorizontallyWithPadding(50);
	menuq->setPosition(Point(winSize.width / 2, 60));
	menuq->setVisible(true);
	this->addChild(menuq);

}
void ThrowScene::die()
{
	unscheduleUpdate();
	w = 1;
	wintime = getMillSecond();
	auto spr = Sprite::create("lan1.png");
	spr->setPosition(winSize.width / 2, winSize.height / 2);
	auto sprr = Sprite::create("SB.png");
	sprr->setPosition(winSize.width / 2, winSize.height * 4 / 7);
	this->addChild(sprr, 1);
	this->addChild(spr);




	auto label_wall = Label::createWithSystemFont("", "Consolas", 30);
	label_wall->setPosition(winSize.width / 2, winSize.height / 2 - 40);
	label_wall->setColor(Color3B::BLACK);
	label_wall->setString(StringUtils::format("木棒:%d", WallNumber));
	this->addChild(label_wall);
	auto label_time = Label::createWithSystemFont("", "Consolas", 30);
	label_time->setPosition(winSize.width / 2, winSize.height / 2 - 80);
	label_time->setColor(Color3B::BLACK);
	Time = wintime - inittime;
	label_time->setString(StringUtils::format("时间:%.2lf", Time));
	this->addChild(label_time);


	auto a = FadeIn::create(0.5);
	spr->setOpacity(0);
	spr->runAction(a);
	sprr->setOpacity(0);
	auto b = FadeIn::create(0.5);
	sprr->runAction(b);
	auto c = FadeIn::create(1);
	auto d = FadeIn::create(1);
	label_time->setOpacity(0);
	label_wall->setOpacity(0);
	label_wall->runAction(c);
	label_time->runAction(d);



	DieMenu();
}
void ThrowScene::DieMenu()
{
	auto item_0 = MenuItemImage::create("CS.png", "CSS.png", CC_CALLBACK_1(ThrowScene::ReStart, this));
	auto item_2 = MenuItemImage::create("FH.png", "FHH.png", CC_CALLBACK_1(ThrowScene::Return, this));



	Menu *menu = Menu::create(item_0, NULL);
	Menu *menuq = Menu::create(item_2, NULL);
	menu->alignItemsHorizontallyWithPadding(50);
	menu->setPosition(Point(winSize.width / 2, 160));
	menu->setVisible(true);
	this->addChild(menu);
	menuq->alignItemsHorizontallyWithPadding(50);
	menuq->setPosition(Point(winSize.width / 2, 60));
	menuq->setVisible(true);
	this->addChild(menuq);

}
void ThrowScene::ReStart(Ref *sender)
{
	delete mWorld;
	this->removeAllChildrenWithCleanup(0);
	InitGameData();
}
void ThrowScene::Next(Ref *sender)
{
	delete mWorld;
	this->removeAllChildrenWithCleanup(0);
	if (Mode == 10 || Mode == 9)
	{
		if (WinNum >= 5)
		{
			Mode++;
			InitGameData();
		}
		else
		{
			auto scene = TransitionFadeTR::create(0.5, ThrowScene::createScene());
			Director::getInstance()->replaceScene(scene);
		}
	}
	else
	{
		Mode++;
		InitGameData();
	}
}
void ThrowScene::Return(Ref *sender)
{
	delete mWorld;
	this->removeAllChildrenWithCleanup(0);
	auto scene = TransitionFadeTR::create(0.5, ThrowScene::createScene());
	Director::getInstance()->replaceScene(scene);
}
double ThrowScene::getMillSecond()
{
	struct timeval tv;
	gettimeofday(&tv, nullptr);
	return (double)tv.tv_sec * 1000 + (double)tv.tv_usec / 1000;
}
void ThrowScene::DestoryWallWithTag(int tag)
{
	star->setTag(1000005);
	for (b2Body* body = mWorld->GetBodyList(); body != nullptr; body = body->GetNext())
	{
		Sprite* sprite = (Sprite*)body->GetUserData();
		if (sprite != NULL)
		{
			if (sprite->getTag() == tag)
			{
				this->removeChildByTag(tag);
				mWorld->DestroyBody(body);
				ShallDestory--;
				if (ShallDestory <= 0)
					win();
				break;
			}
		}
	}
	this->removeChildByTag(tag);
}
void ThrowScene::ChangeOrgan(int tag)
{
	star->setTag(1000005);
	b2Body* body;
	Sprite* sprite;
	for (body = mWorld->GetBodyList(); body != nullptr; body = body->GetNext())
	{
		sprite = (Sprite*)body->GetUserData();
		if (sprite != NULL)
		{
			if (sprite->getTag() == tag)
			{
				break;
			}
		}
	}
	//type3
	if (tag > 10450)
	{
		//放大
		auto spr = this->getChildByTag(tag);
		if (spr == NULL)
			return;
		spr->setTag(tag - 50);
		spr->setScaleX(5);
		mWorld->DestroyBody(body);
		double theta = spr->getRotation();
		double rad = -theta*PI / 180;

		b2BodyDef WallDef;
		WallDef.type = b2_staticBody;
		double wx = spr->getPosition().x;
		double wy = spr->getPosition().y;
		WallDef.position.Set(wx / PTM_RATIO, wy / PTM_RATIO);
		WallDef.angle = rad *1.0f;
		WallDef.userData = spr;

		//mWorld->DestroyBody(mBallBody);
		b2Body* Wall = mWorld->CreateBody(&WallDef); //在世界中创建一个物体（地面）  

		b2PolygonShape WallShape;
		Point po = spr->getContentSize();
		WallShape.SetAsBox(po.x * 5 / PTM_RATIO / 2, 5 / PTM_RATIO / 2); //设置长度和高度，这里描述的地板就像是X轴，是一条线  
		log("%lf,%lf", po.x, po.y);
		b2FixtureDef WallFixture;
		WallFixture.filter.groupIndex = -1;
		WallFixture.shape = &WallShape;
		Wall->CreateFixture(&WallFixture);
	}
	else if (tag > 10400)
	{
		//缩小
		auto spr = this->getChildByTag(tag);
		if (spr == NULL)
			return;

		spr->setTag(tag + 50);
		spr->setScaleX(0.2);
		mWorld->DestroyBody(body);
		double theta = spr->getRotation();
		double rad = -theta*PI / 180;

		b2BodyDef WallDef;
		WallDef.type = b2_staticBody;
		double wx = spr->getPosition().x;
		double wy = spr->getPosition().y;
		WallDef.position.Set(wx / PTM_RATIO, wy / PTM_RATIO);
		WallDef.angle = rad *1.0f;
		WallDef.userData = spr;

		//mWorld->DestroyBody(mBallBody);
		b2Body* Wall = mWorld->CreateBody(&WallDef); //在世界中创建一个物体（地面）  

		b2PolygonShape WallShape;
		Point po = spr->getContentSize();
		WallShape.SetAsBox(po.x / 5 / PTM_RATIO / 2, 5 / PTM_RATIO / 2); //设置长度和高度，这里描述的地板就像是X轴，是一条线  
		b2FixtureDef WallFixture;
		WallFixture.filter.groupIndex = -1;
		WallFixture.shape = &WallShape;
		Wall->CreateFixture(&WallFixture);
	}
	//type2
	else if (tag > 10250)
	{
		return;
	}
	else if (tag > 10200)
	{
		//缩小
		auto spr = this->getChildByTag(tag);
		if (spr == NULL)
			return;
		spr->setTag(tag + 50);
		spr->setScaleX(0.2);
		mWorld->DestroyBody(body);
		double theta = spr->getRotation();
		double rad = -theta*PI / 180;

		b2BodyDef WallDef;
		WallDef.type = b2_staticBody;
		double wx = spr->getPosition().x;
		double wy = spr->getPosition().y;
		WallDef.position.Set(wx / PTM_RATIO, wy / PTM_RATIO);
		WallDef.angle = rad *1.0f;
		WallDef.userData = spr;

		//mWorld->DestroyBody(mBallBody);
		b2Body* Wall = mWorld->CreateBody(&WallDef); //在世界中创建一个物体（地面）  

		b2PolygonShape WallShape;
		Point po = spr->getContentSize();
		WallShape.SetAsBox(po.x / 5 / PTM_RATIO / 2, 5 / PTM_RATIO / 2); //设置长度和高度，这里描述的地板就像是X轴，是一条线  
		b2FixtureDef WallFixture;
		WallFixture.filter.groupIndex = -1;
		WallFixture.shape = &WallShape;
		Wall->CreateFixture(&WallFixture);


	}
	//type1
	else if (tag > 10050)
	{
		return;
	}
	else if (tag > 10000)
	{
		//放大
		auto spr = this->getChildByTag(tag);
		if (spr == NULL)
			return;
		spr->setTag(tag + 50);
		spr->setScaleX(20);
		mWorld->DestroyBody(body);
		double theta = spr->getRotation();
		double rad = -theta*PI / 180;

		b2BodyDef WallDef;
		WallDef.type = b2_staticBody;
		double wx = spr->getPosition().x;
		double wy = spr->getPosition().y;
		WallDef.position.Set(wx / PTM_RATIO, wy / PTM_RATIO);
		WallDef.angle = rad *1.0f;
		WallDef.userData = spr;

		//mWorld->DestroyBody(mBallBody);
		b2Body* Wall = mWorld->CreateBody(&WallDef); //在世界中创建一个物体（地面）  

		b2PolygonShape WallShape;
		Point po = spr->getContentSize();
		WallShape.SetAsBox(po.x * 20 / PTM_RATIO / 2, 5 / PTM_RATIO / 2); //设置长度和高度，这里描述的地板就像是X轴，是一条线  
		log("%lf,%lf", po.x, po.y);
		b2FixtureDef WallFixture;
		WallFixture.filter.groupIndex = -1;
		WallFixture.shape = &WallShape;
		Wall->CreateFixture(&WallFixture);
	}
}
void ThrowScene::CreateNormalWall(Vec2 End, Vec2 Start)
{
	ShallDestory++;
	double x = End.x - Start.x;
	double y = End.y - Start.y;
	double l = sqrt(x*x + y*y);
	if (abs(l) < eps)
	{
		return;
	}
	double si = y / l;
	double theta = asin(si) * 180 / PI;
	if (x < 0)
	{
		if (theta >= 0)
		{
			double temp = 90 - theta;
			theta = temp + 90;
		}
		if (theta < 0)
		{
			double temp = -90 - theta;
			theta = -90 + temp;
		}
	}
	auto spr = Sprite::create("wall.jpg", Rect(0, 0, l, 5));
	spr->setPosition((Start + End) / 2);
	spr->setAnchorPoint(Point(0.5, 0.5));
	spr->setRotation(-theta);
	spr->setTag(101 + ShallDestory);
	spr->setColor(Color3B::BLACK);
	this->addChild(spr);
	double rad = theta*PI / 180;

	b2BodyDef WallDef;
	WallDef.type = b2_staticBody;
	double wx = (Start.x + End.x) / 2;
	double wy = (Start.y + End.y) / 2;
	WallDef.position.Set(wx / PTM_RATIO, wy / PTM_RATIO);
	WallDef.angle = rad *1.0f;
	WallDef.userData = spr;

	//mWorld->DestroyBody(mBallBody);
	b2Body* Wall = mWorld->CreateBody(&WallDef); //在世界中创建一个物体（地面）  

	b2PolygonShape WallShape;
	WallShape.SetAsBox(l / PTM_RATIO / 2, 5 / PTM_RATIO / 2); //设置长度和高度，这里描述的地板就像是X轴，是一条线  
	b2FixtureDef WallFixture;
	WallFixture.filter.groupIndex = -1;
	WallFixture.shape = &WallShape;
	Wall->CreateFixture(&WallFixture);
}
void ThrowScene::CreateOrganWall(Vec2 End, Vec2 Start, int type)
{
	Organ++;
	double x = End.x - Start.x;
	double y = End.y - Start.y;
	double l = sqrt(x*x + y*y);
	if (abs(l) < 1e-9)
	{
		return;
	}
	double si = y / l;
	double theta = asin(si) * 180 / PI;
	if (x < 0)
	{
		if (theta >= 0)
		{
			double temp = 90 - theta;
			theta = temp + 90;
		}
		if (theta < 0)
		{
			double temp = -90 - theta;
			theta = -90 + temp;
		}
	}
	auto spr = Sprite::create("wall.jpg", Rect(0, 0, l, 5));
	spr->setPosition((Start + End) / 2);
	spr->setAnchorPoint(Point(0.5, 0.5));
	spr->setRotation(-theta);
	if (type == 1)
		spr->setTag(10001 + Organ);
	else if (type == 2)
		spr->setTag(10201 + Organ);
	else if (type == 3)
		spr->setTag(10401 + Organ);
	if (type == 1)
		spr->setColor(Color3B::RED);
	else if (type == 2)
		spr->setColor(Color3B::GREEN);
	else if (type == 3)
		spr->setColor(Color3B::GRAY);
	this->addChild(spr);
	double rad = theta*PI / 180;


	b2BodyDef WallDef;
	WallDef.type = b2_staticBody;
	double wx = (Start.x + End.x) / 2;
	double wy = (Start.y + End.y) / 2;
	WallDef.position.Set(wx / PTM_RATIO, wy / PTM_RATIO);
	WallDef.angle = rad *1.0f;
	WallDef.userData = spr;

	//mWorld->DestroyBody(mBallBody);
	b2Body* Wall = mWorld->CreateBody(&WallDef); //在世界中创建一个物体（地面）  

	b2PolygonShape WallShape;
	WallShape.SetAsBox(l / PTM_RATIO / 2, 5 / PTM_RATIO / 2); //设置长度和高度，这里描述的地板就像是X轴，是一条线  
	b2FixtureDef WallFixture;
	WallFixture.shape = &WallShape;
	WallFixture.filter.groupIndex = -1;
	Wall->CreateFixture(&WallFixture);


}
void ThrowScene::CreateOKWall(Vec2 End, Vec2 Start)
{
	WallNumber++;
	double x = End.x - Start.x;
	double y = End.y - Start.y;
	double l = sqrt(x*x + y*y);
	if (abs(l) < eps)
	{
		return;
	}
	double si = y / l;
	double theta = asin(si) * 180 / PI;
	if (x < 0)
	{
		if (theta >= 0)
		{
			double temp = 90 - theta;
			theta = temp + 90;
		}
		if (theta < 0)
		{
			double temp = -90 - theta;
			theta = -90 + temp;
		}
	}
	auto spr = Sprite::create("wall.jpg", Rect(0, 0, l, 5));
	spr->setPosition((Start + End) / 2);
	spr->setAnchorPoint(Point(0.5, 0.5));
	spr->setRotation(-theta);
	spr->setTag(1001 + WallNumber);
	this->addChild(spr);
	double rad = theta*PI / 180;

	b2BodyDef WallDef;
	WallDef.type = b2_staticBody;
	double wx = (Start.x + End.x) / 2;
	double wy = (Start.y + End.y) / 2;
	WallDef.position.Set(wx / PTM_RATIO, wy / PTM_RATIO);
	WallDef.angle = rad *1.0f;
	WallDef.userData = spr;

	//mWorld->DestroyBody(mBallBody);
	b2Body* Wall = mWorld->CreateBody(&WallDef); //在世界中创建一个物体（地面）  

	b2PolygonShape WallShape;
	WallShape.SetAsBox(l / PTM_RATIO / 2, 5 / PTM_RATIO / 2); //设置长度和高度，这里描述的地板就像是X轴，是一条线  
	b2FixtureDef WallFixture;
	WallFixture.filter.groupIndex = -1;
	WallFixture.shape = &WallShape;
	Wall->CreateFixture(&WallFixture);
}
void ThrowScene::menuCallback(Ref *sender)
{
	auto item = (MenuItem*)sender;
	Mode = item->getTag();
	if (Mode > 10)
	{
		GameData(chapter);
		return;
	}
	this->removeAllChildrenWithCleanup(1);
	InitGameData();
}
void ThrowScene::First(Ref *sender)
{
	delete mWorld;
	this->removeAllChildrenWithCleanup(1);
	Th = 1;
	UserDefault::getInstance()->setIntegerForKey("Th", 1);
	UserDefault::getInstance()->flush();
	InitGameData();
}
void ThrowScene::GameData(int chapter)
{
	if (Mode == 11)
	{
		if (WinNum < 5 || chapter == 6)
			return;
		chapter++;
		UserDefault::getInstance()->setIntegerForKey("chapter", chapter);
		UserDefault::getInstance()->flush();
		//auto scene = TransitionFadeTR::create(0.5, ThrowScene::createScene());
		//Director::getInstance()->replaceScene(scene);
		CCDirector::sharedDirector()->replaceScene(ThrowScene::createScene());
		return;
	}
	if (Mode == 12)
	{
		if (chapter == 1)
			return;
		chapter--;
		UserDefault::getInstance()->setIntegerForKey("chapter", chapter);
		UserDefault::getInstance()->flush();
		//auto scene = TransitionFadeTR::create(0.5, ThrowScene::createScene());
		//Director::getInstance()->replaceScene(scene);
		CCDirector::sharedDirector()->replaceScene(ThrowScene::createScene());
		return;
	}
	switch (chapter)
	{
	case 1:
	{
		switch (Mode)
		{
		case 1:
		{
			CreateNormalWall(Point(100, 100), Point(500, 500));
			CreateNormalWall(Point(500, 100), Point(500, 500));
			AllowWallNumber = 1;
		}
			break;
		case 2:
		{
			CreateNormalWall(Point(100, 300), Point(300, 300));
			CreateNormalWall(Point(500, 300), Point(300, 300));
			CreateNormalWall(Point(300, 500), Point(300, 300));
			CreateNormalWall(Point(300, 100), Point(300, 300));
			AllowWallNumber = 2;
		}
			break;
		case 3:
		{
			CreateNormalWall(Point(100, 0), Point(400, 300));
			CreateNormalWall(Point(300, 100), Point(200, 600));
			CreateNormalWall(Point(100, 100), Point(500, 500));
			CreateNormalWall(Point(500, 100), Point(500, 500));
		}
			break;
		case 4:
		{

			CreateNormalWall(Point(100, 100), Point(100, 250));
			CreateNormalWall(Point(100, 450), Point(100, 300));
			CreateNormalWall(Point(100, 500), Point(100, 650));


			CreateNormalWall(Point(480, 100), Point(480, 250));
			CreateNormalWall(Point(480, 450), Point(480, 300));
			CreateNormalWall(Point(480, 500), Point(480, 650));
		}
			break;
		case 5:
		{
			CreateNormalWall(Point(232, 232), Point(473, 753));
			CreateNormalWall(Point(200, 550), Point(350, 730));
			CreateNormalWall(Point(100, 0), Point(410, 340));
			CreateNormalWall(Point(400, 100), Point(200, 100));
			AllowWallNumber = 1;
		}
			break;

		case 6:
		{
			CreateNormalWall(Point(432, 232), Point(173, 553));
			CreateNormalWall(Point(200, 550), Point(220, 130));
			CreateNormalWall(Point(100, 300), Point(110, 340));
			CreateNormalWall(Point(400, 200), Point(600, 600));
			AllowWallNumber = 1;
		}
			break;

		case 7:
		{
			CreateNormalWall(Point(532, 232), Point(273, 653));
			CreateNormalWall(Point(300, 650), Point(350, 330));
			CreateNormalWall(Point(100, 300), Point(440, 340));
			CreateNormalWall(Point(100, 100), Point(200, 100));
			AllowWallNumber = 1;
		}
			break;
		case 8:
		{
			CreateNormalWall(Point(533, 234), Point(325, 235));
			CreateNormalWall(Point(462, 134), Point(123, 324));
			CreateNormalWall(Point(200, 400), Point(640, 340));
			CreateNormalWall(Point(440, 440), Point(100, 100));
			AllowWallNumber = 0;
		}
			break;
		case 9:
		{
			CreateNormalWall(Point(133, 234), Point(625, 235));
			CreateNormalWall(Point(262, 534), Point(233, 652));
			CreateNormalWall(Point(200, 400), Point(140, 340));
			CreateNormalWall(Point(540, 340), Point(200, 100));
			CreateNormalWall(Point(140, 540), Point(100, 300));
			CreateNormalWall(Point(240, 440), Point(300, 100));
			AllowWallNumber = 1;
		}
			break;
		case 10:
		{
			CreateNormalWall(Point(100, 300), Point(300, 300));
			CreateNormalWall(Point(500, 300), Point(300, 300));
			CreateNormalWall(Point(300, 500), Point(300, 300));
			CreateNormalWall(Point(300, 100), Point(300, 300));
			CreateNormalWall(Point(100, 100), Point(300, 300));
			CreateNormalWall(Point(500, 100), Point(300, 300));
			CreateNormalWall(Point(100, 500), Point(300, 300));
			CreateNormalWall(Point(500, 500), Point(300, 300));
			AllowWallNumber = 2;
		}
			break;

		}
	}
		break;
	case 2:
	{
		switch (Mode)
		{
		case 1:
		{
			CreateNormalWall(Point(100, 100), Point(540, 100));
			CreateNormalWall(Point(100, 800), Point(540, 800));
			CreateNormalWall(Point(100, 200), Point(200, 200));
			CreateNormalWall(Point(540, 200), Point(440, 200));
			CreateNormalWall(Point(100, 700), Point(200, 700));
			CreateNormalWall(Point(540, 700), Point(440, 700));
			CreateNormalWall(Point(100, 200), Point(100, 700));
			CreateNormalWall(Point(540, 200), Point(540, 700));
		}
			break;
		case 2:
		{
			CreateNormalWall(Point(60, 100), Point(60, 900));
			CreateNormalWall(Point(600, 100), Point(600, 900));
			CreateNormalWall(Point(600, 200), Point(60, 200));
			CreateNormalWall(Point(600, 300), Point(60, 300));
			CreateNormalWall(Point(600, 400), Point(60, 400));
			CreateNormalWall(Point(600, 500), Point(60, 500));
			CreateNormalWall(Point(600, 600), Point(60, 600));
			CreateNormalWall(Point(600, 700), Point(60, 700));
			CreateNormalWall(Point(600, 800), Point(60, 800));
			CreateNormalWall(Point(600, 900), Point(60, 900));
			CreateNormalWall(Point(600, 100), Point(60, 100));
		}
			break;
		case 3:
		{
			CreateNormalWall(Point(winSize.width / 2 - 160, winSize.height / 2),
				Point(winSize.width / 2 - 80, winSize.height / 2 + 160));
			CreateNormalWall(Point(winSize.width / 2 - 80, winSize.height / 2 + 160),
				Point(winSize.width / 2 + 80, winSize.height / 2 + 160));
			CreateNormalWall(Point(winSize.width / 2 + 80, winSize.height / 2 + 160),
				Point(winSize.width / 2 + 160, winSize.height / 2));
			CreateNormalWall(Point(winSize.width / 2 + 160, winSize.height / 2),
				Point(winSize.width / 2 + 80, winSize.height / 2 - 160));
			CreateNormalWall(Point(winSize.width / 2 + 80, winSize.height / 2 - 160),
				Point(winSize.width / 2 - 80, winSize.height / 2 - 160));
			CreateNormalWall(Point(winSize.width / 2 - 80, winSize.height / 2 - 160),
				Point(winSize.width / 2 - 160, winSize.height / 2));
		}
			break;
		case 4:
		{
			//1
			CreateNormalWall(Point(winSize.width / 2 - 80 - 80 * sqrt(2), winSize.height / 2 - 80),
				Point(winSize.width / 2 - 80 - 80 * sqrt(2), winSize.height / 2 + 80));
			//2
			CreateNormalWall(Point(winSize.width / 2 - 80 - 80 * sqrt(2), winSize.height / 2 + 80),
				Point(winSize.width / 2 - 80, winSize.height / 2 + 80 + 80 * sqrt(2)));

			//3
			CreateNormalWall(Point(winSize.width / 2 - 80, winSize.height / 2 + 80 + 80 * sqrt(2)),
				Point(winSize.width / 2 + 80, winSize.height / 2 + 80 + 80 * sqrt(2)));
			//4
			CreateNormalWall(Point(winSize.width / 2 + 80 + 80 * sqrt(2), winSize.height / 2 + 80),
				Point(winSize.width / 2 + 80, winSize.height / 2 + 80 + 80 * sqrt(2)));;
			//5
			CreateNormalWall(Point(winSize.width / 2 + 80 + 80 * sqrt(2), winSize.height / 2 - 80),
				Point(winSize.width / 2 + 80 + 80 * sqrt(2), winSize.height / 2 + 80));
			//6
			CreateNormalWall(Point(winSize.width / 2 + 80 + 80 * sqrt(2), winSize.height / 2 - 80),
				Point(winSize.width / 2 + 80, winSize.height / 2 - 80 - 80 * sqrt(2)));;
			//7
			CreateNormalWall(Point(winSize.width / 2 - 80, winSize.height / 2 - 80 - 80 * sqrt(2)),
				Point(winSize.width / 2 + 80, winSize.height / 2 - 80 - 80 * sqrt(2)));
			//8
			CreateNormalWall(Point(winSize.width / 2 - 80 - 80 * sqrt(2), winSize.height / 2 - 80),
				Point(winSize.width / 2 - 80, winSize.height / 2 - 80 - 80 * sqrt(2)));;
		}
			break;
		case 5:
		{
			CreateNormalWall(Point(winSize.width / 2 + 80, winSize.height / 2 - 80),
				Point(winSize.width / 2 + 80, winSize.height / 2 + 80));
			CreateNormalWall(Point(winSize.width / 2 - 80, winSize.height / 2 - 80),
				Point(winSize.width / 2 + 80, winSize.height / 2 - 80));
			CreateNormalWall(Point(winSize.width / 2 + 80, winSize.height / 2 + 80),
				Point(winSize.width / 2 - 80, winSize.height / 2 + 80));
			CreateNormalWall(Point(winSize.width / 2 - 80, winSize.height / 2 - 80),
				Point(winSize.width / 2 - 80, winSize.height / 2 + 80));
			CreateNormalWall(Point(winSize.width / 2 + 160, winSize.height / 2 - 160),
				Point(winSize.width / 2 + 160, winSize.height / 2 + 160));
			CreateNormalWall(Point(winSize.width / 2 - 160, winSize.height / 2 - 160),
				Point(winSize.width / 2 + 160, winSize.height / 2 - 160));
			CreateNormalWall(Point(winSize.width / 2 + 160, winSize.height / 2 + 160),
				Point(winSize.width / 2 - 160, winSize.height / 2 + 160));
			CreateNormalWall(Point(winSize.width / 2 - 160, winSize.height / 2 - 160),
				Point(winSize.width / 2 - 160, winSize.height / 2 + 160));
		}
			break;
		case 6:
		{
			CreateNormalWall(Point(winSize.width / 2 + 80, winSize.height / 2 - 80),
				Point(winSize.width / 2 + 80, winSize.height / 2 + 80));
			CreateNormalWall(Point(winSize.width / 2 - 80, winSize.height / 2 - 80),
				Point(winSize.width / 2 + 80, winSize.height / 2 - 80));
			CreateNormalWall(Point(winSize.width / 2 + 80, winSize.height / 2 + 80),
				Point(winSize.width / 2 - 80, winSize.height / 2 + 80));
			CreateNormalWall(Point(winSize.width / 2 - 80, winSize.height / 2 - 80),
				Point(winSize.width / 2 - 80, winSize.height / 2 + 80));



			CreateNormalWall(Point(winSize.width / 2 + 160, winSize.height / 2 - 160),
				Point(winSize.width / 2 + 160, winSize.height / 2 + 160));
			CreateNormalWall(Point(winSize.width / 2 - 160, winSize.height / 2 - 160),
				Point(winSize.width / 2 + 160, winSize.height / 2 - 160));
			CreateNormalWall(Point(winSize.width / 2 + 160, winSize.height / 2 + 160),
				Point(winSize.width / 2 - 160, winSize.height / 2 + 160));
			CreateNormalWall(Point(winSize.width / 2 - 160, winSize.height / 2 - 160),
				Point(winSize.width / 2 - 160, winSize.height / 2 + 160));


			CreateNormalWall(Point(winSize.width / 2 + 240, winSize.height / 2 - 240),
				Point(winSize.width / 2 + 240, winSize.height / 2 + 240));
			CreateNormalWall(Point(winSize.width / 2 - 240, winSize.height / 2 - 240),
				Point(winSize.width / 2 + 240, winSize.height / 2 - 240));
			CreateNormalWall(Point(winSize.width / 2 + 240, winSize.height / 2 + 240),
				Point(winSize.width / 2 - 240, winSize.height / 2 + 240));
			CreateNormalWall(Point(winSize.width / 2 - 240, winSize.height / 2 - 240),
				Point(winSize.width / 2 - 240, winSize.height / 2 + 240));



			CreateNormalWall(Point(winSize.width / 2 + 300, winSize.height / 2 - 300),
				Point(winSize.width / 2 + 300, winSize.height / 2 + 300));
			CreateNormalWall(Point(winSize.width / 2 - 300, winSize.height / 2 - 300),
				Point(winSize.width / 2 + 300, winSize.height / 2 - 300));
			CreateNormalWall(Point(winSize.width / 2 + 300, winSize.height / 2 + 300),
				Point(winSize.width / 2 - 300, winSize.height / 2 + 300));
			CreateNormalWall(Point(winSize.width / 2 - 300, winSize.height / 2 - 300),
				Point(winSize.width / 2 - 300, winSize.height / 2 + 300));
		}
			break;
		case 7:
		{
			AllowWallNumber = 1;
			CreateNormalWall(Point(100, 100), Point(500, 500));
			CreateNormalWall(Point(100, 500), Point(500, 100));
			CreateNormalWall(Point(100, 100), Point(100, 500));
			CreateNormalWall(Point(100, 500), Point(500, 500));
			CreateNormalWall(Point(100, 100), Point(500, 100));
			CreateNormalWall(Point(500, 100), Point(500, 500));
		}
			break;
		case 8:
		{
			CreateNormalWall(Point(100, 100), Point(100, 550));
			CreateNormalWall(Point(100, 550), Point(550, 550));
			CreateNormalWall(Point(100, 100), Point(550, 100));
			CreateNormalWall(Point(550, 100), Point(550, 550));


			CreateNormalWall(Point(250, 100), Point(250, 550));
			CreateNormalWall(Point(400, 100), Point(400, 550));
			CreateNormalWall(Point(100, 250), Point(550, 250));
			CreateNormalWall(Point(100, 400), Point(550, 400));
		}
			break;
		case 9:
		{
			AllowWallNumber = 4;
			CreateNormalWall(Point(100, 100), Point(100, 250));
			CreateNormalWall(Point(100, 400), Point(100, 250));
			CreateNormalWall(Point(100, 400), Point(100, 550));


			CreateNormalWall(Point(100, 550), Point(250, 550));
			CreateNormalWall(Point(400, 550), Point(250, 550));
			CreateNormalWall(Point(400, 550), Point(550, 550));


			CreateNormalWall(Point(100, 100), Point(250, 100));
			CreateNormalWall(Point(400, 100), Point(250, 100));
			CreateNormalWall(Point(400, 100), Point(550, 100));


			CreateNormalWall(Point(550, 100), Point(550, 250));
			CreateNormalWall(Point(550, 400), Point(550, 250));
			CreateNormalWall(Point(550, 400), Point(550, 550));


			CreateNormalWall(Point(250, 100), Point(250, 250));
			CreateNormalWall(Point(250, 400), Point(250, 250));
			CreateNormalWall(Point(250, 400), Point(250, 550));


			CreateNormalWall(Point(400, 100), Point(400, 250));
			CreateNormalWall(Point(400, 400), Point(400, 250));
			CreateNormalWall(Point(400, 400), Point(400, 550));


			CreateNormalWall(Point(100, 250), Point(250, 250));
			CreateNormalWall(Point(400, 250), Point(250, 250));
			CreateNormalWall(Point(400, 250), Point(550, 250));


			CreateNormalWall(Point(100, 400), Point(250, 400));
			CreateNormalWall(Point(400, 400), Point(250, 400));
			CreateNormalWall(Point(400, 400), Point(550, 400));


		}
			break;
		case 10:
		{
			AllowWallNumber = 5;
			CreateNormalWall(Point(winSize.width / 2 + 80 - 200, winSize.height / 2 - 80 - 200),
				Point(winSize.width / 2 + 80 - 200, winSize.height / 2 + 80 - 200));
			CreateNormalWall(Point(winSize.width / 2 - 80 - 200, winSize.height / 2 - 80 - 200),
				Point(winSize.width / 2 + 80 - 200, winSize.height / 2 - 80 - 200));
			CreateNormalWall(Point(winSize.width / 2 + 80 - 200, winSize.height / 2 + 80 - 200),
				Point(winSize.width / 2 - 80 - 200, winSize.height / 2 + 80 - 200));
			CreateNormalWall(Point(winSize.width / 2 - 80 - 200, winSize.height / 2 - 80 - 200),
				Point(winSize.width / 2 - 80 - 200, winSize.height / 2 + 80 - 200));


			CreateNormalWall(Point(winSize.width / 2 + 80 - 200, winSize.height / 2 - 80 + 200),
				Point(winSize.width / 2 + 80 - 200, winSize.height / 2 + 80 + 200));
			CreateNormalWall(Point(winSize.width / 2 - 80 - 200, winSize.height / 2 - 80 + 200),
				Point(winSize.width / 2 + 80 - 200, winSize.height / 2 - 80 + 200));
			CreateNormalWall(Point(winSize.width / 2 + 80 - 200, winSize.height / 2 + 80 + 200),
				Point(winSize.width / 2 - 80 - 200, winSize.height / 2 + 80 + 200));
			CreateNormalWall(Point(winSize.width / 2 - 80 - 200, winSize.height / 2 - 80 + 200),
				Point(winSize.width / 2 - 80 - 200, winSize.height / 2 + 80 + 200));



			CreateNormalWall(Point(winSize.width / 2 + 80 + 200, winSize.height / 2 - 80 - 200),
				Point(winSize.width / 2 + 80 + 200, winSize.height / 2 + 80 - 200));
			CreateNormalWall(Point(winSize.width / 2 - 80 + 200, winSize.height / 2 - 80 - 200),
				Point(winSize.width / 2 + 80 + 200, winSize.height / 2 - 80 - 200));
			CreateNormalWall(Point(winSize.width / 2 + 80 + 200, winSize.height / 2 + 80 - 200),
				Point(winSize.width / 2 - 80 + 200, winSize.height / 2 + 80 - 200));
			CreateNormalWall(Point(winSize.width / 2 - 80 + 200, winSize.height / 2 - 80 - 200),
				Point(winSize.width / 2 - 80 + 200, winSize.height / 2 + 80 - 200));


			CreateNormalWall(Point(winSize.width / 2 + 80 + 200, winSize.height / 2 - 80 + 200),
				Point(winSize.width / 2 + 80 + 200, winSize.height / 2 + 80 + 200));
			CreateNormalWall(Point(winSize.width / 2 - 80 + 200, winSize.height / 2 - 80 + 200),
				Point(winSize.width / 2 + 80 + 200, winSize.height / 2 - 80 + 200));
			CreateNormalWall(Point(winSize.width / 2 + 80 + 200, winSize.height / 2 + 80 + 200),
				Point(winSize.width / 2 - 80 + 200, winSize.height / 2 + 80 + 200));
			CreateNormalWall(Point(winSize.width / 2 - 80 + 200, winSize.height / 2 - 80 + 200),
				Point(winSize.width / 2 - 80 + 200, winSize.height / 2 + 80 + 200));
		}
			break;
		}
	}
		break;
	case 3:
	{
		switch (Mode)
		{
		case 1:
		{
			CreateOrganWall(Point(100, 100), Point(100, 300), 1);
			CreateNormalWall(Point(500, 300), Point(500, 400));
			CreateNormalWall(Point(500, 500), Point(500, 600));
			CreateNormalWall(Point(500, 700), Point(500, 800));
		}
			break;
		case 2:
		{
			CreateOrganWall(Point(100, 100), Point(100, 700), 2);
			CreateNormalWall(Point(50, 300), Point(50, 500));
			CreateNormalWall(Point(300, 100), Point(300, 700));
			CreateNormalWall(Point(400, 100), Point(400, 700));
			CreateNormalWall(Point(500, 100), Point(500, 700));

		}
			break;
		case 3:
		{
			CreateOrganWall(Point(200, 100), Point(200, 700), 3);


			CreateNormalWall(Point(50, 0), Point(50, 300));
			CreateNormalWall(Point(50, 500), Point(50, 800));


			CreateNormalWall(Point(300, 100), Point(300, 700));
			CreateNormalWall(Point(400, 100), Point(400, 700));
			CreateNormalWall(Point(500, 100), Point(500, 700));
		}
			break;
		case 4:
		{
			CreateNormalWall(Point(100, 100), Point(100, 200));
			CreateNormalWall(Point(500, 250), Point(500, 300));
			CreateOrganWall(Point(300, 300), Point(300, 350), 1);
			CreateNormalWall(Point(500, 350), Point(500, 400));
			CreateNormalWall(Point(500, 450), Point(500, 500));
			CreateNormalWall(Point(500, 550), Point(500, 600));
		}
			break;
		case 5:
		{
			AllowWallNumber = 5;
			CreateOrganWall(Point(100, 100), Point(100, 700), 3);
			CreateOrganWall(Point(500, 100), Point(500, 700), 3);
			CreateNormalWall(Point(250, 700), Point(350, 700));
			CreateNormalWall(Point(250, 100), Point(350, 100));
			CreateNormalWall(Point(50, 500), Point(50, 700));
			CreateNormalWall(Point(50, 100), Point(50, 300));
			CreateNormalWall(Point(550, 500), Point(550, 700));
			CreateNormalWall(Point(550, 100), Point(550, 300));
		}
			break;
		case 6:
		{
			CreateNormalWall(Point(winSize.width / 2 + 80, winSize.height / 2 - 80),
				Point(winSize.width / 2 + 80, winSize.height / 2 + 80));
			CreateNormalWall(Point(winSize.width / 2 - 80, winSize.height / 2 - 80),
				Point(winSize.width / 2 + 80, winSize.height / 2 - 80));
			CreateNormalWall(Point(winSize.width / 2 + 80, winSize.height / 2 + 80),
				Point(winSize.width / 2 - 80, winSize.height / 2 + 80));
			CreateNormalWall(Point(winSize.width / 2 - 80, winSize.height / 2 - 80),
				Point(winSize.width / 2 - 80, winSize.height / 2 + 80));


			CreateOrganWall(Point(winSize.width / 2 + 160, winSize.height / 2 - 160),
				Point(winSize.width / 2 + 160, winSize.height / 2 + 160), 2);
			CreateOrganWall(Point(winSize.width / 2 - 160, winSize.height / 2 - 160),
				Point(winSize.width / 2 + 160, winSize.height / 2 - 160), 2);
			CreateOrganWall(Point(winSize.width / 2 + 160, winSize.height / 2 + 160),
				Point(winSize.width / 2 - 160, winSize.height / 2 + 160), 2);
			CreateOrganWall(Point(winSize.width / 2 - 160, winSize.height / 2 - 160),
				Point(winSize.width / 2 - 160, winSize.height / 2 + 160), 2);



			CreateNormalWall(Point(winSize.width / 2 + 240, winSize.height / 2 - 240),
				Point(winSize.width / 2 + 240, winSize.height / 2 + 240));
			CreateNormalWall(Point(winSize.width / 2 - 240, winSize.height / 2 - 240),
				Point(winSize.width / 2 + 240, winSize.height / 2 - 240));
			CreateNormalWall(Point(winSize.width / 2 + 240, winSize.height / 2 + 240),
				Point(winSize.width / 2 - 240, winSize.height / 2 + 240));
			CreateNormalWall(Point(winSize.width / 2 - 240, winSize.height / 2 - 240),
				Point(winSize.width / 2 - 240, winSize.height / 2 + 240));
		}
			break;
		case 7:
		{
			AllowWallNumber = 1;
			CreateOrganWall(Point(30, 100), Point(315, 700), 1);
			CreateOrganWall(Point(600, 100), Point(315, 700), 2);
			CreateOrganWall(Point(600, 100), Point(30, 100), 3);
			CreateNormalWall(Point(250, 650), Point(250, 850));
			CreateNormalWall(Point(150, 200), Point(450, 200));
		}
			break;
		case 8:
		{
			AllowWallNumber = 3;
			CreateOrganWall(Point(100, 200), Point(100, 400), 3);
			CreateOrganWall(Point(100, 200), Point(300, 200), 3);
			CreateOrganWall(Point(100, 600), Point(100, 400), 3);
			CreateOrganWall(Point(300, 200), Point(500, 200), 3);
			CreateOrganWall(Point(500, 200), Point(500, 400), 3);
			CreateOrganWall(Point(500, 600), Point(500, 400), 3);
			CreateOrganWall(Point(500, 600), Point(300, 600), 3);
			CreateOrganWall(Point(100, 600), Point(300, 600), 3);

			CreateOrganWall(Point(300, 600), Point(300, 400), 2);
			CreateOrganWall(Point(500, 400), Point(300, 400), 2);
			CreateOrganWall(Point(100, 400), Point(300, 400), 2);
			CreateOrganWall(Point(300, 200), Point(300, 400), 1);

			CreateNormalWall(Point(150, 300), Point(250, 300));
			CreateNormalWall(Point(350, 300), Point(450, 300));
			CreateNormalWall(Point(150, 500), Point(250, 500));
			CreateNormalWall(Point(350, 500), Point(450, 500));


		}
			break;
		case 9:
		{
			AllowWallNumber = 3;
			CreateOrganWall(Point(100, 200), Point(250, 200), 3);
			CreateOrganWall(Point(250, 350), Point(250, 200), 3);
			CreateOrganWall(Point(250, 350), Point(100, 350), 3);
			CreateOrganWall(Point(100, 200), Point(100, 350), 3);
			CreateOrganWall(Point(400, 200), Point(550, 200), 3);
			CreateOrganWall(Point(550, 350), Point(550, 200), 3);
			CreateOrganWall(Point(550, 350), Point(400, 350), 3);
			CreateOrganWall(Point(400, 200), Point(400, 350), 3);

			CreateNormalWall(Point(120, 275), Point(230, 275));
			CreateNormalWall(Point(420, 275), Point(530, 275));
			CreateNormalWall(Point(200, 700), Point(440, 700));
		}
			break;
		case 10:
		{
			AllowWallNumber = 3;
			CreateOrganWall(Point(100, 200), Point(250, 200), 1);
			CreateOrganWall(Point(250, 200), Point(400, 200), 2);
			CreateOrganWall(Point(400, 200), Point(550, 200), 3);
			CreateOrganWall(Point(100, 400), Point(250, 400), 2);
			CreateOrganWall(Point(250, 400), Point(400, 400), 3);
			CreateOrganWall(Point(400, 400), Point(550, 400), 1);
			CreateOrganWall(Point(100, 600), Point(250, 600), 3);
			CreateOrganWall(Point(250, 600), Point(400, 600), 1);
			CreateOrganWall(Point(400, 600), Point(550, 600), 2);
			CreateNormalWall(Point(150, 300), Point(250, 300));
			CreateNormalWall(Point(400, 300), Point(500, 300));
			CreateNormalWall(Point(150, 500), Point(250, 500));
			CreateNormalWall(Point(400, 500), Point(500, 500));
		}
			break;
		}
	}
		break;
	case 4:
	{
		switch (Mode)
		{
		case 1:
		{
			CreateNormalWall(Point(100, 300), Point(300, 300));
			CreateNormalWall(Point(500, 300), Point(300, 300));
			CreateNormalWall(Point(300, 500), Point(300, 300));
			CreateNormalWall(Point(300, 100), Point(300, 300));
			CreateNormalWall(Point(100, 100), Point(300, 300));
			CreateNormalWall(Point(500, 100), Point(300, 300));
			CreateNormalWall(Point(100, 500), Point(300, 300));
			CreateNormalWall(Point(500, 500), Point(300, 300));
			AllowWallNumber = 3;
		}
			break;
		case 2:
		{
			AllowWallNumber = 1;
			CreateNormalWall(Point(500, 300), Point(500, 400));
			CreateNormalWall(Point(500, 500), Point(500, 600));
			CreateNormalWall(Point(500, 700), Point(500, 800));
		}
			break;
		case 3:
		{
			AllowWallNumber = 1;
			CreateNormalWall(Point(100, 100), Point(100, 200));
			CreateNormalWall(Point(500, 200), Point(500, 300));
			CreateNormalWall(Point(500, 350), Point(500, 450));
			CreateNormalWall(Point(500, 500), Point(500, 600));
		}
			break;
		case 4:
		{
			CreateOrganWall(Point(20, 0), Point(20, 960), 1);
			CreateOrganWall(Point(620, 0), Point(620, 960), 1);

			CreateOrganWall(Point(0, 20), Point(640, 20), 1);
			CreateOrganWall(Point(0, 940), Point(640, 940), 1);

			CreateOrganWall(Point(320, 0), Point(320, 300), 1);

			CreateNormalWall(Point(winSize.width / 2 + 80 - 200, winSize.height / 2 - 80 - 200),
				Point(winSize.width / 2 + 80 - 200, winSize.height / 2 + 80 - 200));
			CreateNormalWall(Point(winSize.width / 2 - 80 - 200, winSize.height / 2 - 80 - 200),
				Point(winSize.width / 2 + 80 - 200, winSize.height / 2 - 80 - 200));
			CreateNormalWall(Point(winSize.width / 2 + 80 - 200, winSize.height / 2 + 80 - 200),
				Point(winSize.width / 2 - 80 - 200, winSize.height / 2 + 80 - 200));
			CreateNormalWall(Point(winSize.width / 2 - 80 - 200, winSize.height / 2 - 80 - 200),
				Point(winSize.width / 2 - 80 - 200, winSize.height / 2 + 80 - 200));


			CreateNormalWall(Point(winSize.width / 2 + 80 - 200, winSize.height / 2 - 80 + 200),
				Point(winSize.width / 2 + 80 - 200, winSize.height / 2 + 80 + 200));
			CreateNormalWall(Point(winSize.width / 2 - 80 - 200, winSize.height / 2 - 80 + 200),
				Point(winSize.width / 2 + 80 - 200, winSize.height / 2 - 80 + 200));
			CreateNormalWall(Point(winSize.width / 2 + 80 - 200, winSize.height / 2 + 80 + 200),
				Point(winSize.width / 2 - 80 - 200, winSize.height / 2 + 80 + 200));
			CreateNormalWall(Point(winSize.width / 2 - 80 - 200, winSize.height / 2 - 80 + 200),
				Point(winSize.width / 2 - 80 - 200, winSize.height / 2 + 80 + 200));

			CreateNormalWall(Point(winSize.width / 2 + 80 + 200, winSize.height / 2 - 80 + 200),
				Point(winSize.width / 2 + 80 + 200, winSize.height / 2 + 80 + 200));
			CreateNormalWall(Point(winSize.width / 2 - 80 + 200, winSize.height / 2 - 80 + 200),
				Point(winSize.width / 2 + 80 + 200, winSize.height / 2 - 80 + 200));
			CreateNormalWall(Point(winSize.width / 2 + 80 + 200, winSize.height / 2 + 80 + 200),
				Point(winSize.width / 2 - 80 + 200, winSize.height / 2 + 80 + 200));
			CreateNormalWall(Point(winSize.width / 2 - 80 + 200, winSize.height / 2 - 80 + 200),
				Point(winSize.width / 2 - 80 + 200, winSize.height / 2 + 80 + 200));
		}
			break;
		case 5:
		{
			CreateOrganWall(Point(150, 300), Point(200, 400), 1);
			CreateOrganWall(Point(450, 300), Point(400, 400), 1);
			CreateOrganWall(Point(225, 100), Point(375, 100), 1);
			CreateNormalWall(Point(100, 110), Point(150, 110));
			CreateNormalWall(Point(500, 110), Point(550, 110));
			CreateNormalWall(Point(300, 500), Point(300, 450));
		}
			break;
		case 6:
		{
			AllowWallNumber = 1;
			CreateOrganWall(Point(450, 300), Point(400, 400), 1);
			CreateOrganWall(Point(225, 100), Point(375, 100), 1);
			CreateNormalWall(Point(100, 110), Point(150, 110));
			CreateNormalWall(Point(500, 110), Point(550, 110));
			CreateNormalWall(Point(300, 500), Point(300, 450));
		}
			break;
		case 7:
		{
			AllowWallNumber = 1;
			CreateNormalWall(Point(30, 30), Point(610, 30));
			CreateNormalWall(Point(30, 920), Point(610, 920));
			CreateOrganWall(Point(50, 350), Point(50, 550), 1);
			CreateOrganWall(Point(550, 350), Point(550, 550), 1);
			CreateOrganWall(Point(220, 50), Point(420, 50), 1);
			CreateOrganWall(Point(220, 900), Point(420, 900), 1);

			//320 450
			CreateNormalWall(Point(220, 450), Point(320, 450));
			CreateNormalWall(Point(420, 450), Point(320, 450));
			CreateNormalWall(Point(320, 550), Point(320, 450));
			CreateNormalWall(Point(320, 350), Point(320, 450));
		}
			break;
		case 8:
		{
			AllowWallNumber = 1;
			CreateNormalWall(Point(30, 30), Point(610, 30));
			CreateNormalWall(Point(30, 920), Point(610, 920));
			CreateOrganWall(Point(50, 350), Point(50, 550), 1);
			CreateOrganWall(Point(550, 350), Point(550, 550), 1);
			CreateOrganWall(Point(220, 50), Point(420, 50), 1);
			CreateOrganWall(Point(220, 900), Point(420, 900), 1);

			CreateNormalWall(Point(100, 100), Point(100, 250));
			CreateNormalWall(Point(100, 450), Point(100, 300));
			CreateNormalWall(Point(100, 500), Point(100, 650));


			CreateNormalWall(Point(480, 100), Point(480, 250));
			CreateNormalWall(Point(480, 450), Point(480, 300));
			CreateNormalWall(Point(480, 500), Point(480, 650));
		}
			break;
		case 9:
		{
			CreateNormalWall(Point(100, 100), Point(100, 250));
			CreateNormalWall(Point(100, 450), Point(100, 300));
			CreateNormalWall(Point(100, 500), Point(100, 650));


			CreateNormalWall(Point(480, 100), Point(480, 250));
			CreateNormalWall(Point(480, 450), Point(480, 300));
			CreateNormalWall(Point(480, 500), Point(480, 650));

			CreateOrganWall(Point(290, 300), Point(290, 400), 1);
			CreateOrganWall(Point(100, 650), Point(480, 650), 1);
		}
			break;
		case 10:
		{
			CreateNormalWall(Point(100, 100), Point(100, 250));
			CreateNormalWall(Point(100, 450), Point(100, 300));
			CreateNormalWall(Point(100, 500), Point(100, 650));


			CreateNormalWall(Point(480, 100), Point(480, 250));
			CreateNormalWall(Point(480, 450), Point(480, 300));
			CreateNormalWall(Point(480, 500), Point(480, 650));

			CreateOrganWall(Point(290, 300), Point(290, 400), 1);
			AllowWallNumber = 1;
		}
			break;
		}
	}
		break;
	case 5:
	{
		switch (Mode)
		{
		case 1:
		{
			AllowWallNumber = 2;
			CreateNormalWall(Point(100, 300), Point(300, 300));
			CreateNormalWall(Point(500, 300), Point(300, 300));
			CreateNormalWall(Point(300, 500), Point(300, 300));
			CreateNormalWall(Point(300, 100), Point(300, 300));
		}
			break;
		case 2:
		{
			AllowWallNumber = 1;
			CreateNormalWall(Point(234, 546), Point(267, 598));
			CreateNormalWall(Point(465, 746), Point(417, 898));
		}
			break;
		case 3:
		{
			AllowWallNumber = 10;
			CreateNormalWall(Point(234, 546), Point(267, 598));
			CreateNormalWall(Point(465, 746), Point(417, 898));
			CreateNormalWall(Point(365, 146), Point(317, 198));
		}
			break;
		case 4:
		{
			AllowWallNumber = 10;

			CreateNormalWall(Point(500, 100), Point(500, 200));
			CreateNormalWall(Point(500, 250), Point(500, 350));
			CreateNormalWall(Point(500, 400), Point(500, 500));
			CreateNormalWall(Point(500, 550), Point(500, 650));
			CreateNormalWall(Point(500, 700), Point(500, 850));
		}
			break;
		case 5:
		{
			AllowWallNumber = 10;
			CreateOrganWall(Point(winSize.width / 2 + 80, winSize.height / 2 - 80),
				Point(winSize.width / 2 + 80, winSize.height / 2 + 80), 2);
			CreateOrganWall(Point(winSize.width / 2 - 80, winSize.height / 2 - 80),
				Point(winSize.width / 2 + 80, winSize.height / 2 - 80), 2);
			CreateOrganWall(Point(winSize.width / 2 + 80, winSize.height / 2 + 80),
				Point(winSize.width / 2 - 80, winSize.height / 2 + 80), 2);
			CreateOrganWall(Point(winSize.width / 2 - 80, winSize.height / 2 - 80),
				Point(winSize.width / 2 - 80, winSize.height / 2 + 80), 2);


			CreateOrganWall(Point(winSize.width / 2 + 160, winSize.height / 2 - 160),
				Point(winSize.width / 2 + 160, winSize.height / 2 + 160), 2);
			CreateOrganWall(Point(winSize.width / 2 - 160, winSize.height / 2 - 160),
				Point(winSize.width / 2 + 160, winSize.height / 2 - 160), 2);
			CreateOrganWall(Point(winSize.width / 2 + 160, winSize.height / 2 + 160),
				Point(winSize.width / 2 - 160, winSize.height / 2 + 160), 2);
			CreateOrganWall(Point(winSize.width / 2 - 160, winSize.height / 2 - 160),
				Point(winSize.width / 2 - 160, winSize.height / 2 + 160), 2);



			CreateOrganWall(Point(winSize.width / 2 + 240, winSize.height / 2 - 240),
				Point(winSize.width / 2 + 240, winSize.height / 2 + 240), 2);
			CreateOrganWall(Point(winSize.width / 2 - 240, winSize.height / 2 - 240),
				Point(winSize.width / 2 + 240, winSize.height / 2 - 240), 2);
			CreateOrganWall(Point(winSize.width / 2 + 240, winSize.height / 2 + 240),
				Point(winSize.width / 2 - 240, winSize.height / 2 + 240), 2);
			CreateOrganWall(Point(winSize.width / 2 - 240, winSize.height / 2 - 240),
				Point(winSize.width / 2 - 240, winSize.height / 2 + 240), 2);


			CreateNormalWall(Point(winSize.width / 2 + 100, winSize.height / 2 + 200),
				Point(winSize.width / 2 + 200, winSize.height / 2 + 200));
			CreateNormalWall(Point(winSize.width / 2 - 100, winSize.height / 2 - 200),
				Point(winSize.width / 2 - 200, winSize.height / 2 - 200));
			CreateNormalWall(Point(winSize.width / 2 - 200, winSize.height / 2 + 200),
				Point(winSize.width / 2 - 100, winSize.height / 2 + 200));
			CreateNormalWall(Point(winSize.width / 2 + 100, winSize.height / 2 - 200),
				Point(winSize.width / 2 + 200, winSize.height / 2 - 200));


		}
			break;
		case 6:
		{
			CreateNormalWall(Point(60, 100), Point(60, 900));
			CreateNormalWall(Point(600, 100), Point(600, 900));

			CreateNormalWall(Point(600, 200), Point(60, 200));
			CreateOrganWall(Point(600, 300), Point(60, 300), 2);
			CreateNormalWall(Point(600, 400), Point(60, 400));
			CreateOrganWall(Point(600, 500), Point(60, 500), 2);
			CreateNormalWall(Point(600, 600), Point(60, 600));
			CreateOrganWall(Point(600, 700), Point(60, 700), 2);
			CreateNormalWall(Point(600, 800), Point(60, 800));
			CreateOrganWall(Point(600, 900), Point(60, 900), 2);
			CreateOrganWall(Point(600, 100), Point(60, 100), 2);
		}
			break;
		case 7:
		{
			CreateOrganWall(Point(300, 50), Point(300, 800), 2);
			CreateNormalWall(Point(100, 650), Point(100, 750));
			CreateNormalWall(Point(100, 800), Point(100, 900));
			CreateNormalWall(Point(550, 400), Point(550, 500));
			CreateNormalWall(Point(550, 250), Point(550, 350));
		}
			break;
		case 8:
		{
			CreateNormalWall(Point(100, 100), Point(100, 700));
			CreateNormalWall(Point(100, 100), Point(500, 100));
			CreateNormalWall(Point(500, 700), Point(500, 100));
			CreateNormalWall(Point(500, 700), Point(100, 700));
			CreateOrganWall(Point(300, 100), Point(300, 700), 2);
			CreateOrganWall(Point(100, 400), Point(500, 400), 2);
		}
			break;
		case 9:
		{
			AllowWallNumber = 1;
			CreateNormalWall(Point(100, 650), Point(100, 750));
			CreateNormalWall(Point(100, 800), Point(100, 900));
			CreateNormalWall(Point(550, 450), Point(550, 550));
			CreateNormalWall(Point(550, 300), Point(550, 400));

		}
			break;
		case 10:
		{
			AllowWallNumber = 8000;
			CreateNormalWall(Point(100, 300), Point(300, 300));
			CreateNormalWall(Point(500, 300), Point(300, 300));
			CreateNormalWall(Point(300, 500), Point(300, 300));
			CreateNormalWall(Point(300, 100), Point(300, 300));
			CreateNormalWall(Point(100, 100), Point(300, 300));
			CreateNormalWall(Point(500, 100), Point(300, 300));
			CreateNormalWall(Point(100, 500), Point(300, 300));
			CreateNormalWall(Point(500, 500), Point(300, 300));
		}
			break;
		}
	}
		break;
	case 6:
	{
		switch (Mode)
		{
		case 1:
		{

			CreateNormalWall(Point(60, 100), Point(60, 900));
			CreateNormalWall(Point(600, 100), Point(600, 900));

			CreateNormalWall(Point(600, 200), Point(60, 200));
			CreateOrganWall(Point(600, 300), Point(60, 300), 3);
			CreateNormalWall(Point(600, 400), Point(60, 400));
			CreateOrganWall(Point(600, 500), Point(60, 500), 3);
			CreateNormalWall(Point(600, 600), Point(60, 600));
			CreateOrganWall(Point(600, 700), Point(60, 700), 3);
			CreateNormalWall(Point(600, 800), Point(60, 800));
			CreateOrganWall(Point(600, 900), Point(60, 900), 3);
			CreateOrganWall(Point(600, 100), Point(60, 100), 3);
		}
			break;
		case 2:
		{
			CreateOrganWall(Point(100, 100), Point(540, 100), 3);
			CreateOrganWall(Point(100, 900), Point(540, 900), 3);
			CreateOrganWall(Point(100, 100), Point(100, 900), 3);
			CreateOrganWall(Point(540, 100), Point(540, 900), 3);

			CreateNormalWall(Point(100, 50), Point(540, 50));
			CreateNormalWall(Point(100, 930), Point(540, 930));
			CreateNormalWall(Point(50, 100), Point(50, 900));
			CreateNormalWall(Point(590, 100), Point(590, 900));
		}
			break;
		case 3:
		{
			AllowWallNumber = 1;
			CreateOrganWall(Point(200, 200), Point(400, 400), 3);
			CreateOrganWall(Point(400, 200), Point(200, 400), 3);
			CreateNormalWall(Point(200, 200), Point(200, 400));
			CreateNormalWall(Point(400, 200), Point(400, 400));
			CreateNormalWall(Point(200, 400), Point(400, 400));
			CreateNormalWall(Point(200, 200), Point(400, 200));
		}
			break;
		case 4:
		{
			CreateNormalWall(Point(100, 100), Point(540, 100));
			CreateNormalWall(Point(100, 100), Point(250, 400));
			CreateNormalWall(Point(390, 400), Point(540, 100));
			CreateOrganWall(Point(250, 400), Point(390, 400), 3);
			CreateNormalWall(Point(100, 700), Point(540, 700));
			CreateNormalWall(Point(100, 700), Point(250, 400));
			CreateNormalWall(Point(390, 400), Point(540, 700));
		}
			break;
		case 5:
		{
			CreateNormalWall(Point(200, 200), Point(400, 400));
			CreateOrganWall(Point(400, 200), Point(200, 400), 3);
			CreateNormalWall(Point(200, 200), Point(200, 400));
			CreateNormalWall(Point(400, 200), Point(400, 400));
			CreateOrganWall(Point(200, 400), Point(400, 400), 3);
			CreateOrganWall(Point(200, 200), Point(400, 200), 3);
		}
			break;
		case 6:
		{
			CreateNormalWall(Point(winSize.width / 2 - 160, winSize.height / 2),
				Point(winSize.width / 2 - 80, winSize.height / 2 + 160));
			CreateNormalWall(Point(winSize.width / 2 - 80, winSize.height / 2 + 160),
				Point(winSize.width / 2 + 80, winSize.height / 2 + 160));
			CreateNormalWall(Point(winSize.width / 2 + 80, winSize.height / 2 + 160),
				Point(winSize.width / 2 + 160, winSize.height / 2));
			CreateNormalWall(Point(winSize.width / 2 + 160, winSize.height / 2),
				Point(winSize.width / 2 + 80, winSize.height / 2 - 160));
			CreateNormalWall(Point(winSize.width / 2 + 80, winSize.height / 2 - 160),
				Point(winSize.width / 2 - 80, winSize.height / 2 - 160));
			CreateNormalWall(Point(winSize.width / 2 - 80, winSize.height / 2 - 160),
				Point(winSize.width / 2 - 160, winSize.height / 2));
			CreateOrganWall(Point(winSize.width / 2 - 80, winSize.height / 2 + 160),
				Point(winSize.width / 2 + 80, winSize.height / 2 - 160), 3);
		}
			break;
		case 7:
		{
			CreateNormalWall(Point(100, 100), Point(540, 100));
			CreateNormalWall(Point(100, 800), Point(540, 800));
			CreateNormalWall(Point(100, 200), Point(200, 200));
			CreateNormalWall(Point(540, 200), Point(440, 200));
			CreateNormalWall(Point(100, 700), Point(200, 700));
			CreateNormalWall(Point(540, 700), Point(440, 700));
			CreateNormalWall(Point(100, 200), Point(100, 700));
			CreateNormalWall(Point(540, 200), Point(540, 700));
			CreateOrganWall(Point(320, 200), Point(320, 700), 3);
		}
			break;
		case 8:
		{
			AllowWallNumber = 10;
			CreateNormalWall(Point(100, 100), Point(540, 100));
			CreateNormalWall(Point(100, 800), Point(540, 800));
			CreateNormalWall(Point(100, 200), Point(200, 200));
			CreateNormalWall(Point(540, 200), Point(440, 200));
			CreateNormalWall(Point(100, 700), Point(200, 700));
			CreateNormalWall(Point(540, 700), Point(440, 700));
			CreateNormalWall(Point(200, 200), Point(200, 700));
			CreateNormalWall(Point(440, 200), Point(440, 700));
			CreateOrganWall(Point(320, 200), Point(320, 700), 3);
		}
			break;
		case 9:
		{
			CreateNormalWall(Point(100, 100), Point(540, 100));
			CreateNormalWall(Point(100, 800), Point(540, 800));
			CreateNormalWall(Point(100, 200), Point(200, 200));
			CreateNormalWall(Point(540, 200), Point(440, 200));
			CreateNormalWall(Point(100, 700), Point(200, 700));
			CreateNormalWall(Point(540, 700), Point(440, 700));
			CreateNormalWall(Point(100, 200), Point(100, 700));
			CreateNormalWall(Point(540, 200), Point(540, 700));
			CreateOrganWall(Point(250, 200), Point(390, 200), 3);
			CreateOrganWall(Point(250, 700), Point(390, 700), 3);
		}
			break;
		case 10:
		{
			AllowWallNumber = 8000;
			CreateOrganWall(Point(100, 100), Point(100, 250), 3);
			CreateOrganWall(Point(100, 400), Point(100, 250), 3);
			CreateOrganWall(Point(100, 400), Point(100, 550), 3);


			CreateOrganWall(Point(100, 550), Point(250, 550), 3);
			CreateOrganWall(Point(400, 550), Point(250, 550), 3);
			CreateOrganWall(Point(400, 550), Point(550, 550), 3);


			CreateOrganWall(Point(100, 100), Point(250, 100), 3);
			CreateOrganWall(Point(400, 100), Point(250, 100), 3);
			CreateOrganWall(Point(400, 100), Point(550, 100), 3);


			CreateOrganWall(Point(550, 100), Point(550, 250), 3);
			CreateOrganWall(Point(550, 400), Point(550, 250), 3);
			CreateOrganWall(Point(550, 400), Point(550, 550), 3);


			CreateOrganWall(Point(250, 100), Point(250, 250), 3);
			CreateOrganWall(Point(250, 400), Point(250, 250), 3);
			CreateOrganWall(Point(250, 400), Point(250, 550), 3);


			CreateOrganWall(Point(400, 100), Point(400, 250), 3);
			CreateOrganWall(Point(400, 400), Point(400, 250), 3);
			CreateOrganWall(Point(400, 400), Point(400, 550), 3);


			CreateOrganWall(Point(100, 250), Point(250, 250), 3);
			CreateOrganWall(Point(400, 250), Point(250, 250), 3);
			CreateOrganWall(Point(400, 250), Point(550, 250), 3);


			CreateOrganWall(Point(100, 400), Point(250, 400), 3);
			CreateOrganWall(Point(400, 400), Point(250, 400), 3);
			CreateOrganWall(Point(400, 400), Point(550, 400), 3);

			CreateNormalWall(Point(125, 175), Point(225, 175));
			CreateNormalWall(Point(125, 475), Point(225, 475));
			CreateNormalWall(Point(425, 175), Point(525, 175));
			CreateNormalWall(Point(425, 475), Point(525, 475));



		}
			break;
		}
	}
	}
}