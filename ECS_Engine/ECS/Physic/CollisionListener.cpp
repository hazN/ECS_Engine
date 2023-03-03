#include "CollisionListener.h"
#include <iostream>

Physic::CollisionListener::CollisionListener()
{
}

Physic::CollisionListener::~CollisionListener()
{
}

void Physic::CollisionListener::notifyCollision(iCollision* body1, iCollision* body2)
{
	std::cout << "pong!!" << std::endl;
}
