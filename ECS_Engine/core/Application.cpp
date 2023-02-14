#include "Application.h"
#include <Events/MouseEvent.h>
#include "Input.h"
#include <GLFW/glfw3.h>
#include <iostream>
#include <Events/KeyEvent.h>
#include "../savedata/JSONPersitence.h"
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
		m_Window->SetEventCallback(SAS_BIND_EVENT_FN(Application::OnEvent));

		m_Entities = new std::vector<Entity*>();
		//{
		//	{
		//		Entity* entity = new Entity();
		//		entity->name = "TestCube";
		//		Transform* transform = new Transform();
		//		transform->Position = glm::vec3(0.f, 0.f, -1.f);
		//		entity->AddComponent(transform);
		//		Material* material = new Material();
		//		MeshRenderer* meshRenderer = new MeshRenderer();
		//		material->RGBA = glm::vec4(0.1f, 0.1f, 0.8f, 1.f);
		//		meshRenderer->material = material;
		//		material->bUseLight = false;
		//		meshRenderer->Path = "assets/models/cube.ply";
		//		meshRenderer->MaterialPath = "assets/materials/cubeMaterial.json";
		//		meshRenderer->Mesh = "cube";
		//		entity->AddComponent(meshRenderer);
		//		entities->push_back(entity);
		//	}
		//	{
		//		Entity* entity = new Entity();
		//		entity->name = "FemaleKnight";
		//		Transform* transform = new Transform();
		//		transform->Position = glm::vec3(0.f, 0.f, 10.f);
		//		entity->AddComponent(transform);
		//		Material* material = new Material();
		//		MeshRenderer* meshRenderer = new MeshRenderer();
		//		material->RGBA = glm::vec4(0.8f, 0.3f, 0.3f, 1.f);
		//		meshRenderer->material = material;
		//		meshRenderer->MaterialPath = "assets/materials/femaleKnightMaterial.json";
		//		material->bUseLight = false;
		//		meshRenderer->material->bWireframe = false;
		//		meshRenderer->Path = "assets/models/femaleKnight.ply";
		//		meshRenderer->Mesh = "femaleKnight";
		//		entity->AddComponent(meshRenderer);
		//		entities->push_back(entity);
		//	}
		//	{
		//		Entity* entity = new Entity();
		//		entity->name = "Ground";
		//		Transform* transform = new Transform();
		//		transform->Position = glm::vec3(0, -0.5f, 0);
		//		transform->Scale = glm::vec3(10, 2, 10);
		//		transform->Rotation = glm::rotate(entity->transform.Rotation, glm::vec3(-1.57f, 0.f, 0.f));
		//		entity->AddComponent(transform);
		//		Material* material = new Material();
		//		MeshRenderer* meshRenderer = new MeshRenderer();
		//		meshRenderer->MaterialPath = "assets/materials/groundMaterial.json";
		//		material->RGBA = glm::vec4(0.3f, 0.7f, 0.3f, 1.f);
		//		meshRenderer->material = material;
		//		material->bUseLight = false;
		//		meshRenderer->Path = "assets/models/plane.ply";
		//		meshRenderer->Mesh = "plane";
		//		entity->AddComponent(meshRenderer);
		//		entities->push_back(entity);
		//	}
		//	sas::persistence::SaveGameObjects(*entities);
		//}

		// Loading data straight from the JSON file now
		sas::persistence::LoadEntities(*m_Entities);
		std::string vertex = "assets/shaders/vertexShader03.glsl";
		std::string fragment = "assets/shaders/fragmentShader03.glsl";
		m_Renderer.Init(m_Entities, vertex, fragment);
		m_MovmentScript.Init(m_Entities);
		//m_Window->SetVSync(false);
	}

	Application::~Application()
	{
	}

	void Application::OnEvent(Event& e)
	{
		EventDispatcher dispatcher(e);
		//std::cout << e << std::endl;
		if (dispatcher.Dispatch<WindowCloseEvent>(SAS_BIND_EVENT_FN(Application::OnWindowClosed)))
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
			m_Renderer.Process(m_Entities, timestep);
			m_MovmentScript.Process(m_Entities, timestep);
			if (Input::IsKeyPressed(KeyCode::S) && Input::IsKeyPressed(KeyCode::LeftControl))
			{
				std::cout << "Saving objects" << std::endl;
				sas::persistence::SaveEntities(*m_Entities);
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
