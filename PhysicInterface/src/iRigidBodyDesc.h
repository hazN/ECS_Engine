#pragma once
#include "iShape.h"

class iRigidBodyDesc
{
public:
	iRigidBodyDesc();
	~iRigidBodyDesc();

	float mass;
	bool bStatic;
	float restitution;
	float friction;

	Vec3 position;
	Vec3 velocity;

	Vec3 linearFactor;
	Vec3 angularFactor;

	Quat rotation;
	Vec3 angularVelocity;

	float linearDamping;
	float angularDamping;

private:

};

