#pragma once

#include <vector>

#include "Entity.h"

namespace sas{
	namespace Systems
	{
		// Base class for all system
		class System
		{
		public:
			// Process entities every frame
			virtual void Process(const std::vector < Entity* >* entites, float dt) = 0;
			virtual ~System() {}
		};
	}
}