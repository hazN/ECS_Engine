#include "Physic.h"
#include "../components/RigidBodyComp.h"

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

	collisionListener = new CollisionListener();
	World->setGravity(glm::vec3(0, -9.8f, 0));
	World->addToCollisionListener(collisionListener);
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
		iRigidBody* rigidBody = (iRigidBody*)body->GetComponentByType<sas::RigidbodyComp>()->i_CollisionBody;
		if (rigidBody != nullptr)
		{
			body->transform.Position = rigidBody->getPosition();
			body->transform.Rotation = rigidBody->getRotation();
		}
	}
}

void Physic::Physic::UserForce(glm::vec3 dir)
{

}



void Physic::Physic::createWorldObj(std::vector<sas::Entity*>* entityList)
{
	for (sas::Entity* entity : *entityList)
	{
		if (entity->name == "Ground")
		{
			iCollision* collisionBody = createPlane(entity);
			sas::RigidbodyComp* rigidBody = new sas::RigidbodyComp();
			rigidBody->i_CollisionBody = collisionBody;
			entity->AddComponent<sas::RigidbodyComp>(rigidBody);
		}
		if (entity->name == "TestCube")
		{
			iCollision* collisionBody = createBox(entity);
			sas::RigidbodyComp* rigidBody = new sas::RigidbodyComp();
			rigidBody->i_CollisionBody = collisionBody;
			entity->AddComponent<sas::RigidbodyComp>(rigidBody);
		}
		if (entity->name == "FemaleKnight")
		{
			iCollision* collisionBody = createAgent(entity);
			sas::RigidbodyComp* rigidBody = new sas::RigidbodyComp();
			rigidBody->i_CollisionBody = collisionBody;
			entity->AddComponent<sas::RigidbodyComp>(rigidBody);
		}
	}
}

iCollision* Physic::Physic::createPlane(sas::Entity* mGround)
{
	iShape* groundShape = new iPlaneShape(glm::vec3(0.f, 1.f, 0.f), 0.f);
	iRigidBodyDesc groundDesc;
	groundDesc.bStatic = true;
	groundDesc.mass = 0;
	groundDesc.position = mGround->transform.Position;
	groundDesc.velocity = glm::vec3(0.f);
	iCollision* body = Factory->createRigidBody(groundDesc, groundShape);
	World->addBody(body);
	return body;
}

iCollision* Physic::Physic::createBox(sas::Entity* box)
{
	iShape* boxShape = new iSphereShape(1); //todo -> change to iboxshape
	iRigidBodyDesc desc;
	desc.bStatic = false;
	desc.mass = 20; // todo change mass
	desc.position = box->transform.Position + glm::vec3(0.f, 20.f, 0.f);
	desc.velocity = glm::vec3(0.f);
	iCollision* body = Factory->createRigidBody(desc, boxShape);
	World->addBody(body);
	this->entityList.push_back(box);
	return body;
}

iCollision* Physic::Physic::createAgent(sas::Entity* agent)
{
	iShape* boxShape = new iSphereShape(1); //todo -> change to iboxshape
	iRigidBodyDesc desc;
	desc.bStatic = false;
	desc.mass = 40; // todo change mass
	desc.position = agent->transform.Position + glm::vec3(0.f, 20.f, 0.f);
	desc.velocity = glm::vec3(0.f);
	iCollision* body = Factory->createRigidBody(desc, boxShape);
	World->addBody(body);
	this->entityList.push_back(agent);
	return body;
}
