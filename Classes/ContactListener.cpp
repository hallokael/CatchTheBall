#include "ContactListener.h"  
#include "ThrowScene.h"
#include<math.h>
//extern b2World* mWorld; 
void ContactListener::BeginContact(b2Contact* contact)
{
	log("BeginContact");

	b2Body* bodyA = contact->GetFixtureA()->GetBody();
	b2Body* bodyB = contact->GetFixtureB()->GetBody();
	auto spriteA = (Sprite*)bodyA->GetUserData();
	auto spriteB = (Sprite*)bodyB->GetUserData();
	log("%d", spriteB->getTag());
	if (spriteB == NULL)
	{
		spriteA->setTag(1);
		return;
	}
	if (spriteA == NULL)
	{
		spriteB->setTag(1);
		return;
	}
	int ta = spriteA->getTag();
	int tb = spriteB->getTag();

	if (ta > 1000000 || tb > 1000000)
	{
		//if (ta < 1000000)
		//{
		//	if (ta > 10200)
		//	{
		//		if (ta > 10250)
		//			return;
		//	}
		//	if (ta > 10100)
		//	{
		//		if (ta > 10150)
		//			return;
		//	}
		//	if (ta > 10000)
		//		if (ta > 10050)
		//			return;
			spriteB->setTag(ta + 1000000);
		}
		if (tb < 1000000)
		{
			//if (tb > 10200)
			//{
			//	if (tb - 10200 > 50)
			//		return; 
			//}
			//else if (tb > 10100)
			//{
			//	if (tb > 10150)
			//		return; 
			//}
			//else if (tb > 10000)
			//	if (tb > 10050)
			//		return; 
			spriteA->setTag(tb + 1000000);
		}

	
	log("%d", spriteB->getTag());


}


void ContactListener::EndContact(b2Contact* contact)
{
	//b2Body* bodyA = contact->GetFixtureA()->GetBody();
	//b2Body* bodyB = contact->GetFixtureB()->GetBody();
	//auto spriteA = (Sprite*)bodyA->GetUserData();
	//auto spriteB = (Sprite*)bodyB->GetUserData();
	//if (spriteA == NULL || spriteB == NULL)
	//	return;
	//int ta = spriteA->getTag();
	//int tb = spriteB->getTag();


}


void ContactListener::PreSolve(b2Contact* contact, const b2Manifold* oldManifold)
{
	//log("PreSolve");
}


void ContactListener::PostSolve(b2Contact* contact, const b2ContactImpulse* impulse)
{
	//log("PostSolve");
}