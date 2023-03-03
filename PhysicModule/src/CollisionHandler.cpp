#include "CollisionHandler.h"
#include <glm/gtx/projection.hpp>

CollisionHandler::CollisionHandler()
{
}

CollisionHandler::~CollisionHandler()
{
}

glm::vec3 CollisionHandler::ClosestPointPlain(const glm::vec3& point, const glm::vec3& planNormal, float dotProd)
{
	float cal = glm::dot(planNormal, point) - dotProd;
	glm::vec3 result = point - cal * planNormal;
	return result;
}

bool CollisionHandler::SphereVsSphere(float dt, RigidBody* body1, iSphereShape* sphere1, RigidBody* body2, iSphereShape* sphere2)
{
	if (body1->isStatic() && body2->isStatic())
	{
		return false;
	}

	Vec3 v0 = body1->m_position - body1->m_prevPosition;
	Vec3 v1 = body2->m_position - body2->m_prevPosition;
	float t = 0.f;

	float sphere1_rad = sphere1->getRad();
	float sphere2_rad = sphere2->getRad();
	bool bResult = testMovingSphereVsSphere(body1->m_prevPosition, sphere1_rad, body2->m_prevPosition, sphere2_rad, v0, v1, t);

	if (!bResult)
	{
		//no collision now
		return false;
	}

	if (t > dt)
	{
		//no collision in this step of time
		return false;
	}

	float fractionTime = t / (glm::length(v0) + glm::length(v1));
	float revTime = (1.f - fractionTime) * dt;
	body1->verletStep1(-revTime);
	body2->verletStep1(-revTime);


	//momentum p = mv
	Vec3 p1 = body1->m_mass * body1->m_velocity;
	Vec3 p2 = body2->m_mass * body2->m_velocity;
	Vec3 sumP = p1 + p2;
	float sumMass = body1->m_mass + body2->m_mass;
	float factorA = body1->m_mass / sumMass;
	float factorB = body2->m_mass / sumMass;
	p1 = sumP * factorA;
	p2 = sumP * factorB;

	//check overlap
	Vec3 vec = body2->m_position - body1->m_position;
	float length = glm::length(vec);
	float overlap = length - (sphere1_rad + sphere2_rad);

	if (overlap < std::numeric_limits<float>::epsilon())
	{
		Vec3 overlapVec = glm::normalize(vec);
		overlapVec *= -overlap;

		if (!body1->m_bStatic)
		{
			body1->m_position -= overlapVec * factorA;
		}
		if (!body2->m_bStatic)
		{
			body2->m_position -= overlapVec * factorB;
		}
		//recalculate
		vec = body2->m_position - body1->m_position;
		length = glm::length(vec);
	}

	vec /= length;

	// Elastic& inelastic momentum
	Vec3 p1_elastic = vec * (glm::length(p1) * ELASTIC_COEF);
	Vec3 p1_inelastic = vec * (glm::length(p1) * INELASTIC_COEF);
	Vec3 p2_elastic = vec * (glm::length(p2) * ELASTIC_COEF);
	Vec3 p2_inelastic = vec * (glm::length(p2) * INELASTIC_COEF);

	body1->m_velocity -= (p1_elastic + p1_inelastic) * body1->m_inverseMass * body1->m_restitution;
	body2->m_velocity -= (p2_elastic + p2_inelastic) * body2->m_inverseMass * body2->m_restitution;

	body1->verletStep1(revTime);
	body2->verletStep1(revTime);

	return true;
}

