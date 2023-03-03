#pragma once
#include <iPhysicFactory.h>
#include <iPhysicWorld.h>
#include "../Entity.h"

#define GDP_Physics
#if defined GDP_Physics
#pragma comment(lib, "PhysicModule.lib")
#include <PhysicFactory.h>
#endif

namespace Physic
{
	class Physic
	{
	public:
		Physic();
		~Physic();

		void init();
		void destroy();
		void update(float dt);
		void UserForce(glm::vec3 dir);
		void setActive(int num);

		void createWorldObj(std::vector<sas::Entity*>* entityList);
		void createPlane(sas::Entity* mGround);
		void createBox(sas::Entity* box);
		void createAgent(sas::Entity* agent);
		//void createBall(cMeshObj* mOBJ, float size);


		iPhysicFactory* Factory;
		iPhysicWorld* World;
		std::vector<sas::Entity*> entityList;
	};

}