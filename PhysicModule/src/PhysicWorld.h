#pragma once
#include <iPhysicWorld.h>
#include <vector>
#include "RigidBody.h"
#include "CollisionHandler.h"

class PhysicWorld : public iPhysicWorld
{
public:
	PhysicWorld();
	virtual ~PhysicWorld();

	virtual void setGravity(const Vec3& gravity) override;
	virtual void addBody(iCollision* body) override;
	virtual void removeBody(iCollision* body) override;

	virtual void timeStep(float dt) override;
	virtual void addToCollisionListener(iCollisionListener* listener) override;

private:
	Vec3 m_gravity;

	std::vector<iCollision*> m_body;
	std::vector<RigidBody*> m_rigidBody;

	CollisionHandler* m_collisionHandler;
	iCollisionListener* m_collisionListener;

	void addRigid(iCollision* body);
	void removeRigid(iCollision* body);

	PhysicWorld(const PhysicWorld&) {}
	PhysicWorld& operator=(const PhysicWorld&) 
	{
		return *this;
	}
};

