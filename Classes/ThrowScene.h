#include "Box2D/Box2D.h"
#include "cocos2d.h"
#include "ContactListener.h"
USING_NS_CC;

class ThrowScene : public Layer
{
public:
	void Tech();
	int Th; 
	void First(Ref *sender);
	int Organ = 0; 
	void CreateNormalWall(Vec2 End, Vec2 Start); 
	void CreateOKWall(Vec2 End, Vec2 Start); 
	void CreateOrganWall(Vec2 End, Vec2 Start,int type); 
	void ChangeOrgan(int tag); 
	ContactListener* contactListener;
	void DestoryWallWithTag(int tag); 
	void die(); 
	Sprite* numberrr; 
	int Mode; 
	int wing = 0;
	int w = 0;
	double eps = 1e-11;
	int go = false;
	int WallNumber=0;
	int AllowWallNumber=0; 
	int ShallDestory=0; 
	int t = 0;
	int HaveChoose=0; 
	double inittime;
	double wintime;
	float timeStep = 1.0f / 60.0f;
	double coi, sii;
	double lastx, lasty;
	int speed = 26;
	int gra = 0;
	int iter=8;
	int wi = 0;
	int updat = 0;
	double Time = 0;
	int WinNum; 
	int MinWall;
	double MinTime; 
	int32 velocityIterations = 20;
	int32 positionIterations = 10;

	int wei(int input)
	{
		int count = 1;
		while (input % 10 > 10)
		{
			count++;
		}
		return count;
	}
	static Scene* createScene();
	virtual bool init();
	CREATE_FUNC(ThrowScene);
	ParticleSystem* mypat;
	// 触摸事件 回调函数   
	bool onTouchBegan(Touch* pTouch, Event* pEvent);
	void onTouchMoved(Touch* pTouch, Event* pEvent);
	void onTouchEnded(Touch* pTouch, Event* pEvent);
	static double getMillSecond();


	double PTM_RATIO = 30;
	Sprite* prespr; 
	cocos2d::Size winSize;
	b2Body* mBallBody;
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
	b2BodyDef bodyDef;
	b2BodyDef bodyDef2;
	b2BodyDef HbodyDef;
	b2BodyDef HbodyDef2;
	b2Vec2 gravity;
	// implement the "static create()" method manually
	cocos2d::EventListenerTouchOneByOne* listener;
	void update(float dt) override;
	b2World* mWorld;
	Sprite* numberr; 
	int32 iterations = 10;
	Vec2 Delta;
	int chapter; 
	Vec2 Start;
	Vec2 End;
	void Choose(); 
	void menuCallback(Ref *sender);
	void Achieve();
	void CreateWall();
	void win();
	void ReStart(Ref *sender);
	void Next(Ref *sender);
	void Return(Ref *sender);
	void InitGameData();
	void WinMenu();
	void DieMenu();
	void GameData(int chapter); 
	Sprite* spr1;
	Sprite* spr2;
	Sprite* spr3;
	Sprite* spr4;
	cocos2d::EventDispatcher* dispatcher;
private:
	Sprite* star;
	// 流星精灵    
	MotionStreak* streak;
	// 拖尾
}; //




