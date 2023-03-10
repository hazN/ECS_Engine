#pragma once
#include <vector>
#include "Component.h"
#include "Transform.h"
#include "components/MeshRenderer.h"
#include "components/Light.h"

namespace sas
{
	// Holds list of components
	class Entity
	{
	public:
		// Added this here but I assume later will just iterate through the components
		std::string name;
		Transform transform;
		Light light;
		MeshRenderer mesh;

		inline unsigned int GetID() const { return m_ID; }

		// Has <T> component
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

		// Get <T> component
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

		// Add <T> component
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

		// Remove <T> component
		template<class T>
		T* RemoveComponent()
		{
			for (std::vector<Component*>::iterator it = m_Components.begin();
				it != m_Components.end(); it++)
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

		// Get all the components
		inline std::vector<Component*> GetAllComponents() const { return m_Components; }

		// Set entity ID
		inline void SetID(int id) { m_ID = id; };
	private:
		unsigned int m_ID;
		std::vector<Component*> m_Components;
	};
}