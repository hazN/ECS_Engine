#include "iRigidBodyDesc.h"

iRigidBodyDesc::iRigidBodyDesc()
{
	mass = 1.f;
	bStatic = false;
	restitution = 1.f;
	friction = 0.2f;
	position = Vec3(0.f, 0.f, 0.f);
	velocity = Vec3(0.f, 0.f, 0.f);
	linearFactor = Vec3(1.f, 1.f, 1.f);
	angularFactor = Vec3(1.f, 1.f, 1.f);
	rotation = Quat(1.f, 0.f, 0.f, 0.f);
	angularVelocity = Vec3(0.f, 0.f, 0.f);
	linearDamping = 0.01f;
	angularDamping = 0.01f;
}

iRigidBodyDesc::~iRigidBodyDesc()
{
}
