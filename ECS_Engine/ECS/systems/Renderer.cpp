#include "Renderer.h"
#include "../../core/Renderer/RenderCommand.h"
#include <OpenGL/OpenGLShader.h>

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
		void Renderer::Process(const std::vector<Entity*>* entityList, float dt)
		{
			for (std::vector<Entity*>::const_iterator it = entityList->begin();
				it != entityList->end();
				it++)
			{
				Entity* entity = *it;
				if (entity->HasComponent<MeshRenderer>())
				{
					MeshRenderer* meshRenderer = entity->GetComponentByType<MeshRenderer>();
					sModelDrawInfo drawInfo;
					m_VertexArray->FindDrawInfoByModelName(meshRenderer->Mesh, drawInfo);

					// Bind the shader
					std::dynamic_pointer_cast<OpenGLShader>(m_Shader)->Bind();

					// Draw the vertices
					RenderCommand::DrawIndexed(drawInfo);

					// Unbind everything later
				}
			}

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