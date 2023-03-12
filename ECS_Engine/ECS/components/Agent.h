#pragma once
#pragma once
#include <vector>
#include "MeshRenderer.h"
#include "../Transform.h"
#include "../Entity.h"
namespace sas
{
	enum AItype { ZOMBIE, RANGED};

	class Agent
	{
	public:
		Agent() = default;
		~Agent() = default;
		Agent(Entity* agent, AItype type);
		Agent(Entity* agent, AItype type, float speed);
		Agent(Entity* agent, AItype type, float max, float min);
		Agent(Entity* agent, AItype type, float max, float min, float speed);
		Entity* AgentEntity;
		AItype Type;
		void Face(glm::vec3 Target);
		void Seek(glm::vec3 Target);
		void Flee(glm::vec3 Target);
		void Pursue(glm::vec3 Target, glm::vec3 Force);
		void Evade(glm::vec3 Target, glm::vec3 Force);
		void Approach(glm::vec3 Target);
	private:
		float Max;
		float Min;
		float Speed;
	};
}