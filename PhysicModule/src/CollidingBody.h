#pragma once
#include <iCollision.h>

class CollidingBody
{
public:
	CollidingBody(iCollision* body1, iCollision* body2) : bodyA(body1), bodyB(body2) {}
	~CollidingBody() {}

	iCollision* bodyA;
	iCollision* bodyB;

};

