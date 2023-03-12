#pragma once
#include "../Component.h"
#include <iCollision.h>


namespace sas
{
	class RigidbodyComp : public Component
	{
	public:
		RigidbodyComp()
		{

		}
		virtual ~RigidbodyComp(){}
		bool Enabled;


		iCollision* i_CollisionBody;
	};
}