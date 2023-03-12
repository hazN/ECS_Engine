#pragma once
#include "MeshRenderer.h"
#include "Agent.h"
#include <glm/gtc/quaternion.hpp>
#include <glm/gtx/quaternion.hpp>
#include <glm/gtx/euler_angles.hpp>
#include <glm/gtx/norm.hpp>
#include <glm/glm.hpp>
#include <glm/vec3.hpp> 
#include <glm/vec4.hpp> 
#include <glm/mat4x4.hpp> 
namespace sas
{
	class AgentController
	{
	public:
		AgentController() = default;
		~AgentController() = default;

		std::vector<Agent> agents_;
		Entity* Player;
		AgentController(Entity* player);
		void Update(float dt);
	};
}