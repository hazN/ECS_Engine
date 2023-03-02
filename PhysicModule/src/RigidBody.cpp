#include "RigidBody.h"


RigidBody::RigidBody(const iRigidBodyDesc& desc, iShape* shape)
	:iRigidBody()
{
	m_friction = desc.friction;
	m_restitution = desc.restitution;
	m_linearDamping = desc.linearDamping;
	m_angularDamping = desc.angularDamping;
	m_bStatic = desc.bStatic;
	m_position = desc.position;
	//m_prevPosition
	m_velocity = desc.velocity;
	//m_acceleration

	//m_force
	//m_torque
	//m_gravity

	m_rotation = desc.rotation;
	m_angularVelocity = desc.angularVelocity;
	//m_angularAcceleration

	m_shape = shape;

	//m_renderPosition
	if (m_bStatic || desc.mass <= 0.f)
	{
		m_mass = 0.f;
		m_inverseMass = 0.f;
		m_bStatic = true;
	}
	else 
	{
		m_mass = desc.mass;
		m_inverseMass = 1 / m_mass;
	}
}

RigidBody::~RigidBody()
{
}

RigidBody* RigidBody::cast(iCollision* body)
{
	return dynamic_cast<RigidBody*>(body);
}

iShape* RigidBody::getShape()
{
	return m_shape;
}

bool RigidBody::isStatic()
{
	return m_bStatic;
}

Vec3 RigidBody::getPosition()
{
	return m_position;
}

void RigidBody::setPosition(const Vec3& pos)
{
	m_position = pos;
}

Quat RigidBody::getRotation()
{
	return m_rotation;
}

void RigidBody::setRotation(const Quat& rotate)
{
	m_rotation = rotate;
}

void RigidBody::addForce(const Vec3& force)
{
	m_force += force;
}

void RigidBody::addForceAP(const Vec3& force, const Vec3& at)
{
	addForce(force);
	addTorque(glm::cross(at, force));
}

void RigidBody::addImpulse(const Vec3& impulse)
{
	m_velocity += impulse * m_inverseMass;
}

void RigidBody::addImpulseAP(const Vec3& impulse, const Vec3& at)
{
	addTorqueImpulse(glm::cross(at, impulse));
}

void RigidBody::addTorque(const Vec3& torque)
{
	m_torque += torque;
}

void RigidBody::addTorqueImpulse(const Vec3& torqueImpulse)
{
	m_angularVelocity += torqueImpulse;
}

void RigidBody::setGravity(const Vec3& gravity)
{
	m_gravity = gravity;
}

void RigidBody::updateAcc()
{
	if (m_bStatic)
	{
		return;
	}
	m_acceleration = (m_force * m_inverseMass) + m_gravity;
	m_angularAcceleration = m_torque;
}

void RigidBody::verletStep1(float dt)
{
	if (m_bStatic)
	{
		return;
	}

	m_prevPosition = m_position;
	// s = ut + 1/2(at^2)
	m_position += (m_velocity + (0.5f * m_acceleration * dt)) * dt; 
	
	if (m_position.y < 0.f)
	{
		m_position.y = 1.f;
	}

	// theta = omega*t + 1/2(alpha*t^2) angular rotation
	Vec3 theta = (m_angularVelocity + (0.5f * m_angularAcceleration * dt)) * dt;

	float angle = glm::length(theta);
	Vec3 theta_normal = glm::normalize(theta);
	
	if (angle != 0.f)
	{
		Quat rotate = glm::angleAxis(angle, theta_normal);
		m_rotation *= rotate;
	}
}

void RigidBody::verletStep2(float dt)
{
	if (m_bStatic)
	{
		return;
	}

	m_velocity += m_acceleration * (dt / 2);
	m_angularVelocity += m_angularAcceleration * (dt / 2);
}

void RigidBody::verletStep3(float dt)
{
	verletStep2(dt);
}

void RigidBody::killForce()
{
	m_force = Vec3(0.f);
	m_torque = Vec3(0.f);
}

void RigidBody::addDamping(float dt)
{
	m_velocity *= pow((1.f - m_linearDamping), dt);
	m_angularVelocity *= pow((1.f - m_angularDamping), dt);

	//todo
}

void RigidBody::setRenderPosition(Vec3* pos)
{
	m_renderPosition = pos;
}

void RigidBody::update(float step)
{
	if (m_renderPosition != nullptr)
	{
		m_renderPosition->x += step;
	}
}


