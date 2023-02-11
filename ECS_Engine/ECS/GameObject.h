#pragma once
#include "Entity.h"
#include <string>

namespace sas
{
	class GameObject : Entity
	{
		std::string Name;


	private:
		unsigned int m_ID;
		std::vector<Component*> m_Components;
	};
}