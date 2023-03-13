#pragma once
#include "Core.h"

#include "Events/Event.h"
#include "Timestep.h"
#include <memory>

#include "Window.h"
#include <Events/ApplicationEvent.h>
#include "../ECS/systems/Renderer.h"
#include "../ECS/systems/Movement.h"
#include "../ECS/Physic/Physic.h"
#include "../ECS/components/AgentController.h"

namespace sas {

	// Main Application
	class Application
	{
	public:
		Application();
		virtual ~Application();

		// Game Loop
		void Run();

		// Event observer
		void OnEvent(Event& e);

		// Get Window
		inline Window& GetWindow() { return *m_Window; }

		// Get singleton instance
		inline static Application& Get() { return *s_Instance; }
	private:

		// When a window is closed
		bool OnWindowClosed(WindowCloseEvent& e);
	private:

		std::unique_ptr<Window> m_Window;
		Systems::Renderer m_Renderer;
		std::vector<Entity*>* m_Entities;
		bool m_Running = true;

		// temporary control script
		Systems::Movement m_MovmentScript;

		float m_LastFrameTime = 0.f;

		//physic factory
		
		Physic::Physic* m_Physic;

		AgentController* agentController;

		Entity* Player;

	private:
		static Application* s_Instance;
	};

}
