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
			createBox(entity);
		}
		if (entity->name == "FemaleKnight")
		{
			createAgent(entity);
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
	mGround->bControl = false;
}

void Physic::Physic::createBox(sas::Entity* box)
{
	iShape* boxShape = new iSphereShape(1); //todo -> change to iboxshape
	iRigidBodyDesc desc;
	desc.bStatic = false;
	desc.mass = 1; // todo change mass
	desc.position = box->transform.Position;
	desc.velocity = glm::vec3(0.f);
	box->transform.p_physicBody = Factory->createRigidBody(desc, boxShape);
	World->addBody(box->transform.p_physicBody);
	this->entityList.push_back(box);
	box->bControl = false;
}

void Physic::Physic::createAgent(sas::Entity* agent)
{
	iShape* boxShape = new iSphereShape(1); //todo -> change to iboxshape
	iRigidBodyDesc desc;
	desc.bStatic = false;
	desc.mass = 40; // todo change mass
	desc.position = agent->transform.Position;
	desc.velocity = glm::vec3(0.f);
	agent->transform.p_physicBody = Factory->createRigidBody(desc, boxShape);
	World->addBody(agent->transform.p_physicBody);
	this->entityList.push_back(agent);
	agent->bControl = true;
}
