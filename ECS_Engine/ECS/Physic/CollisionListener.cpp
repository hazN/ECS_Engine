#include "CollisionListener.h"
#include <iostream>

Physic::CollisionListener::CollisionListener()
{
}

Physic::CollisionListener::~CollisionListener()
{
}

// Method : notifyCollision
// Summary: Interface function when collision between body1 and body2 was happen
// Accepts: iCollision* body1,body2
void Physic::CollisionListener::notifyCollision(iCollision* body1, iCollision* body2)
{
	//std::cout << "pong!!" << std::endl;
	// lua call fx
	Lua->LoadScript("collision");
}
