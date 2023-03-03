#pragma once
#include <glm/glm.hpp>
#include <glm/gtx/quaternion.hpp>
#include <iCollision.h>

namespace sas
{
	// Holds Position, rotation and scale of an entity
	class Transform : public Component
	{
	public:
		bool Enabled;
		glm::vec3 Position;
		glm::quat Rotation;
		glm::vec3 Scale = glm::vec3(1.f);
		iCollision* p_physicBody;
	};
}