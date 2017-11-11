#include "MenuScene.h"
#include "GameScene.h"
#include <math.h>

#define PI acos( -1.0 )
USING_NS_CC;
Scene* GameScene::createScene()
{
	// 'scene' is an autorelease object
	auto scene = Scene::create();

	// 'layer' is an autorelease object
	auto layer = GameScene::create();

	// add layer as a child to scene
	scene->addChild(layer);

	// return the scene
	return scene;
}
bool GameScene::init()
{
	auto listener1 = EventListenerKeyboard::create();
	listener1->onKeyReleased = [this](EventKeyboard::KeyCode key, Event*)
	{
		if (EventKeyboard::KeyCode::KEY_RETURN == key || EventKeyboard::KeyCode::KEY_ESCAPE == key || EventKeyboard::KeyCode::KEY_BACKSPACE == key)
		{
			auto scene = TransitionFadeTR::create(0.5, MenuScene::createScene());
			Director::getInstance()->replaceScene(scene);
		}
	};
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener1, this);
	winSize = Director::getInstance()->getWinSize();
	MinTime = UserDefault::getInstance()->getDoubleForKey("MinTime", 10000000);
	MinWall = UserDefault::getInstance()->getIntegerForKey("MinWall", 100000);
	//gra = UserDefault::getInstance()->getIntegerForKey("gra", 0);
	//speed = UserDefault::getInstance()->getIntegerForKey("speed", 0);
	//iter = UserDefault::getInstance()->getIntegerForKey("iter", 0);
	//gra = -gra;
	if (!Layer::init())
		return false;

	// 注册单点触摸  
	dispatcher = this->getEventDispatcher();
	listener = EventListenerTouchOneByOne::create();
	listener->onTouchBegan = CC_CALLBACK_2(GameScene::onTouchBegan, this);
	// 触摸开始  
	listener->onTouchMoved = CC_CALLBACK_2(GameScene::onTouchMoved, this);
	listener->onTouchEnded = CC_CALLBACK_2(GameScene::onTouchEnded, this);
	// 触摸移动 
	dispatcher->addEventListenerWithSceneGraphPriority(listener, this);

	InitGameData();
	return true;
}
void GameScene::InitGameData()
{
	wi = 0;
	auto spr = Sprite::create("BG.jpg");
	spr->setScaleX(Director::getInstance()->getWinSize().width/1795); 
	spr->setScaleY(Director::getInstance()->getWinSize().height/2320); 
	spr->setPosition(Point(Director::getInstance()->getWinSize().width / 2, Director::getInstance()->getWinSize().height / 2));
	this->addChild(spr);
	prespr = Sprite::create("wall.jpg", Rect(0, 0, 100, 5));
	prespr->setAnchorPoint(Point(0.5, 0.5));
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
	w = 0;
	t = 0;
	go = false;
	WallNumber = 0;
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



	star->setAnchorPoint(Point(0.5, 0.5));
	star->setPosition(winSize.width / 2, winSize.height / 2);
	this->addChild(star);
	scheduleUpdate();
	Game = UserDefault::getInstance()->getIntegerForKey("Game", 0);
	if (!Game)
	{
		Tech();
	}
}
bool GameScene::onTouchBegan(Touch* pTouch, Event* pEvent)
{
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
void GameScene::onTouchMoved(Touch* pTouch, Event* pEvent)
{

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
void GameScene::onTouchEnded(Touch* pTouch, Event* pEvent)
{
	if (w)
		return;
	if (!Game)
		return;
	if (go)
	{
		End = pTouch->getLocation();
		CreateWall();
		WallNumber++;
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
void GameScene::update(float dt)
{
	if (updat && go)
	{
		unscheduleUpdate();
		return;
	}
	if (!go)
	{
		streak->setPosition(star->getPosition());
		mypat->setPosition(star->getPosition());
		return;
	}
	updat = 1;
	//使用固定的时间间隔将物理模拟向前推进一步 
	Sprite* sprite = (Sprite*)mBallBody->GetUserData();
	for (int i = 0; i < iter; i++)
	{
		mWorld->Step(timeStep / iter, velocityIterations, positionIterations);
		b2Vec2 pos = mBallBody->GetPosition();
		double x = pos.x * PTM_RATIO;
		double y = pos.y * PTM_RATIO;
		if (fabs(lastx - x) < eps && fabs(lasty - y) < eps)
		{
			t++;
		}
		else
		{
			t = 0;
		}
		if (t > iter)
		{
			wi = 1;
			break;
			//int f = 0;
			//mworld->step(timestep / iter*(iter - i) / 2, velocityiterations, positioniterations);
			//b2vec2 pos = mballbody->getposition();
			//double xx = pos.x * ptm_ratio;
			//double yy = pos.y * ptm_ratio;
			//if (fabs(xx - x) > eps || fabs(yy - y) > eps)
			//{
			//	f = 1;
			//}
			//mworld->step(timestep / iter*(iter - i) / 2, velocityiterations, positioniterations);
			//pos = mballbody->getposition();
			//xx = pos.x * ptm_ratio;
			//yy = pos.y * ptm_ratio;
			//if (fabs(xx - x) > eps || fabs(yy - y) > eps)
			//{
			//	f = 1;
			//}
			//if (f == 0)
			//{
			//	wi = 1;
			//	break;
			//}
		}
		lastx = x;
		lasty = y;
	}
	b2Vec2 pos = mBallBody->GetPosition();
	double x = pos.x * PTM_RATIO;
	double y = pos.y * PTM_RATIO;
	sprite->setPosition(Point(x, y));
	float angle = mBallBody->GetAngle();
	sprite->setRotation(angle);
	streak->setPosition(star->getPosition());
	mypat->setPosition(star->getPosition());
	if (wi == 1)
	{
		win();
	}
	updat = 0;
}
void GameScene::CreateWall()
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
	this->addChild(spr);
	double rad = theta*PI / 180;


	b2BodyDef WallDef;
	WallDef.type = b2_staticBody;
	double wx = (Start.x + End.x) / 2;
	double wy = (Start.y + End.y) / 2;
	WallDef.position.Set(wx / PTM_RATIO, wy / PTM_RATIO);
	WallDef.angle = rad *1.0f;


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
void GameScene::win()
{
	unscheduleUpdate();
	w = 1;
	wintime = getMillSecond();
	Sprite* spr;
	Time = wintime - inittime;
	if (Time < 3000 || WallNumber <= 3)
	{
		spr = Sprite::create("hong.png");
	}
	else if (Time <= 5000 || WallNumber <= 5)
	{
		spr = Sprite::create("qing.png");
	}
	else
	{
		spr = Sprite::create("lan2.png");
	}

	spr->setScaleY(1.2);
	auto a = FadeIn::create(0.5);
	spr->setOpacity(0);
	spr->runAction(a);
	spr->setPosition(winSize.width / 2, winSize.height / 2);

	this->addChild(spr);


	auto label_wall = Label::createWithSystemFont("", "", 30);
	label_wall->setPosition(winSize.width / 2, winSize.height / 2 + 80);
	label_wall->setColor(Color3B::BLACK);
	label_wall->setString(StringUtils::format("木棒:%d", WallNumber));
	this->addChild(label_wall);
	auto label_time = Label::createWithSystemFont("", "", 30);
	label_time->setPosition(winSize.width / 2, winSize.height / 2 + 40);
	label_time->setColor(Color3B::BLACK);
	label_time->setString(StringUtils::format("时间:%.2lf", Time));
	this->addChild(label_time);

	if (WallNumber < MinWall)
	{
		MinWall = WallNumber;
		UserDefault::getInstance()->setIntegerForKey("MinWall", MinWall);
		UserDefault::getInstance()->flush();
	}
	if (Time < MinTime)
	{
		MinTime = Time;
		UserDefault::getInstance()->setDoubleForKey("MinTime", MinTime);
		UserDefault::getInstance()->flush();
	}
	auto label_minwall = Label::createWithSystemFont("", "", 30);
	label_minwall->setPosition(winSize.width / 2, winSize.height / 2 - 40);
	label_minwall->setColor(Color3B::BLACK);
	label_minwall->setString(StringUtils::format("最少木棒:%d", MinWall));
	this->addChild(label_minwall);
	auto label_mintime = Label::createWithSystemFont("", "", 30);
	label_mintime->setPosition(winSize.width / 2, winSize.height / 2 - 80);
	label_mintime->setColor(Color3B::BLACK);
	label_mintime->setString(StringUtils::format("最短时间:%.2lf", MinTime));
	this->addChild(label_mintime);



	WinMenu();
}
void GameScene::WinMenu()
{
	auto item_0 = MenuItemImage::create("CS.png", "CSS.png", CC_CALLBACK_1(GameScene::ReStart, this));
	auto item_2 = MenuItemImage::create("FH.png", "FHH.png", CC_CALLBACK_1(GameScene::Return, this));

	item_0->setTag(0);
	item_2->setTag(2);

	item_0->setColor(Color3B::WHITE);
	item_2->setColor(Color3B::WHITE);

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
void GameScene::ReStart(Ref *sender)
{
	delete mWorld;
	this->removeAllChildrenWithCleanup(1);
	InitGameData();
}
void GameScene::First(Ref *sender)
{
	delete mWorld;
	this->removeAllChildrenWithCleanup(1);
	Game = 1;
	UserDefault::getInstance()->setIntegerForKey("Game", 1);
	UserDefault::getInstance()->flush();
	InitGameData();
}
void GameScene::Return(Ref *sender)
{
	delete mWorld;
	auto scene = TransitionFadeTR::create(0.5, MenuScene::createScene());
	Director::getInstance()->replaceScene(scene);
}
double GameScene::getMillSecond()
{
	struct timeval tv;
	gettimeofday(&tv, nullptr);
	return (double)tv.tv_sec * 1000 + (double)tv.tv_usec / 1000;
}
void GameScene::Tech()
{
	auto spr = Sprite::create("bai.png");
	spr->setScale(5);
	spr->setPosition(winSize.width / 2, winSize.height / 2);
	this->addChild(spr);
	auto label_tech = Label::createWithSystemFont
		("捕捉模式：\n拖动屏幕移动并释放小球，之后拖动屏幕划出木棒困住小球即可", "", 40, Size(500, 300));
	label_tech->setPosition(winSize.width / 2, winSize.height / 2);
	label_tech->setColor(Color3B::BLACK);
	this->addChild(label_tech);
	auto item_0 = MenuItemImage::create("ZDL.png", "ZDLL.png", CC_CALLBACK_1(GameScene::First, this));
	Menu *menu = Menu::create(item_0, NULL);
	menu->alignItemsHorizontallyWithPadding(50);
	menu->setPosition(Point(Director::getInstance()->getWinSize().width / 2, Director::getInstance()->getWinSize().height * 1 / 3));
	menu->setVisible(true);
	this->addChild(menu);
}