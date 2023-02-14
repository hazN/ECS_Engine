#include "Renderer.h"
#include "../../core/Renderer/RenderCommand.h"
#include <OpenGL/OpenGLShader.h>
#include "../../core/Application.h"
#include <glm/ext/matrix_transform.hpp>
#include <glm/gtc/quaternion.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "../../core/Input.h"
#include <iostream>
#include <GLFW/glfw3.h>

namespace sas
{
	namespace Systems
	{
		Entity* Renderer::EDITOR_CAMERA = new Entity();
		Renderer::Renderer()
		{
			m_VertexArray = VertexArray::Create();
		}
		Renderer::~Renderer()
		{
		}
		void Renderer::Process(const std::vector<Entity*>* entityList, float dt)
		{
			glm::vec3 defFront = cameraFront;

			float cameraSpeed;
			if (Input::IsKeyPressed(KeyCode::LeftShift))
				cameraSpeed = 10.5f * dt;
			else  cameraSpeed = 2.5f * dt;
			if (Input::IsKeyPressed(KeyCode::W))
				EDITOR_CAMERA->transform.Position += cameraSpeed * defFront;
			if (Input::IsKeyPressed(KeyCode::S))
				EDITOR_CAMERA->transform.Position -= cameraSpeed * defFront;
			if (Input::IsKeyPressed(KeyCode::A))
				EDITOR_CAMERA->transform.Position -= cameraRight * cameraSpeed;
			if (Input::IsKeyPressed(KeyCode::D))
				EDITOR_CAMERA->transform.Position += cameraRight * cameraSpeed;

			if (Input::IsKeyPressed(KeyCode::Q))     // Down
			{
				EDITOR_CAMERA->transform.Position.y -= cameraSpeed;
			}
			if (Input::IsKeyPressed(KeyCode::E))      // Up
			{
				EDITOR_CAMERA->transform.Position.y += cameraSpeed;
			}
			xpos = Input::GetMouseX();
			ypos = Input::GetMouseY();

			if (firstMouse)
			{
				lastX = xpos;
				lastY = ypos;
				firstMouse = false;
			}

			float xoffset = xpos - lastX;
			float yoffset = lastY - ypos; // reversed since y-coordinates go from bottom to top

			lastX = xpos;
			lastY = ypos;
			if (Input::IsMouseButtonPressed(MouseButton::Button1))
			{
				ProcessMouseMovement(xoffset, yoffset);
			}
			int width = Application::Get().GetWindow().GetWidth();
			int height = Application::Get().GetWindow().GetHeight();
			float ratio = width / (float)height;
			RenderCommand::SetViewport(0, 0, width, height);
			RenderCommand::SetClearColor(glm::vec4(0.2f, 0.2f, 0.2f, 1.f));
			RenderCommand::Clear();

			for (std::vector<Entity*>::const_iterator it = entityList->begin();
				it != entityList->end();
				it++)
			{
				//{	//.................TEMPORARY.................\\

				//	GLFWwindow* m_Window = (GLFWwindow*)Application::Get().GetWindow().GetNativeWindow();
				//	std::stringstream title;
				//	title << "CAMERA: " << EDITOR_CAMERA->transform.Position.x << ", "
				//		<< EDITOR_CAMERA->transform.Position.y << ", "
				//		<< EDITOR_CAMERA->transform.Position.z;
				//	glfwSetWindowTitle(m_Window, title.str().c_str());

				//	//...........................................\\

				//}
				Entity* entity = *it;
				if (entity->HasComponent<MeshRenderer>())
				{
					std::shared_ptr<OpenGLShader> openGLShader = std::dynamic_pointer_cast<OpenGLShader>(m_Shader);
					MeshRenderer* meshRenderer = entity->GetComponentByType<MeshRenderer>();
					m_Shader->Bind();
					glm::mat4x4 matModel = glm::mat4x4(1.0f); ;
					glm::mat4x4 matProjection;
					glm::mat4x4 matView;

					glm::vec3 upVector = glm::vec3(0.0f, 1.0f, 0.0f);
					matView = glm::lookAt(EDITOR_CAMERA->transform.Position,
						EDITOR_CAMERA->transform.Position + cameraFront,
						upVector);
					matProjection = glm::perspective(
						0.6f,
						ratio,
						0.1f,
						10000.0f);

					openGLShader->UploadUniformFloat4("eyeLocation", glm::vec4(EDITOR_CAMERA->transform.Position, 1));
					openGLShader->UploadUniformMat4("mView", matView);
					openGLShader->UploadUniformMat4("mProjection", matProjection);
					glm::mat4 viewProjection = matProjection * matView;
					//openGLShader->UploadUniformMat4("u_ViewProjection", viewProjection);
					RenderCommand::SetCullFace();
					RenderCommand::EnableDepth();

					openGLShader->UploadUniformFloat("bIsFlameObject", 0);
					openGLShader->UploadUniformFloat("bUseDiscardTexture", 0);

					Transform entityTransform = entity->transform;

					glm::mat4 matTranslation = glm::translate(glm::mat4(1.0f),
						entityTransform.Position);
					glm::mat4 matQRotation = glm::mat4(entityTransform.Rotation);
					glm::mat4 matScale = glm::scale(glm::mat4(1.0f),
						entityTransform.Scale);

					matModel = matModel * matTranslation;
					matModel = matModel * matQRotation;
					matModel = matModel * matScale;

					openGLShader->UploadUniformMat4("mModel", matModel);
					// Inverse transpose of a 4x4 matrix removes the right column and lower row
					// Leaving only the rotation (the upper left 3x3 matrix values)
					glm::mat4 mModelInverseTransform = glm::inverse(glm::transpose(matModel));
					openGLShader->UploadUniformMat4("mModelInverseTranspose", mModelInverseTransform);

					RenderCommand::SetPolygonMode(!meshRenderer->material->bWireframe);

					if(meshRenderer->material->bUseRGBA)
						openGLShader->UploadUniformFloat("bUseRGBA_Colour", 1);
					else openGLShader->UploadUniformFloat("bUseRGBA_Colour", 0);

					openGLShader->UploadUniformFloat4("RGBA_Colour", meshRenderer->material->RGBA);
					openGLShader->UploadUniformFloat4("specularColour", meshRenderer->material->SPEC);

					if(meshRenderer->material->bUseLight)
						openGLShader->UploadUniformFloat("bDoNotLight", 0);
					else openGLShader->UploadUniformFloat("bDoNotLight", 1);


					sModelDrawInfo drawInfo;
					m_VertexArray->FindDrawInfoByModelName(meshRenderer->Mesh, drawInfo);
					
					
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
		void Renderer::ProcessMouseMovement(float xoffset, float yoffset)
		{
			xoffset *= SENSITIVITY;
			yoffset *= SENSITIVITY;

			YAW += xoffset;
			PITCH += yoffset;

			// make sure that when pitch is out of bounds, screen doesn't get flipped
			if (PITCH > 89.9f)
				PITCH = 89.9f;
			if (PITCH < -89.9f)
				PITCH = -89.9f;

			glm::vec3 direction;
			direction.x = cos(glm::radians(YAW)) * cos(glm::radians(PITCH));
			direction.y = sin(glm::radians(PITCH));
			direction.z = sin(glm::radians(YAW)) * cos(glm::radians(PITCH));
			cameraFront = glm::normalize(direction);
			cameraRight = glm::normalize(glm::cross(cameraFront, WorldUp));
			cameraUp = glm::normalize(glm::cross(cameraRight, cameraFront));
		}
		void Renderer::Init(std::vector<Entity*>* entityList, std::string& vertexSourceFile, std::string& fragmentSourcFile)
		{
			EDITOR_CAMERA->transform.Position = glm::vec3(5, 0, 0);
			cameraRight = glm::normalize(glm::cross(cameraFront, WorldUp));
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