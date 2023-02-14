#pragma once
#include <vector>
#include "../Entity.h"
#include "../System.h"
#include "../core/Renderer/VertexArray.h"
#include <string>
#include <memory>
#include <Renderer/Shader.h>

namespace sas
{
	namespace Systems
	{
		// System to render meshes
		class Renderer : public System
		{
		public:
			Renderer();
			~Renderer();

			// Render all the entities which has a meshrenderer component
			virtual void Process(const std::vector < Entity* >* entityList, float dt) override;

			// Create Vertex Array IDs for all the entity with mesh renderer
			void Init(std::vector<Entity*>* entityList, std::string& vertexSourceFile, std::string& fragmentSourcFile);
		private:
			// Compile the given shader
			void CompileShaders(std::string& vertexSourceFile, std::string& fragmentSourcFile);
			std::shared_ptr<Shader> m_Shader;
			std::shared_ptr<VertexArray> m_VertexArray;

			// Temporary

			static Entity* EDITOR_CAMERA;
			bool mouseHoldDown = false;
			bool mouseClicked = false; 
			glm::vec3 cameraFront = glm::vec3(0.0f, 0.0f, 1.0f);
			glm::vec3 cameraUp = glm::vec3(0.0f, 1.0f, 0.0f);
			glm::vec3 WorldUp = glm::vec3(0.0f, 1.0f, 0.0f);
			glm::vec3 cameraRight = glm::vec3(0.0f, 0.0f, 0.0f);

			// Process mouse movement
			void ProcessMouseMovement(float xoffset, float yoffset);

			int SCR_WIDTH = 1200;
			int SCR_HEIGHT = 800;
			float lastX = SCR_WIDTH / 2.0f;
			float lastY = SCR_HEIGHT / 2.0f;
			bool firstMouse = true;

			float YAW = 90.0f;
			float PITCH = 0.0f;
			float SENSITIVITY = 0.1f;
			float xpos;
			float ypos;
		};
	}
}