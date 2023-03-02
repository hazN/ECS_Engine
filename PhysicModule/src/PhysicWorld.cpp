#include "PhysicWorld.h"

PhysicWorld::PhysicWorld()
	:iPhysicWorld()
	,m_collisionHandler(nullptr)
{
	m_collisionHandler = new CollisionHandler();
}

PhysicWorld::~PhysicWorld()
{
	m_rigidBody.clear();
	m_body.clear();

	delete m_collisionHandler;
	delete m_collisionListener;
}

void PhysicWorld::setGravity(const Vec3& gravity)
{
	m_gravity = gravity;
}

void PhysicWorld::addBody(iCollision* body)
{
	if (body == nullptr)
	{
		return;
	}
	
	//find existing body if not found then push new body
	if (std::find(m_body.begin(), m_body.end(), body) == m_body.end())
	{
		m_body.push_back(body);
	}
	switch (body->getBodyType())
	{
	case BodyType::RigidBody:
		addRigid(body);
		break;
	default:
		break;
	}
}

void PhysicWorld::removeBody(iCollision* body)
{
	if (body == nullptr)
	{
		return;
	}

	switch (body->getBodyType())
	{
	case BodyType::RigidBody:
		removeRigid(body);
		break;
	default:
		break;
	}

	m_body.erase(std::find(m_body.begin(), m_body.end(), body));
	
}

void PhysicWorld::timeStep(float dt)
{
	int count = int(m_body.size());
	int count_rigid = int(m_rigidBody.size());

	for (int i = 0; i < count_rigid; i++)
	{
		m_rigidBody[i]->update(dt);
	}

	//verlet
	//step 0
	for (int i = 0; i < count_rigid; i++)
	{
		if (!m_rigidBody[i]->isStatic())
		{
			m_rigidBody[i]->setGravity(m_gravity);
			m_rigidBody[i]->updateAcc();
		}
	}

	//step 3 update velocity
	for (int i = 0; i < count_rigid; i++)
	{
		if (!m_rigidBody[i]->isStatic())
		{
			m_rigidBody[i]->verletStep3(dt);
			m_rigidBody[i]->addDamping(dt * 0.5f);
		}
	}

	//step 1 - position update
	for (int i = 0; i < count_rigid; i++)
	{
		if (!m_rigidBody[i]->isStatic())
		{
			m_rigidBody[i]->verletStep1(dt);
		}
	}

	// collision handler
	std::vector<CollidingBody> collision;
	m_collisionHandler->collide(dt, m_body, collision);

	for (int i = 0; i < collision.size(); i++)
	{
		CollidingBody& collisionBody = collision[i];
		//play sound here
		//m_collisionListener->notifyCollision(collisionBody.bodyA, collisionBody.bodyB);
	}

	//step 2 - update velocity
	for (int i = 0; i < count_rigid; i++)
	{
		if (!m_rigidBody[i]->isStatic())
		{
			m_rigidBody[i]->verletStep2(dt);
			m_rigidBody[i]->addDamping(dt * 0.5f);
			m_rigidBody[i]->killForce();
		}
	}
}

void PhysicWorld::addToCollisionListener(iCollisionListener* listener)
{
	m_collisionListener = listener;
}

void PhysicWorld::addRigid(iCollision* body)
{
	RigidBody* rigid = RigidBody::cast(body);

	if (std::find(m_rigidBody.begin(), m_rigidBody.end(), rigid) == m_rigidBody.end())
	{
		m_rigidBody.push_back(rigid);
	}
}

void PhysicWorld::removeRigid(iCollision* body)
{
	RigidBody* rigid = RigidBody::cast(body);
	m_rigidBody.erase(std::find(m_rigidBody.begin(), m_rigidBody.end(), rigid));

}
