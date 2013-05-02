
#ifndef __PHYSICS_WORLD__
#define __PHYSICS_WORLD__

#include "Box2D/Box2D.h"
#include "cocos2d.h"

using namespace cocos2d;

class Physics
{
public:
	Physics():
		meterPerPixel(0.1),
		gravity(0,-9.8) ,
		sleep(true),
		updateTime(1.0 / 30),
		stepTime(1.0 / 30),
		velocityIterations(10),
		positionIterations(10),
		mouseJoint(NULL)
	{}

	// Public Interface
	static Physics* create();
	void updateWorld();
	void drawDebugData();

	void touchBegin(CCTouch *pTouch, CCEvent *pEvent);
	void touchMoved(CCTouch *pTouch, CCEvent *pEvent);
	void touchEnded (CCTouch *pTouch, CCEvent *pEvent);

	// Utilities
	b2Body* createCircle(int x, int y, float radius, char* name);
	b2Body* createStaticBrick(int x, int y, int width, int height,char* name, float angle = 0);
	b2Body* createBrick(int x, int y, int width, int height,char* name, float angle = 0, int group = 0);
	b2Body* createIdol(int x, int y,char* name);

	void		createRope(b2Body* bodyA, b2Body* bodyB,int length);
	void		createMouseJoint(b2MouseJointDef* jointDef){ mouseJoint = (b2MouseJoint*)world->CreateJoint(jointDef);}
private:
	float		getRectangleInRadian(b2Body* bodyA, b2Body* bodyB);

public:
	//virtual void createMap();
	float			getMeterPerPixel(){ return meterPerPixel;}
	float			getUpdateTime(){ return updateTime;}
	b2World*	getWorld(){ return world;}
	b2Body*	getBackgroundBody() { return backgroundBody;}

private:
	float meterPerPixel;
	b2World* world;
	b2Body* backgroundBody;
	b2Vec2 gravity;
	bool sleep;

	// Joint
	b2MouseJoint* mouseJoint;

	float updateTime;
	float stepTime;
	int velocityIterations;
	int positionIterations;

private:
	bool init();
};

#endif // !__PHYSICS_WORLD__
