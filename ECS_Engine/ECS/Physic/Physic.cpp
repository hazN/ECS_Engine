#include "Physic.h"

Physic::Physic::Physic()
{
}

Physic::Physic::~Physic()
{
}

void Physic::Physic::init()
{
	Factory = new PhysicFactory();
	World = Factory->createWorld();

	World->setGravity(glm::vec3(0, -9.8f, 0));
}

void Physic::Physic::destroy()
{
}

void Physic::Physic::update(float dt)
{
	World->timeStep(dt);
	//todo
	for (int i = 0; i < entityList.size(); i++)
	{
		sas::Entity* body = entityList[i];
		iRigidBody* rigidBody = dynamic_cast<iRigidBody*>(body->transform.p_physicBody);
		if (body->transform.p_physicBody != nullptr)
		{
			body->transform.Position = rigidBody->getPosition();
			body->transform.Rotation = rigidBody->getRotation();
		}
	}
}

void Physic::Physic::UserForce(glm::vec3 dir)
{
	for (int i =0; i< entityList.size(); i++)
	{
		if (entityList[i]->bControl)
		{
			sas::Entity* body = entityList[i];
			iRigidBody* rigidBody = dynamic_cast<iRigidBody*>(body->transform.p_physicBody);
			if (body->transform.p_physicBody != nullptr)
			{
				rigidBody->addForce(dir * 5.f);
			}
		}
	}
}



void Physic::Physic::createWorldObj(std::vector<sas::Entity*>* entityList)
{
	for (sas::Entity* entity : *entityList)
	{
		if (entity->name == "Ground")
		{
			createPlane(entity);
		}
		if (entity->name == "TestCube")
		{
			//todo
		}
		if (entity->name == "FemaleKnight")
		{
			//todo
		}
	}
}

void Physic::Physic::createPlane(sas::Entity* mGround)
{
	iShape* groundShape = new iPlaneShape(glm::vec3(0.f, 1.f, 0.f), 0.f);
	iRigidBodyDesc groundDesc;
	groundDesc.bStatic = true;
	groundDesc.mass = 0;
	groundDesc.position = mGround->transform.Position;
	groundDesc.velocity = glm::vec3(0.f);
	mGround->transform.p_physicBody = Factory->createRigidBody(groundDesc, groundShape);
	World->addBody(mGround->transform.p_physicBody);
}
