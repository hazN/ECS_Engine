#include "Movement.h"
#include "../../core/Input.h"
#include <iostream>

namespace sas
{
	namespace Systems
	{
		Movement::Movement()
			:controlEntity(nullptr)
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
				controlEntity->transform.Position.z += speed * dt;
			}
			if (Input::IsKeyPressed(KeyCode::Down))
			{
				controlEntity->transform.Position.z -= speed * dt;
			}
			if (Input::IsKeyPressed(KeyCode::Left))
			{
				controlEntity->transform.Position.x += speed * dt;
			}
			if (Input::IsKeyPressed(KeyCode::Right))
			{
				controlEntity->transform.Position.x -= speed * dt;
			}
		}
		void Movement::Init(std::vector<Entity*>* entities)
		{
			for (Entity* entity : *entities)
			{
				if (entity->name == "FemaleKnight")
				{
					controlEntity = entity;
				}
				/*if (entity->name == "Ground")
				{
					entity->transform.Rotation = glm::quat(glm::vec3(-1.57f, 0.f, 0.f));
					std::cout << "New Rotation for Ground:" << std::endl;
					std::cout << "\t{ " 
						<< entity->transform.Rotation.w << ","
						<< entity->transform.Rotation.x << ","
						<< entity->transform.Rotation.y << ","
						<< entity->transform.Rotation.z << " ]" << std::endl;
				}*/
			}
		}
	}
}