bool CollisionHandler::SphereVsPlane(float dt, RigidBody* sphere, iSphereShape* sphereShape, RigidBody* plane, iPlaneShape* planeShape)
{
	bool bResult = testMovingSphereVsPlane((sphere->m_prevPosition - plane->m_position), (sphere->m_position - plane->m_position), sphereShape->getRad(), planeShape->getNormal(), planeShape->getDotProd());
	if (!bResult)
	{
		return false;
	}

	Vec3 closestPoint = ClosestPointPlain(sphere->m_position, planeShape->getNormal(), planeShape->getDotProd());
	Vec3 overlap = closestPoint - sphere->m_position;
	float length = glm::length(overlap);
	float velocity_scarlar = glm::length(sphere->m_velocity);
	float angularVelocity_scarlar = glm::length(sphere->m_angularVelocity);

	if (velocity_scarlar > 0.f || angularVelocity_scarlar > 0.f)
	{
		float DT_fract = 0.f;
		float sphereRad = sphereShape->getRad();
		
		if (velocity_scarlar != 0.f) 
		{
			DT_fract = sphereRad * ((sphereRad / length) - 1.f) / velocity_scarlar;
		}

		float DT_partial = (1.f - DT_fract) * dt;

		//Reverse sphere off the plane
		sphere->verletStep1(-DT_partial);
		
		//bounce cal
		Vec3 prevVelocity = sphere->m_velocity;
		//reflection
		sphere->m_velocity = glm::reflect(sphere->m_velocity, planeShape->getNormal());

		//impact
		Vec3 impactComponent = glm::proj(sphere->m_velocity, planeShape->getNormal());
		Vec3 impactTangent = sphere->m_velocity - impactComponent;
		Vec3 relativePT = glm::normalize(closestPoint - sphere->m_position) * sphereRad;
		float v_surface = sphereRad * glm::length(sphere->m_angularVelocity);
		Vec3 rotateDir = glm::normalize(glm::cross(relativePT - sphere->m_position, sphere->m_angularVelocity));

		if (glm::dot(impactTangent, planeShape->getNormal()) > 0.f)
		{
			sphere->addImpulseAP((impactComponent * sphere->m_mass * -2.f), relativePT);
		}
		else
		{
			Vec3 F_impact = -impactTangent * sphere->m_mass * plane->m_friction;
			sphere->addForceAP(F_impact, relativePT);
		}

		if (glm::dot(sphere->m_velocity, planeShape->getNormal()) == 0.f)
		{
			Vec3 force = v_surface * rotateDir * sphere->m_mass * plane->m_friction;
			sphere->addForce(force);
		}

		sphere->updateAcc();

		sphere->verletStep1(DT_partial);

		closestPoint = ClosestPointPlain(sphere->m_position, planeShape->getNormal(), planeShape->getDotProd());
		overlap = closestPoint - sphere->m_position;
		length = glm::length(overlap);
		if (length < sphereShape->getRad())
		{
			//still collide
			sphere->m_position += planeShape->getNormal() * (sphereShape->getRad() - length);
			float VDotNorm = glm::dot(sphere->m_velocity, planeShape->getNormal());
			if (VDotNorm < 0.f)
			{
				sphere->m_velocity -= planeShape->getNormal() * VDotNorm;
			}
			if (sphere->m_position.y < 0.f)
			{
				sphere->m_position.y = 1.f;
			}
		}
		else
		{
			sphere->m_velocity *= sphere->m_restitution;
		}
	}
	else
	{
		return false;
	}

	return true;

}

void CollisionHandler::collide(float dt, std::vector<iCollision*>& body, std::vector<CollidingBody>& collision)
{
	int count = body.size();
	bool bCollision = false;
	for (size_t i = 0; i < count-1; i++)
	{
		iCollision* bodyA = body[i];
		for (size_t j = 0; j < count; j++)
		{
			if (i == j)
				continue;
			iCollision* bodyB = body[j];
			bCollision = false;

			if (bodyA->getBodyType() == BodyType::RigidBody)
			{
				if (bodyB->getBodyType() == BodyType::RigidBody)
				{
					bCollision = RigidVsRigid(dt, RigidBody::cast(bodyA), RigidBody::cast(bodyB));
				}
			}

			if (bCollision)
			{
				collision.push_back(CollidingBody(bodyA, bodyB));
			}
		}
	}

}

bool CollisionHandler::RigidVsRigid(float dt, RigidBody* rigid1, RigidBody* rigid2)
{
	iShape* shapeA = rigid1->getShape();
	iShape* shapeB = rigid2->getShape();

	bool bCollision = false;

	if (shapeA->getShapeType() == shapeType::Sphere)
	{
		if (shapeB->getShapeType() == shapeType::Sphere)
		{
			bCollision = SphereVsSphere(dt, rigid1, iSphereShape::cast(shapeA), rigid2, iSphereShape::cast(shapeB));
		}
		else if(shapeB->getShapeType() == shapeType::Plane)
		{
			bCollision = SphereVsPlane(dt, rigid1, iSphereShape::cast(shapeA), rigid2, iPlaneShape::cast(shapeB));
		}
	}
	else if(shapeA->getShapeType() == shapeType::Plane)
	{
		if (shapeB->getShapeType() == shapeType::Sphere)
		{
			bCollision = SphereVsPlane(dt, rigid2, iSphereShape::cast(shapeB), rigid1, iPlaneShape::cast(shapeA));
		}
	}

	return bCollision;
}

bool CollisionHandler::testMovingSphereVsSphere(const Vec3& s0_center, const float s0_rad, const Vec3& s1_center, const float s1_rad, const Vec3& v0, const Vec3& v1, float& t)
{
	Vec3 s = s1_center - s0_center;
	Vec3 v = v1 - v0;
	float r = s1_rad + s0_rad;
	float c = glm::dot(s, s) - r * r;

	if (c < 0.f)
	{
		t = 0.f;
		return true;
	}

	float a = glm::dot(v, v);
	if (a < std::numeric_limits<float>::epsilon())
	{
		return false;
	}

	float b = glm::dot(v, s);
	if (b >= 0.f)
	{
		return false;
	}

	float d = (b * b) - (a * c);
	if (d < 0.f)
	{
		return false;
	}

	t = (-b - sqrt(d)) / a;

	return true;
}

bool CollisionHandler::testMovingSphereVsPlane(const Vec3& prevPos, const Vec3& currentPos, float rad, const Vec3& normal, float dotprod)
{
	float distanceA = glm::dot(prevPos, normal) - dotprod;
	float distanceB = glm::dot(currentPos, normal) - dotprod;

	if (distanceA * distanceB < 0.f)
	{
		return true;
	}

	if ((abs(distanceA) < rad) || (abs(distanceB) <= rad))
	{
		return true;
	}

	return false;
}
