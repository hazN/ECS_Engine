#include "Application.h"
#include <Events/MouseEvent.h>
#include "Input.h"
#include <GLFW/glfw3.h>
#include <iostream>

namespace sas {

	Application* Application::s_Instance = nullptr;

	Application::Application()
	{
		/*if (s_Instance)
		{
			std::cout << "Application already exists!" << std::endl;
			return;
		}*/

		s_Instance = this;
		m_Window = std::unique_ptr<Window>(Window::Create());
		m_Window->SetEventCallback(VEL_BIND_EVENT_FN(Application::OnEvent));
		//m_Window->SetVSync(false);
	}

	Application::~Application()
	{
	}

	void Application::OnEvent(Event& e)
	{
		EventDispatcher dispatcher(e);
		std::cout << e << std::endl;
		dispatcher.Dispatch<WindowCloseEvent>(VEL_BIND_EVENT_FN(Application::OnWindowClosed));
	}

	void Application::Run()
	{
		while (m_Running)
		{
			float time = (float)glfwGetTime();
			Timestep timestep = time - m_LastFrameTime;
			m_LastFrameTime = time;

			

			m_Window->OnUpdate();
		}
	}

	bool Application::OnWindowClosed(WindowCloseEvent& e)
	{
		m_Running = false;
		return true;
	}

}
