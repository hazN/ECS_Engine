#include "AgentController.h"
#include <RigidBody.h>
#include "RigidBodyComp.h"

namespace sas
{
	AgentController::AgentController(Entity* player)
	{
		Player = player;
	}

	void AgentController::Update(float dt)
	{
		for (Agent* agent : agents_)
		{
			switch (agent->Type)
			{ // WILL FIX LATER
			case AItype::ZOMBIE:
			{
				if (glm::length(agent->AgentEntity->transform.Position - Player->transform.Position) < 300.f)
				{
					RigidbodyComp* rigidBodyComp = (RigidbodyComp*)agent->AgentEntity->GetComponentByType<RigidbodyComp>();
					iRigidBody* rigidBody = (iRigidBody*)rigidBodyComp->i_CollisionBody; glm::vec3 forwardVector;
					forwardVector.x = 2 * (Player->transform.Rotation.x * Player->transform.Rotation.z + Player->transform.Rotation.w * Player->transform.Rotation.y);
					forwardVector.y = 2 * (Player->transform.Rotation.y * Player->transform.Rotation.z - Player->transform.Rotation.w * Player->transform.Rotation.x);
					forwardVector.z = 1 - 2 * (Player->transform.Rotation.x * Player->transform.Rotation.x + Player->transform.Rotation.y * Player->transform.Rotation.y);
					float dotProduct = glm::dot(glm::normalize(agent->AgentEntity->transform.Position - Player->transform.Position), forwardVector);
					if (dotProduct > 0.2f)
					{
						if (glm::length(agent->AgentEntity->transform.Position - Player->transform.Position) < 250.f)
							agent->Seek(Player->transform.Position + glm::vec3(5.f, 0.f, 5.f));
							//agent->Evade(Player->position, player->physics_object->GetVelocity());
					}
					//else if (dotProduct < 0.f)
					//{
					//	if (glm::length(agent->AgentEntity->transform.Position - Player->transform.Position) < 300.f)
					//		agent->Flee(Player->transform.Position);
					//		//agent->Pursue(Player->position, player->physics_object->GetVelocity());
					//}
					else if(rigidBody) rigidBody->addForce(glm::vec3(0.f));
				}
			}
			break;
		/*	case AItype::RANGED:
			{
				agent->Approach(player->physics_object->position);
			}
			break;
			*/
			}
		}
	}
}