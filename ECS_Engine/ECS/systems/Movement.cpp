#include "Movement.h"
#include "../../core/Input.h"
#include <iostream>

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
			float speed = 10.f;
			if (Input::IsKeyPressed(KeyCode::Up))
			{
				physic_movement->UserForce(Vec3(0.f, 0.f, 1.f));
				//controlEntity->transform.Position.z += speed * dt;
			}
			if (Input::IsKeyPressed(KeyCode::Down))
			{
				physic_movement->UserForce(Vec3(0.f, 0.f, -1.f));
				//controlEntity->transform.Position.z -= speed * dt;
			}
			if (Input::IsKeyPressed(KeyCode::Left))
			{
				physic_movement->UserForce(Vec3(1.f, 0.f, 0.f));
				//controlEntity->transform.Position.x += speed * dt;
			}
			if (Input::IsKeyPressed(KeyCode::Right))
			{
				physic_movement->UserForce(Vec3(-1.f, 0.f, 0.f));
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
				}
			}
			physic_movement = phy_movement;
		}
	}
}