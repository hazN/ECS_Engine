#include "Renderer.h"
#include "../../core/Renderer/RenderCommand.h"
#include <OpenGL/OpenGLShader.h>
#include "../../core/Application.h"

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
			RenderCommand::SetViewport(0, 0, Application::Get().GetWindow().GetWidth(), Application::Get().GetWindow().GetWidth());
			RenderCommand::Clear();
			RenderCommand::SetClearColor(glm::vec4(0.2f, 0.2f, 0.2f, 1.f));
			for (std::vector<Entity*>::const_iterator it = entityList->begin();
				it != entityList->end();
				it++)
			{
				Entity* entity = *it;
				if (entity->HasComponent<MeshRenderer>())
				{
					MeshRenderer* meshRenderer = entity->GetComponentByType<MeshRenderer>();
					sModelDrawInfo drawInfo;
					RenderCommand::SetCullFace();
					m_VertexArray->FindDrawInfoByModelName(meshRenderer->Mesh, drawInfo);

					// Bind the shader
					m_Shader->Bind();
					RenderCommand::SetPolygonMode(meshRenderer->material->bWireframe);
					// Draw the vertices
					RenderCommand::DrawIndexed(drawInfo);

					// Unbind everything later
				}
			}

		}
		void Renderer::CompileShaders(std::string& vertexSourceFile, std::string& fragmentSourcFile)
		{
			m_Shader = Shader::Create(vertexSourceFile, fragmentSourcFile);
		}
		void Renderer::Init(std::vector<Entity*>* entityList, std::string& vertexSourceFile, std::string& fragmentSourcFile)
		{
			CompileShaders(vertexSourceFile, fragmentSourcFile);
			m_Shader->Bind();
			std::shared_ptr<OpenGLShader> openGLShader = std::dynamic_pointer_cast<OpenGLShader>(m_Shader);
			for (std::vector<Entity*>::iterator it = entityList->begin();
				it != entityList->end();
				it++)
			{
				Entity* entity = *it;
				if(entity->HasComponent<MeshRenderer>())
				{
					MeshRenderer* meshRenderer = entity->GetComponentByType<MeshRenderer>();
					sModelDrawInfo modelDrawInfo;
					m_VertexArray->LoadPlyFiles(meshRenderer->Path, modelDrawInfo);
					m_VertexArray->LoadModelIntoVAO(meshRenderer->Mesh, modelDrawInfo, openGLShader->GetID());
				}
			}
		}
	}
}