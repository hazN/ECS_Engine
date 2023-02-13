#include "Application.h"
#include <Events/MouseEvent.h>
#include "Input.h"
#include <GLFW/glfw3.h>
#include <iostream>
#include <Events/KeyEvent.h>

namespace sas {

	Application* Application::s_Instance = nullptr;

	Application::Application()
	{
		if (s_Instance)
		{
			std::cout << "Application already exists!" << std::endl;
			return;
		}
		
		s_Instance = this;
		m_Window = std::unique_ptr<Window>(Window::Create());
		m_Window->SetEventCallback(VEL_BIND_EVENT_FN(Application::OnEvent));

		entities = new std::vector<Entity*>();
		{
			Entity* entity = new Entity();
			entity->transform.Position = glm::vec3(0.f, 0.f, -1.f);
			Material* material = new Material();
			MeshRenderer* meshRenderer = new MeshRenderer();
			material->RGBA = glm::vec4(0.1f, 0.1f, 0.8f, 1.f);
			meshRenderer->material = material;
			material->bUseLight = false;
			meshRenderer->Path = "assets/models/cube.ply";
			meshRenderer->Mesh = "cube";
			entity->AddComponent(meshRenderer);
			entities->push_back(entity);
		}
		{
			Entity* entity = new Entity();
			entity->transform.Position = glm::vec3(0.f, 0.f, 10.f);
			Material* material = new Material();
			MeshRenderer* meshRenderer = new MeshRenderer();
			material->RGBA = glm::vec4(0.8f, 0.3f, 0.3f, 1.f);
			meshRenderer->material = material;
			material->bUseLight = false;
			meshRenderer->material->bWireframe = false;
			meshRenderer->Path = "assets/models/femaleKnight.ply";
			meshRenderer->Mesh = "femaleKnight";
			entity->AddComponent(meshRenderer);
			entities->push_back(entity);
		}
		{
			Entity* entity = new Entity();
			entity->transform.Position = glm::vec3(0, -0.5f, 0);
			entity->transform.Scale = glm::vec3(10, 2, 10);
			entity->transform.Rotation = glm::rotate(entity->transform.Rotation, glm::vec3(-1.57f, 0.f, 0.f));
			Material* material = new Material();
			MeshRenderer* meshRenderer = new MeshRenderer();
			material->RGBA = glm::vec4(0.3f, 0.7f, 0.3f, 1.f);
			meshRenderer->material = material;
			material->bUseLight = false;
			meshRenderer->Path = "assets/models/plane.ply";
			meshRenderer->Mesh = "plane";
			entity->AddComponent(meshRenderer);
			entities->push_back(entity);
		}
		std::string vertex = "assets/shaders/vertexShader03.glsl";
		std::string fragment = "assets/shaders/fragmentShader03.glsl";
		m_Renderer.Init(entities, vertex, fragment);
		//m_Window->SetVSync(false);
	}

	Application::~Application()
	{
	}

	void Application::OnEvent(Event& e)
	{
		EventDispatcher dispatcher(e);
		//std::cout << e << std::endl;
		if (dispatcher.Dispatch<WindowCloseEvent>(VEL_BIND_EVENT_FN(Application::OnWindowClosed)))
		{
			std::cout << "Window Closed called!!";
		}
	}

	void Application::Run()
	{
		while (m_Running)
		{
			float time = (float)glfwGetTime();
			Timestep timestep = time - m_LastFrameTime;
			m_LastFrameTime = time;
			m_Renderer.Process(entities, timestep);
			if (Input::IsKeyPressed(KeyCode::Escape))
			{
				m_Running = false;
			}

			m_Window->OnUpdate();
		}
	}

	bool Application::OnWindowClosed(WindowCloseEvent& e)
	{
		m_Running = false;
		return true;
	}

}
