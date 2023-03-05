#include "PhysicFactory.h"

PhysicFactory::PhysicFactory()
	: iPhysicFactory()
{
}

PhysicFactory::~PhysicFactory()
{
}

iPhysicWorld* PhysicFactory::createWorld()
{
	return new PhysicWorld();
}

iRigidBody* PhysicFactory::createRigidBody(const iRigidBodyDesc& desc, iShape* shape)
{
	return new RigidBody(desc, shape);
}
