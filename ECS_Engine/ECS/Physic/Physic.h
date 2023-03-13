#pragma once
#include <iPhysicFactory.h>
#include <iPhysicWorld.h>
#include "../Entity.h"

#include "CollisionListener.h"

#define GDP_Physics
#if defined GDP_Physics
#pragma comment(lib, "PhysicModule.lib")
#include <PhysicFactory.h>
#endif

namespace Physic
{
	//class : Physic
	//Summary : Physic world object which is connect to Physic module via Physic Interface
	class Physic
	{
	public:
		Physic();
		~Physic();

		void init();
		void destroy();
		void update(float dt);
		void UserForce(glm::vec3 dir);
		//void setActive(int num);

		void createWorldObj(std::vector<sas::Entity*>* entityList);
		iCollision* createPlane(sas::Entity* mGround);
		iCollision* createBox(sas::Entity* box);
		iCollision* createAgent(sas::Entity* agent);
		

		CollisionListener* collisionListener;
		iPhysicFactory* Factory;
		iPhysicWorld* World;
		std::vector<sas::Entity*> entityList;
	};

}