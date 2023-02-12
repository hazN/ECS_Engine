#pragma once
#include "Entity.h"

namespace sas
{
	class EntityManager
	{
	public:
		void Init();
		
		inline std::vector<Entity*> GetEntities() const { return m_Entities; }

	private:
		std::vector<Entity*> m_Entities;
	};
}