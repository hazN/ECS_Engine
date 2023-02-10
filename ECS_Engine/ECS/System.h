#pragma once

#include <vector>

#include "Entity.h"

namespace sas{
	class System
	{
	public:
		virtual void Process(const std::vector < Entity* > entites, float dt) = 0;
		virtual ~System() {}
	};
}