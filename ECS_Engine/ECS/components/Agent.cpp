#include "Agent.h"
#include "../Transform.h"
#include <glm/gtc/quaternion.hpp>
#include <glm/gtx/quaternion.hpp>
#include <glm/gtx/euler_angles.hpp>
#include <glm/gtx/norm.hpp>

#include <glm/quaternion_utils.h>
#include <RigidBody.h>
namespace sas
{
	Agent::Agent(Entity* agent, AItype type)
	{
		this->AgentEntity = agent;
		this->Type = type;
		Max = 70.f;
		Min = 50.f;
		Speed = 1.1f;
	}

	Agent::Agent(Entity* agent, AItype type, float speed)
	{
		this->AgentEntity = agent;
		this->Type = type;
		Max = 70.f;
		Min = 50.f;
		Speed = speed;
	}

	Agent::Agent(Entity* agent, AItype type, float max, float min)
	{
		this->AgentEntity = agent;
		this->Type = type;
		Max = max;
		Min = min;
		Speed = 1.1f;
	}
	Agent::Agent(Entity* agent, AItype type, float max, float min, float speed)
	{
		this->AgentEntity = agent;
		this->Type = type;
		Max = max;
		Min = min;
		Speed = speed;
	}
	void Agent::Face(glm::vec3 Target)
	{
		glm::vec3 direction = glm::normalize(AgentEntity->transform.Position - Target);
		//transform->Rotation = RotationBetweenVectors(direction, direction);
		glm::quat targetDir = glm::quat(direction);
		//transform->Rotation = RotateTowards(transform->Rotation, targetDir, 3.14f * 0.5);
		glm::vec3 up = glm::vec3(0, 1, 0);
		AgentEntity->transform.Rotation = (direction, up);
	}

	void Agent::Seek(glm::vec3 Target)
	{
		glm::vec3 direction = glm::normalize(Target - AgentEntity->transform.Position);
		glm::quat targetDir = q_utils::LookAt(-direction, glm::vec3(0, 1, 0));
		AgentEntity->transform.Rotation = q_utils::RotateTowards(AgentEntity->transform.Rotation, targetDir, 3.14f * 0.005f);
		// NEED TO APPLY FORCE 		
		//transform->p_physicBody->ApplyForce(glm::normalize(direction) * Speed);
		AgentEntity->GetComponentByType<RigidBody>()->addForce(glm::normalize(direction) * Speed);
	}

	void Agent::Flee(glm::vec3 Target)
	{
		glm::vec3 direction = glm::normalize(Target - AgentEntity->transform.Position);
		glm::quat targetDir = q_utils::LookAt(direction, glm::vec3(0, 1, 0));
		AgentEntity->transform.Rotation = q_utils::RotateTowards(AgentEntity->transform.Rotation, targetDir, 3.14f * 0.005f);
		// NEED TO APPLY FORCE 
		//transform->->ApplyForce(glm::normalize(-direction) * Speed);
		AgentEntity->GetComponentByType<RigidBody>()->addForce(glm::normalize(-direction) * Speed);
	}

	void Agent::Pursue(glm::vec3 Target, glm::vec3 Velocity)
	{
		Target += Velocity * 50.f;
		glm::vec3 direction = glm::normalize(Target - AgentEntity->transform.Position);
		glm::quat targetDir = q_utils::LookAt(-direction, glm::vec3(0, 1, 0));
		AgentEntity->transform.Rotation = q_utils::RotateTowards(AgentEntity->transform.Rotation, targetDir, 3.14f * 0.005f);
		// NEED TO APPLY FORCE
		//transform->physics_transformect->ApplyForce(glm::normalize(direction) * Speed);
		AgentEntity->GetComponentByType<RigidBody>()->addForce(glm::normalize(direction) * Speed);
	}

	void Agent::Evade(glm::vec3 Target, glm::vec3 Velocity)
	{
		if (glm::length(AgentEntity->transform.Position - Target) < 300.f)
		{
			Target -= Velocity * 50.f;
			glm::vec3 direction = glm::normalize(Target - AgentEntity->transform.Position);
			glm::quat targetDir = q_utils::LookAt(direction, glm::vec3(0, 1, 0));
			AgentEntity->transform.Rotation = q_utils::RotateTowards(AgentEntity->transform.Rotation, targetDir, 3.14f * 0.005f);
			// NEED TO APPLY FORCE
			//transform->physics_transformect->ApplyForce(glm::normalize(-direction) * Speed);
			AgentEntity->GetComponentByType<RigidBody>()->addForce(glm::normalize(-direction) * Speed);
		}
	}

	void Agent::Approach(glm::vec3 Target)
	{
		if (glm::length(AgentEntity->transform.Position - Target) > Max)
		{
			Seek(Target);
		}
		else if (glm::length(AgentEntity->transform.Position - Target) < Min)
		{
			Flee(Target);
		}
		else
		{
			glm::vec3 direction = glm::normalize(Target - AgentEntity->transform.Position);
			glm::quat targetDir = q_utils::LookAt(-direction, glm::vec3(0, 1, 0));
			AgentEntity->transform.Rotation = q_utils::RotateTowards(AgentEntity->transform.Rotation, targetDir, 3.14f * 0.005f);
		}
	}
}