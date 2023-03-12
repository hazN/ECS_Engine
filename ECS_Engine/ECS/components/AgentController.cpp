#include "AgentController.h"

namespace sas
{
	AgentController::AgentController(Transform* player)
	{
		Player = player;
	}

	void AgentController::Update(float dt)
	{
		for (Agent agent : agents_)
		{
			switch (agent.type)
			{ // WILL FIX LATER
			//case AItype::ZOMBIE:
			//{
			//	if (glm::length(agent - player->physics_object->position) < 300.f)
			//	{
			//		glm::vec3 forwardVector;
			//		forwardVector.x = 2 * (Player->qRotation.x * Player->qRotation.z + Player->qRotation.w * Player->qRotation.y);
			//		forwardVector.y = 2 * (Player->qRotation.y * Player->qRotation.z - Player->qRotation.w * Player->qRotation.x);
			//		forwardVector.z = 1 - 2 * (Player->qRotation.x * Player->qRotation.x + Player->qRotation.y * Player->qRotation.y);
			//		float dotProduct = glm::dot(glm::normalize(agent.obj->position - Player->position), forwardVector);
			//		if (dotProduct > 0.2f)
			//		{
			//			if (glm::length(agent.obj->position - player->physics_object->position) < 250.f)
			//				agent.Evade(Player->position, player->physics_object->GetVelocity());
			//		}
			//		else if (dotProduct < 0.f)
			//		{
			//			if (glm::length(agent.obj->position - player->physics_object->position) < 300.f)
			//				agent.Pursue(Player->position, player->physics_object->GetVelocity());
			//		}
			//		else agent.obj->physics_object->ApplyForce(glm::vec3(0));
			//	}
			//}
			//break;
			//case AItype::RANGED:
			//{
			//	agent.Approach(player->physics_object->position);
			//}
			//break;
			//}
		}
	}
}