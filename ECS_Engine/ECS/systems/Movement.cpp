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

			if (Input::IsKeyPressed(KeyCode::Q))
			{
				rigidBody->addForce(Vec3(0.f, -speed * 50.f, 0.f));
				//physic_movement->UserForce(Vec3(0.f, -speed * 50.f, 0.f));
			}

			if (Input::IsKeyPressed(KeyCode::E))
			{
				rigidBody->addForce(Vec3(0.f, speed * 50.f, 0.f));
			}

			if (Input::IsKeyPressed(KeyCode::W))
			{
				rigidBody->addForce(Vec3(0.f, 0.f, speed));
				//controlEntity->transform.Position.z += speed * dt;
			}
			if (Input::IsKeyPressed(KeyCode::S))
			{
				rigidBody->addForce(Vec3(0.f, 0.f, -speed));
				//controlEntity->transform.Position.z -= speed * dt;
			}
			if (Input::IsKeyPressed(KeyCode::A))
			{
				rigidBody->addForce(Vec3(speed, 0.f, 0.f));
				//controlEntity->transform.Position.x += speed * dt;
			}
			if (Input::IsKeyPressed(KeyCode::D))
			{
				rigidBody->addForce(Vec3(-speed, 0.f, 0.f));
				//controlEntity->transform.Position.x -= speed * dt;
			}
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