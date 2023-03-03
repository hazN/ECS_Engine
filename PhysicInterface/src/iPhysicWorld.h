#pragma once
#include "iShape.h"
#include "iCollisionListener.h"

class iPhysicWorld
{
public:
	virtual ~iPhysicWorld() {}

	virtual void setGravity(const Vec3& gravity) = 0;

	virtual void addBody(iCollision* body) = 0;
	virtual void removeBody(iCollision* body) = 0;

	virtual void timeStep(float dt) = 0;

	virtual void addToCollisionListener(iCollisionListener* listener) = 0;


private:
	iPhysicWorld(const iPhysicWorld&) {}
	iPhysicWorld& operator=(const iPhysicWorld&)
	{
		return *this;
	}

protected:
	iPhysicWorld() {}
};

