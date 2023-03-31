#pragma once
#include <iCollisionListener.h>
#include "..\..\core\LuaBrain.h"
namespace Physic
{
    //class : CollisionListener
    //Summary : Listen for collision event from physic module
    class CollisionListener :
        public iCollisionListener
    {
    public:
        CollisionListener();
        virtual ~CollisionListener();

        virtual void notifyCollision(iCollision* body1, iCollision* body2) override;
        LuaBrain* Lua;
    };
}

