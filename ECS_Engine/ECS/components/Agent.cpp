#include "Agent.h"
#include "../Transform.h"
#include <glm/gtc/quaternion.hpp>
#include <glm/gtx/quaternion.hpp>
#include <glm/gtx/euler_angles.hpp>
#include <glm/gtx/norm.hpp>

#include <glm/quaternion_utils.h>
#include <RigidBody.h>
#include "RigidBodyComp.h"
namespace sas
{
	// Method : Agent
	// Summary: Constructor for Agent, and the type of ai
	// Accepts: Entity* agent, AItype type
	Agent::Agent(Entity* agent, AItype type)
	{
		this->AgentEntity = agent;
		this->Type = type;
		Max = 70.f;
		Min = 50.f;
		Speed = 50.1f;
	}

	// Method : Agent
	// Summary: Constructor for Agent, the type of ai and speed
	// Accepts: Entity* agent, AItype type, float speed
	Agent::Agent(Entity* agent, AItype type, float speed)
	{
		this->AgentEntity = agent;
		this->Type = type;
		Max = 70.f;
		Min = 50.f;
		Speed = speed;
	}

	// Method : Agent
	// Summary: Constructor for Agent, the type of ai and max/min aggro distances
	// Accepts: Entity* agent, AItype type, float speed
	Agent::Agent(Entity* agent, AItype type, float max, float min)
	{
		this->AgentEntity = agent;
		this->Type = type;
		Max = max;
		Min = min;
		Speed = 1.1f;
	}

	// Method : Agent
	// Summary: Constructor for Agent, the type of ai, speed and max/min aggro distances
	// Accepts: Entity* agent, AItype type, float speed
	Agent::Agent(Entity* agent, AItype type, float max, float min, float speed)
	{
		this->AgentEntity = agent;
		this->Type = type;
		Max = max;
		Min = min;
		Speed = speed;
	}

	// Method : Face
	// Summary: Just a direct face function to be used to compliment other ai functions
	// Accepts: vec3 Target
	void Agent::Face(glm::vec3 Target)
	{
		glm::vec3 direction = glm::normalize(AgentEntity->transform.Position - Target);
		//transform->Rotation = RotationBetweenVectors(direction, direction);
		glm::quat targetDir = glm::quat(direction);
		//transform->Rotation = RotateTowards(transform->Rotation, targetDir, 3.14f * 0.5);
		glm::vec3 up = glm::vec3(0, 1, 0);
		AgentEntity->transform.Rotation = (direction, up);
	}

	// Method : Seek
	// Summary: Takes given target, rotates and moves towards it
	// Accepts: vec3 Target
	void Agent::Seek(glm::vec3 Target)
	{
		glm::vec3 direction = glm::normalize(Target - AgentEntity->transform.Position);
		glm::quat targetDir = q_utils::LookAt(-direction, glm::vec3(0, 1, 0));
		AgentEntity->transform.Rotation = q_utils::RotateTowards(AgentEntity->transform.Rotation, targetDir, 3.14f * 0.005f);
		RigidbodyComp* rigidBodyComp = (RigidbodyComp*) AgentEntity->GetComponentByType<RigidbodyComp>();
		iRigidBody* rigidBody = (iRigidBody*) rigidBodyComp->i_CollisionBody;
		if (rigidBody)
			rigidBody->addForce(glm::normalize(direction) * Speed);
	}

	// Method : Flee
	// Summary: Takes given target, rotates and moves away from it
	// Accepts: vec3 Target
	void Agent::Flee(glm::vec3 Target)
	{
		glm::vec3 direction = glm::normalize(Target - AgentEntity->transform.Position);
		glm::quat targetDir = q_utils::LookAt(direction, glm::vec3(0, 1, 0));
		AgentEntity->transform.Rotation = q_utils::RotateTowards(AgentEntity->transform.Rotation, targetDir, 3.14f * 0.005f);
		// NEED TO APPLY FORCE 
		//transform->->ApplyForce(glm::normalize(-direction) * Speed);
		RigidbodyComp* rigidBodyComp = (RigidbodyComp*)AgentEntity->GetComponentByType<RigidbodyComp>();
		iRigidBody* rigidBody = (iRigidBody*)rigidBodyComp->i_CollisionBody;
		if (rigidBody)
			rigidBody->addForce(glm::normalize(-direction) * Speed);
	}

	// Method : Pursue
	// Summary: Takes given target, rotates and moves towards its future position using velocity
	// Accepts: vec3 Target, vec3 Velocity
	void Agent::Pursue(glm::vec3 Target, glm::vec3 Velocity)
	{
		Target += Velocity * 50.f;
		glm::vec3 direction = glm::normalize(Target - AgentEntity->transform.Position);
		glm::quat targetDir = q_utils::LookAt(-direction, glm::vec3(0, 1, 0));
		AgentEntity->transform.Rotation = q_utils::RotateTowards(AgentEntity->transform.Rotation, targetDir, 3.14f * 0.005f);
		// NEED TO APPLY FORCE
		//transform->physics_transformect->ApplyForce(glm::normalize(direction) * Speed);
		RigidbodyComp* rigidBodyComp = (RigidbodyComp*)AgentEntity->GetComponentByType<RigidbodyComp>();
		iRigidBody* rigidBody = (iRigidBody*)rigidBodyComp->i_CollisionBody;
		if (rigidBody)
			rigidBody->addForce(glm::normalize(direction) * Speed);
	}

	// Method : Evade
	// Summary: Takes given target, rotates and moves away from its future position using velocity
	// Accepts: vec3 Target, vec3 Velocity
	void Agent::Evade(glm::vec3 Target, glm::vec3 Velocity)
	{
		if (glm::length(AgentEntity->transform.Position - Target) < 300.f)
		{
			Target -= Velocity * 50.f;
			glm::vec3 direction = glm::normalize(Target - AgentEntity->transform.Position);
			glm::quat targetDir = q_utils::LookAt(direction, glm::vec3(0, 1, 0));
			AgentEntity->transform.Rotation = q_utils::RotateTowards(AgentEntity->transform.Rotation, targetDir, 3.14f * 0.005f);
			RigidbodyComp* rigidBodyComp = (RigidbodyComp*)AgentEntity->GetComponentByType<RigidbodyComp>();
			iRigidBody* rigidBody = (iRigidBody*)rigidBodyComp->i_CollisionBody;
			if(rigidBody)
				rigidBody->addForce(glm::normalize(-direction) * Speed);
		}
	}

	// Method : Approach
	// Summary: Takes given target, and maintains a set distance between itself and the target
	// Accepts: vec3 Target
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