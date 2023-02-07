#pragma once
#include "Core.h"

#include "Events/Event.h"
#include "Timestep.h"
#include <memory>

#include "Window.h"
#include <Events/ApplicationEvent.h>


namespace sas {
	class Application
	{
	public:
		Application();
		virtual ~Application();
		void Run();

		void OnEvent(Event& e);

		inline Window& GetWindow() { return *m_Window; }
		inline static Application& Get() { return *s_Instance; }
	private:
		bool OnWindowClosed(WindowCloseEvent& e);
	private:

		std::unique_ptr<Window> m_Window;
		bool m_Running = true;

		float m_LastFrameTime = 0.f;


	private:
		static Application* s_Instance;
	};

}
