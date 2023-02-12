#pragma once
#include <glm/glm.hpp>
#include <glm/gtx/quaternion.hpp>

namespace sas
{
	class Transform
	{
	public:
		bool Enabled;
		glm::vec3 Position;
		glm::quat Rotation;
		glm::vec3 Scale;
	};
}