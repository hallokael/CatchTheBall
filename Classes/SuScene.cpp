#include "MenuScene.h"
#include "SuScene.h"
#include <math.h>
#define PI acos( -1.0 )
USING_NS_CC;
Scene* SuScene::createScene()
{
	// 'scene' is an autorelease object
	auto scene = Scene::create();

	// 'layer' is an autorelease object
	auto layer = SuScene::create();

	// add layer as a child to scene
	scene->addChild(layer);

	// return the scene
	return scene;
}
bool SuScene::init()
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
	MinTime = UserDefault::getInstance()->getDoubleForKey("MaxTime", 0);
	MinWall = UserDefault::getInstance()->getIntegerForKey("MaxWall", 0);
	if (!Layer::init())
		return false;

	// ע�ᵥ�㴥��  
	dispatcher = this->getEventDispatcher();
	listener = EventListenerTouchOneByOne::create();
	listener->onTouchBegan = CC_CALLBACK_2(SuScene::onTouchBegan, this);
	// ������ʼ  
	listener->onTouchMoved = CC_CALLBACK_2(SuScene::onTouchMoved, this);
	listener->onTouchEnded = CC_CALLBACK_2(SuScene::onTouchEnded, this);
	// �����ƶ� 
	dispatcher->addEventListenerWithSceneGraphPriority(listener, this);


	InitGameData();
	return true;
}
void SuScene::InitGameData()
{
	q = 0; 
	NowWallNumber = 0;
	auto spr = Sprite::create("BG.jpg");
	spr->setScaleX(Director::getInstance()->getWinSize().width/1795); 
	spr->setScaleY(Director::getInstance()->getWinSize().height/2320); 
	spr->setPosition(Point(Director::getInstance()->getWinSize().width / 2, Director::getInstance()->getWinSize().height / 2));
	this->addChild(spr);
	prespr = Sprite::create("wall.jpg", Rect(0, 0, 100, 5));
	prespr->setAnchorPoint(Point(0.5, 0.5));
	this->addChild(prespr);
	gravity.Set(0, gra); //һ������10��λ����������Ϊ�������ٶȣ�Box2D��Ĭ�ϵĵ�λ�������  
	mWorld = new b2World(gravity); // ����һ�����������ٶȵ�����  
	b2BodyDef bodyDef;
	b2BodyDef bodyDef2;
	b2CircleShape bodyShape;
	b2PolygonShape bodyShape2;
	b2FixtureDef bodyFixture;
	b2FixtureDef HFixture;
	b2Body * bottomBorder;
	b2Body * bottomBorder2;
	b2PolygonShape borderShape; // һ�����ε���״  
	b2FixtureDef borderFixture; // һ��������  
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

	// ���Ǿ���Sprtie     
	star = Sprite::create("ball.png");
	star->setTag(1000005);
	// ������βMotionStreak  
	streak = MotionStreak::create(0.5f, 1, 28, Color3B::WHITE, "steak.png");

	//����
	//streak->setFastMode(false); 
	//streak = MotionStreak::create(0.5f, 1, 10, Color3B::RED, "ball.png");  
	streak->setPosition(star->getPosition());
	// ������βstreak��λ��  
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

	//һ������Ķ���  
	bodyDef.type = b2_staticBody; //��������ͣ������ģ���Ӳ��~ ���԰����������嵱�ɵ���  

	//����ذ�  
	bodyDef.position.Set(0, -90 / PTM_RATIO); // �ذ���0��0λ��  
	borderShape.SetAsBox(winSize.width / PTM_RATIO, 100 / PTM_RATIO); //���ó��Ⱥ͸߶ȣ����������ĵذ������X�ᣬ��һ����  
	borderFixture.shape = &borderShape;
	bottomBorder = mWorld->CreateBody(&bodyDef); //�������д���һ�����壨���棩 
	bottomBorder->CreateFixture(&borderFixture);          //���Ƶ������״ 


	bodyDef2.type = b2_staticBody;
	bodyDef2.position.Set(0, winSize.height / PTM_RATIO + 90.0 / PTM_RATIO);
	bottomBorder2 = mWorld->CreateBody(&bodyDef2);
	bottomBorder2->CreateFixture(&borderFixture);


	bodyShape2.SetAsBox(100 / PTM_RATIO, winSize.height / PTM_RATIO); //���ó��Ⱥ͸߶ȣ����������ĵذ������X�ᣬ��һ����  
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
	this->addChild(star);
	scheduleUpdate();
	Su = UserDefault::getInstance()->getIntegerForKey("Su", 0);
	if (!Su)
	{
		Tech();
	}
}
bool SuScene::onTouchBegan(Touch* pTouch, Event* pEvent)
{
	if (go)
	{
		Start = pTouch->getLocation();
		return true;
	}

	// ��ȡ������λ��    
	Vec2 pos = pTouch->getLocation();
	// ����λ��    
	star->setPosition(pos);
	// ɾ�����л������  
	streak->reset();
	return true;
}
void SuScene::onTouchMoved(Touch* pTouch, Event* pEvent)
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
	// �����ƶ���ƫ����   
	Vec2 delta = pTouch->getDelta();
	// ����λ��    
	if (!(delta.x == 0 && delta.y == 0))
		Delta = delta;
	star->setPosition(star->getPosition() + delta);
}
void SuScene::onTouchEnded(Touch* pTouch, Event* pEvent)
{
	if (w)
		return;
	if (!Su)
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
	bodyDef.type = b2_dynamicBody; //С���ǿ��Զ���  
	bodyDef.bullet = true;
	bodyDef.userData = star;    //��ֻ��Ϊ�˱������ݣ�����ͨ�������ҵ���Ӧ�ľ���  
	bodyDef.linearDamping = 0.0f; //���ٶ�Ϊ0  
	bodyDef.position.Set(star->getPositionX() / PTM_RATIO, star->getPositionY() / PTM_RATIO); //��ʼλ��  
	mBallBody = mWorld->CreateBody(&bodyDef); // ��Box2D�����д���һ������  
	b2Vec2 Speed;
	Speed.x = speed *(co);
	Speed.y = speed*(si);
	mBallBody->SetLinearVelocity(Speed);
	mBallBody->SetBullet(true);
	mBallBody->SetFixedRotation(true);
	//12.0f
	bodyShape.m_radius = 13.0f / PTM_RATIO;
	//С��Ķ�����  
	bodyFixture.density = 1;  // �ܶ�  
	bodyFixture.shape = &bodyShape; //��״  
	bodyFixture.friction = 0.0f; //Ħ��������Ϊ���������û��������Ħ��������û��  
	bodyFixture.restitution = 1.0f; //������100%����~~~  
	mBallBody->CreateFixture(&bodyFixture);
	go = true;
	inittime = getMillSecond();
}
void SuScene::update(float dt)
{
	//q++; 
	DestoryWallWithTag(star->getTag() - 1000000);
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
	b2Vec2 v=mBallBody->GetLinearVelocity(); 
	//log("%lf", sqrt(v.x*v.x + v.y*v.y));
	v.x = v.x + 80   / 10000.0*v.x / sqrt(v.x*v.x + v.y*v.y);
	v.y = v.y + 80   / 10000.0*v.y / sqrt(v.x*v.x + v.y*v.y);
	log("%d %lf", q,sqrt(v.x*v.x + v.y*v.y)); 
	mBallBody->SetLinearVelocity(v);
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
	if (star->getTag() < 1000000)
	{
		win();
	}
	updat = 0;
}
void SuScene::CreateWall()
{
	if (NowWallNumber >= 3)
		return;
	NowWallNumber++;
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
	spr->setTag(101 + WallNumber);
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
	b2Body* Wall = mWorld->CreateBody(&WallDef); //�������д���һ�����壨���棩  

	b2PolygonShape WallShape;
	WallShape.SetAsBox(l / PTM_RATIO / 2, 5 / PTM_RATIO / 2); //���ó��Ⱥ͸߶ȣ����������ĵذ������X�ᣬ��һ����  
	b2FixtureDef WallFixture;
	WallFixture.shape = &WallShape;
	Wall->CreateFixture(&WallFixture);          //���Ƶ������״ 
	//double xx = Delta.x;
	//double yy = Delta.y;
	//double ll = sqrt(xx*xx + yy*yy);
	//if (abs(ll) < eps)
	//	return;
	//sii = yy / ll;
	//coi = xx / ll;
	//bodyDef.position.Set(star->getPositionX() / PTM_RATIO, star->getPositionY() / PTM_RATIO); //��ʼλ��  
	//mBallBody = mWorld->CreateBody(&bodyDef); // ��Box2D�����д���һ������  
	//b2Vec2 speed;
	//speed.x = 100.0f *(co);
	//speed.y = 100.0f*(si);
	//mBallBody->SetLinearVelocity(speed);
	//mBallBody->SetBullet(true);
	//mBallBody->SetFixedRotation(true);
	//12.0f
	//bodyShape.m_radius = 12.0f / PTM_RATIO;
	//С��Ķ�����  
	//bodyFixture.density = 1;  // �ܶ�  
	//bodyFixture.shape = &bodyShape; //��״  
	//bodyFixture.friction = 0.0f; //Ħ��������Ϊ���������û��������Ħ��������û��  
	//bodyFixture.restitution = 1.0f; //������100%����~~~  
	//mBallBody->CreateFixture(&bodyFixture);
}
void SuScene::win()
{
	unscheduleUpdate();
	w = 1;
	wintime = getMillSecond();
	Sprite* spr;
	Time = wintime - inittime;
	if (Time > 30000 )
	{
		spr = Sprite::create("hong.png");
	}
	else if (Time > 15000 )
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
	Time = wintime - inittime;
	label_time->setString(StringUtils::format("时间:%.2lf", Time));
	this->addChild(label_time);

	if (WallNumber > MinWall)
	{
		MinWall = WallNumber;
		UserDefault::getInstance()->setIntegerForKey("MaxWall", MinWall);
		UserDefault::getInstance()->flush();
	}
	if (Time > MinTime)
	{
		MinTime = Time;
		UserDefault::getInstance()->setDoubleForKey("MaxTime", MinTime);
		UserDefault::getInstance()->flush();
	}
	auto label_minwall = Label::createWithSystemFont("", "", 30);
	label_minwall->setPosition(winSize.width / 2, winSize.height / 2 - 40);
	label_minwall->setColor(Color3B::BLACK);
	label_minwall->setString(StringUtils::format("最多木棒:%d", MinWall));
	this->addChild(label_minwall);
	auto label_mintime = Label::createWithSystemFont("", "", 30);
	label_mintime->setPosition(winSize.width / 2, winSize.height / 2 - 80);
	label_mintime->setColor(Color3B::BLACK);
	label_mintime->setString(StringUtils::format("最长时间:%.2lf", MinTime));
	this->addChild(label_mintime);
	WinMenu();
}
void SuScene::WinMenu()
{
	auto item_0 = MenuItemImage::create("CS.png", "CSS.png", CC_CALLBACK_1(SuScene::ReStart, this));
	auto item_2 = MenuItemImage::create("FH.png", "FHH.png", CC_CALLBACK_1(SuScene::Return, this));

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
void SuScene::ReStart(Ref *sender)
{
	delete mWorld;
	this->removeAllChildrenWithCleanup(1);
	InitGameData();
}
void SuScene::Return(Ref *sender)
{
	auto scene = TransitionFadeTR::create(0.5, MenuScene::createScene());
	Director::getInstance()->replaceScene(scene);
}
void SuScene::First(Ref *sender)
{
	delete mWorld;
	this->removeAllChildrenWithCleanup(1);
	Su = 1;
	UserDefault::getInstance()->setIntegerForKey("Su", 1);
	UserDefault::getInstance()->flush();
	InitGameData();
}
double SuScene::getMillSecond()
{
	struct timeval tv;
	gettimeofday(&tv, nullptr);
	return (double)tv.tv_sec * 1000 + (double)tv.tv_usec / 1000;
}
void SuScene::DestoryWallWithTag(int tag)
{
	for (b2Body* body = mWorld->GetBodyList(); body != nullptr; body = body->GetNext())
	{
		Sprite* sprite = (Sprite*)body->GetUserData();
		if (sprite != NULL)
			if (sprite->getTag() == tag)
			{
			this->removeChildByTag(tag);
			mWorld->DestroyBody(body);
			NowWallNumber -= 1;
			break;
			}
	}
	this->removeChildByTag(tag);
}
void SuScene::Tech()
{
	auto spr = Sprite::create("bai.png");
	spr->setScale(5);
	spr->setPosition(winSize.width / 2, winSize.height / 2);
	this->addChild(spr);
	auto label_tech = Label::createWithSystemFont
		("生存模式：\n拖动屏幕移动并释放小球,之后拖动屏幕划出木棒以保护小球不碰撞四周墙壁,小球会不断加速，尽量坚持更长时间", "", 40, Size(500, 300));
	label_tech->setPosition(winSize.width / 2, winSize.height / 2 );
	label_tech->setColor(Color3B::BLACK);
	this->addChild(label_tech);
	auto item_0 = MenuItemImage::create("ZDL.png", "ZDLL.png", CC_CALLBACK_1(SuScene::First, this));
	Menu *menu = Menu::create(item_0, NULL);
	menu->alignItemsHorizontallyWithPadding(50);
	menu->setPosition(Point(Director::getInstance()->getWinSize().width / 2, Director::getInstance()->getWinSize().height * 1 / 4));
	menu->setVisible(true);
	this->addChild(menu);
}