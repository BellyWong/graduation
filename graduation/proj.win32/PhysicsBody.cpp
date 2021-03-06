
#include "PhysicsBody.h"

	PhysicsBody::PhysicsBody(b2World* world)
	{
		this->world = world;

		bodyDef	= NULL;
		body			= NULL;

		bodyUserData = NULL;

		fixtureDef = NULL;

		chainShape		= NULL;
		circleShape		= NULL;
		edgeShape		= NULL;
		polygonShape	= NULL;
		_setFixtureSensorFlag = false;
	}

	bool PhysicsBody::isBodyExistence(char* functionName)
	{
		if(NULL != body)
		{
			cout<<"Error! In Class PHysicsBody, In Function "<<functionName<<" !"<<endl;
			cout<<"Body Already Created ! "<<endl;
			cout<<"Use This Method Before Any Fixture Or Shape Function May Help !"<<endl;
			return true;
		}

		return false;
	}

	void PhysicsBody::resetAllShape()
	{
		//chainShape	= NULL;
		//circleShape	= NULL;
		//edgeShape		= NULL;
		//polygonShape	= NULL;
		if(NULL != chainShape)
		{
			delete chainShape;
			chainShape = NULL;
		}else if(NULL != circleShape)
		{
			delete circleShape;
			circleShape = NULL;
		}else if(NULL != edgeShape)
		{
			delete edgeShape;
			edgeShape = NULL;
		}else if(NULL != polygonShape)
		{
			delete polygonShape;
			polygonShape = NULL;
		}
	}

	void PhysicsBody::resetBodyUserData()
	{

		if(NULL != bodyUserData)
		{

			delete bodyUserData;
			bodyUserData = NULL;
		}
	}

	void PhysicsBody::resetFixture()
	{
		if(NULL != fixtureDef)
		{
			delete fixtureDef;
			fixtureDef = NULL;
		}

		_setFixtureSensorFlag = false;
	}

	void PhysicsBody::resetBody()
	{
		// Clear BodyDefinition
		if(NULL != bodyDef)
		{
			delete bodyDef;
			bodyDef = NULL;
		}

		// Clear Body
		body = NULL;
	}

	PhysicsBody* PhysicsBody::newBody()
	{
		resetBody();
		resetFixture();
		resetAllShape();
		resetBodyUserData();

		return this;
	}


	// 操作 Body
	PhysicsBody* PhysicsBody::setBodyPosition(b2Vec2 position)
	{
		if(NULL != body)
			newBody();

		if(NULL == bodyDef)
			bodyDef = new b2BodyDef();

		bodyDef->position = position;
		return this;
	}
	PhysicsBody* PhysicsBody::setBodyType(b2BodyType type)
	{
		if(NULL != body)
			newBody();

		if(NULL == bodyDef)
			bodyDef = new b2BodyDef();

		bodyDef->type = type;
		return this;
	}

	// 操作 Shape
	// polygonShape
	PhysicsBody* PhysicsBody::setPolygonShapeASBox(float hx, float hy)
	{
		resetAllShape();

		if(NULL == polygonShape)
			polygonShape = new b2PolygonShape();

		polygonShape->SetAsBox(hx, hy);
		return this;
	}
	// circleShape
	PhysicsBody* PhysicsBody::setCircleShape(float radius)
	{
		resetAllShape();

		if(NULL == circleShape)
			circleShape = new b2CircleShape();

		circleShape->m_radius = radius;

		return this;
	}

	// 操作 Fixture
	PhysicsBody* PhysicsBody::setFixtureSensor(bool sensor)
	{
		_setFixtureSensorFlag = true;
		return this;
	}
	PhysicsBody* PhysicsBody::setFixtureDensity(float density)
	{
		if(NULL == fixtureDef)
			fixtureDef = new b2FixtureDef;

		fixtureDef->density = density;

		return this;
	}
	PhysicsBody* PhysicsBody::setFixtureRestitution(float restitution)
	{
		if(NULL == fixtureDef)
			fixtureDef = new b2FixtureDef;

		fixtureDef->restitution = restitution;

		return this;
	}
	PhysicsBody* PhysicsBody::setFixtureFriction(float friction)
	{
		if(NULL == fixtureDef)
			fixtureDef = new b2FixtureDef;

		fixtureDef->friction = friction;

		return this;
	}

	PhysicsBody* PhysicsBody::setFixtureGroupIndex(int groupIndex)
	{
		if(NULL == fixtureDef)
			fixtureDef = new b2FixtureDef();

		fixtureDef->filter.groupIndex = groupIndex;

		return this;
	}
	PhysicsBody* PhysicsBody::setFixtureCategoryBits(int categoryBits)
	{
		if(NULL == fixtureDef)
			fixtureDef = new b2FixtureDef();

		fixtureDef->filter.categoryBits = categoryBits;

		return this;
	}
	PhysicsBody* PhysicsBody::setFixtureMaskBits(int maskBits)
	{
		if(NULL == fixtureDef)
			fixtureDef = new b2FixtureDef();

		fixtureDef->filter.maskBits = maskBits;

		return this;
	}

	PhysicsBody* PhysicsBody::createFixture()
	{
		// 创建 Fixture 的时候，
		// 保证 body 的存在
		//			bodyDefinition 存在
		if(NULL == body)
		{
			if(NULL == bodyDef)
			{
				bodyDef = new b2BodyDef();
			}

			body = world->CreateBody(bodyDef);
		}

		// 保证 FixtureDef 的存在
		if(NULL == fixtureDef)
		{
			fixtureDef = new b2FixtureDef();
		}

		//chainShape		= NULL;
		//circleShape		= NULL;
		//edgeShape		= NULL;
		//polygonShape	= NULL;
		if(NULL != chainShape)
		{
			fixtureDef->shape = chainShape;
		}else if(NULL != circleShape)
		{
			fixtureDef->shape = circleShape;
		}else if(NULL != edgeShape)
		{
			fixtureDef->shape = edgeShape;
		}else if(NULL != polygonShape)
		{
			fixtureDef->shape = polygonShape;
		}else
		{
			// 默认
			fixtureDef->shape = new b2PolygonShape();
		}

		b2Fixture* fixture = body->CreateFixture(fixtureDef);

		if(_setFixtureSensorFlag)
		{
			fixture->SetSensor(true);
		}

		// 创建完 Fixture 后，
		// 清空 已经创建过的 Shape
		resetFixture();
		resetAllShape();

		return this;
	}

	b2Body* PhysicsBody::createBody()
	{
		if(NULL == bodyUserData)
			bodyUserData = new BodyUserData("null");

		body->SetUserData(bodyUserData);

		return body;
	}

