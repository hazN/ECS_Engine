#pragma once
#include <vector>
#include "Component.h"
#include "Transform.h"

namespace sas
{
	class Entity
	{
	public:
		Transform transform;

		inline unsigned int GetID() const { return m_ID; }

		template<class T>
		bool HasComponent()
		{
			for (int i = 0; i < m_Components.size(); i++)
			{
				T* component = dynamic_cast<T*>(m_Components[i]);
				if (component != nullptr)
					return true;
			}
			return false;
		}

		template<class T>
		T* GetComponentByType()
		{
			for (int i = 0; i < m_Components.size(); i++)
			{
				T* component = dynamic_cast<T*>(m_Components[i]);
				if (component != nullptr)
					return component;
			}
			return nullptr;
		}

		template<class T>
		bool AddComponent(T* newComponent)
		{
			if (HasComponent<T>())
			{
				return false;
			}

			m_Components.push_back(newComponent);
			return true;
		}

		template<class T>
		T* RemoveComponent()
		{
			for (std::vector<Component*>::iterator it = m_Components.begin();
				it != m_Components.size(); it++)
			{
				T* component = dynamic_cast<T*>(*it);
				if (component != nullptr)
				{
					m_Components.erase(it);
					return *it;
				}
			}
			return nullptr;
		}

		inline std::vector<Component*> GetAllComponents() const { return m_Components; }

	private:
		unsigned int m_ID;
		std::vector<Component*> m_Components;
	};
}