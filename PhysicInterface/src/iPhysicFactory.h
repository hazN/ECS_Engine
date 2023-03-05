#pragma once
#include "iPhysicWorld.h"
#include "iRigidBody.h"
#include "iRigidBodyDesc.h"

class iPhysicFactory
{
public:
	virtual ~iPhysicFactory() {}

	virtual iPhysicWorld* createWorld() = 0;
	virtual iRigidBody* createRigidBody(const iRigidBodyDesc& desc, iShape* shape) = 0;

private:
	iPhysicFactory(const iPhysicFactory&) {}
	iPhysicFactory& operator=(const iPhysicFactory&)
	{
		return *this;
	}

protected:
	iPhysicFactory() {}
};

