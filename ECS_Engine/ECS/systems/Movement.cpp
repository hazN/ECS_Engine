#include "Movement.h"
#include "../../core/Input.h"
#include <iostream>
#include "../components/RigidBodyComp.h"

namespace sas
{
	namespace Systems
	{
		Movement::Movement()
			:controlEntity(nullptr), physic_movement(nullptr)
		{
		}
		Movement::~Movement()
		{
		}
		void Movement::Process(const std::vector<Entity*>* entities, float dt)
		{
			if (!controlEntity)
			{
				return;
			}
			if (!rigidBody)
				return;
			if (Input::IsMouseButtonPressed(MouseButton::Button1))
				return;
			float speed = 145.f;

			float force = 0.3f;
			glm::vec3 direction(0.f);

			if (Input::IsKeyPressed(KeyCode::Q))
			{
				direction = Vec3(0.f, -speed * 50.f, 0.f);
			}

			if (Input::IsKeyPressed(KeyCode::E))
			{
				direction = Vec3(0.f, speed * 50.f, 0.f);
			}

			if (sas::Input::IsKeyPressed(KeyCode::W))
			{
				glm::vec3 temp = *GameplayCameraPostion;
				temp.y = 0.f;
				glm::vec3 forward = glm::normalize(rigidBody->getPosition() - temp);
				float x = forward.x * speed;
				float z = forward.z * speed;
				direction = glm::vec3(
					x,
					0.f,
					z
				);
			}
			if (sas::Input::IsKeyPressed(KeyCode::S))
			{
				glm::vec3 temp = *GameplayCameraPostion;
				temp.y = 0.f;
				glm::vec3 forward = glm::normalize(rigidBody->getPosition() - temp);
				float x = forward.x * speed;
				float z = forward.z * speed;
				direction = glm::vec3(
					-x,
					0.f,
					-z
				);
			}
			if (sas::Input::IsKeyPressed(KeyCode::A))
			{
				glm::vec3 temp = *GameplayCameraPostion;
				temp.y = 0.f;
				glm::vec3 forward = glm::normalize(rigidBody->getPosition() - temp);

				glm::mat4 rotationMat(1);
				rotationMat = glm::rotate(rotationMat, 90.0f, glm::vec3(0.0, 1.0, 0.0));
				glm::vec3 right = glm::vec3(rotationMat * glm::vec4(forward, 1.0));

				float x = right.x * speed;
				float z = right.z * speed;

				direction = glm::vec3(x,
					0.f,
					z
				);
			}
			if (sas::Input::IsKeyPressed(KeyCode::D))
			{
				glm::vec3 temp = *GameplayCameraPostion;
				temp.y = 0.f;
				glm::vec3 forward = glm::normalize(rigidBody->getPosition() - temp);

				glm::mat4 rotationMat(1);
				rotationMat = glm::rotate(rotationMat, -90.0f, glm::vec3(0.0, 1.0, 0.0));
				glm::vec3 right = glm::vec3(rotationMat * glm::vec4(forward, 1.0));

				float x = right.x * speed;
				float z = right.z * speed;

				direction = glm::vec3(
					x,
					0.f,
					z
				);
			}

			rigidBody->addForce(
				direction
			);

			//if (Input::IsKeyPressed(KeyCode::Q))
			//{
			//	rigidBody->addForce(Vec3(0.f, -speed * 50.f, 0.f));
			//	//physic_movement->UserForce(Vec3(0.f, -speed * 50.f, 0.f));
			//}

			//if (Input::IsKeyPressed(KeyCode::E))
			//{
			//	rigidBody->addForce(Vec3(0.f, speed * 50.f, 0.f));
			//}

			//if (Input::IsKeyPressed(KeyCode::W))
			//{
			//	rigidBody->addForce(Vec3(0.f, 0.f, speed));
			//	//controlEntity->transform.Position.z += speed * dt;
			//}
			//if (Input::IsKeyPressed(KeyCode::S))
			//{
			//	rigidBody->addForce(Vec3(0.f, 0.f, -speed));
			//	//controlEntity->transform.Position.z -= speed * dt;
			//}
			//if (Input::IsKeyPressed(KeyCode::A))
			//{
			//	rigidBody->addForce(Vec3(speed, 0.f, 0.f));
			//	//controlEntity->transform.Position.x += speed * dt;
			//}
			//if (Input::IsKeyPressed(KeyCode::D))
			//{
			//	rigidBody->addForce(Vec3(-speed, 0.f, 0.f));
			//	//controlEntity->transform.Position.x -= speed * dt;
			//}
		}
		void Movement::Init(std::vector<Entity*>* entities, Physic::Physic* phy_movement)
		{
			for (Entity* entity : *entities)
			{
				if (entity->name == "FemaleKnight")
				{
					controlEntity = entity;

					rigidBody = (iRigidBody*)entity->GetComponentByType<RigidbodyComp>()->i_CollisionBody;

				}
			}
			physic_movement = phy_movement;
		}
	}
}