#include "Renderer.h"

namespace sas
{
	namespace Systems
	{
		Renderer::Renderer()
		{
			m_VertexArray = VertexArray::Create();
		}
		Renderer::~Renderer()
		{
		}
		void Renderer::Process(const std::vector<Entity*> entites, float dt)
		{

		}
		void Renderer::Init(std::vector<Entity*>* entityList, unsigned int shaderID)
		{
			for (std::vector<Entity*>::iterator it = entityList->begin();
				it != entityList->end();
				it++)
			{
				Entity* entity = *it;
				if(entity->HasComponent<MeshRenderer>())
				{
					MeshRenderer* meshRenderer = entity->GetComponentByType<MeshRenderer>();
					sModelDrawInfo modelDrawInfo;
					m_VertexArray->LoadModelIntoVAO(meshRenderer->Mesh, modelDrawInfo, shaderID);
				}
			}
		}
	}
}