#pragma once
#include "MeshRenderer.h"
#include "Agent.h"
namespace sas
{
	class AgentController
	{
	public:
		AgentController() = default;
		~AgentController() = default;

		std::vector<Agent> agents_;
		Transform* Player;
		AgentController(Transform* player);
		void Update(float dt);
	};
}