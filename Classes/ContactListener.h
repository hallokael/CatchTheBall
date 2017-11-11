#include "cocos2d.h"  
#include "Box2D/Box2D.h"  
USING_NS_CC;
#pragma once

class ContactListener : public b2ContactListener
{
private:
	//两个物体开始接触时会响应  
	virtual void BeginContact(b2Contact* contact);


	double PTM_RATIO = 30;
	//持续接触时响应  
	virtual void PreSolve(b2Contact* contact, const b2Manifold* oldManifold);
	//持续接触时响应，调用完preSolve后调用  
	virtual void PostSolve(b2Contact* contact, const b2ContactImpulse* impulse);

	//分离时响应  
	virtual void EndContact(b2Contact* contact);
};