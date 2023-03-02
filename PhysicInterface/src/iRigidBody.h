#pragma once
#include "iCollision.h"
#include "iShape.h"

class iRigidBody : public iCollision
{
public:
	virtual ~iRigidBody() {}

	virtual Vec3 getPosition() = 0;
	virtual void setPosition(const Vec3& pos) = 0;

	virtual Quat getRotation() = 0;
	virtual void setRotation(const Quat& rotate) = 0;

	virtual void addForce(const Vec3& force) = 0;
	virtual void addForceAP(const Vec3& force, const Vec3& at) = 0;

	virtual void addImpulse(const Vec3& impulse) = 0;
	virtual void addImpulseAP(const Vec3& impulse, const Vec3& at) = 0;

	virtual void addTorque(const Vec3& torque) = 0;
	virtual void addTorqueImpulse(const Vec3& torqueImpulse) = 0;

protected:
	iRigidBody() : iCollision(BodyType::RigidBody)
	{
	}

private:
	iRigidBody(const iRigidBody&) :iCollision(BodyType::RigidBody)
	{
	}

	iRigidBody& operator=(const iRigidBody&)
	{
		return *this;
	}

};

