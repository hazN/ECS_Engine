#pragma once
#include <string>

namespace sas
{
	class GameObject : Entity
	{
		std::string Name;
		std::vector<Component*> m_Components;

	};
}