#pragma once
#include "iCollision.h"

// class : iCollisionListener
// Summary : interface class for collision listener
class iCollisionListener
{
public:
	virtual ~iCollisionListener() {}

	virtual void notifyCollision(iCollision* body1, iCollision* body2) = 0;

protected:
	iCollisionListener() {}

};

