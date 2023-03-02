#pragma once
#include <vector>
#include "RigidBody.h"
#include "CollidingBody.h"
#include <iPlaneShape.h>
#include <iSphereShape.h>

#define ELASTIC_COEF 0.4f
#define INELASTIC_COEF (1.f - ELASTIC_COEF)

class CollisionHandler
{
public:
	CollisionHandler();
	~CollisionHandler();

	glm::vec3 ClosestPointPlain(const glm::vec3& point, const glm::vec3& planNormal, float dotProd);

	bool SphereVsSphere(float dt, RigidBody* body1, iSphereShape* sphere1, RigidBody* body2, iSphereShape* sphere2);
	bool SphereVsPlane(float dt, RigidBody* sphere, iSphereShape* sphereShape, RigidBody* plane, iPlaneShape* planeShape);
	void collide(float dt, std::vector<iCollision*>& body, std::vector<CollidingBody>& collision);

	bool RigidVsRigid(float dt, RigidBody* rigid1, RigidBody* rigid2);

private:
	bool testMovingSphereVsSphere(
		const Vec3& s0_center, const float s0_rad,
		const Vec3& s1_center, const float s1_rad,
		const Vec3& v0, const Vec3& v1, float& t);

	bool testMovingSphereVsPlane(const Vec3& prevPos, const Vec3& currentPos, float rad, const Vec3& normal, float dotprod);
};

