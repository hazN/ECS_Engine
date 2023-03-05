#pragma once
#include <iPhysicFactory.h>
#include "PhysicWorld.h"

class PhysicFactory :    public iPhysicFactory
{
public:
	PhysicFactory();
	virtual ~PhysicFactory();

	virtual iPhysicWorld* createWorld() override;
	virtual iRigidBody* createRigidBody(const iRigidBodyDesc& desc, iShape* shape) override;

};

