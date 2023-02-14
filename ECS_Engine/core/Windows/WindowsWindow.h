#pragma once

#include "Window.h"
#include "Renderer/GraphicsContext.h"
#include <GLFW/glfw3.h>

namespace sas
{
	// Windows specific window
	class WindowsWindow : public Window
	{
	public:
		// Create windows window using props
		WindowsWindow(const WindowProps& props);
		virtual ~WindowsWindow();

		// Frame update
		void OnUpdate() override;

		// Get windows Width
		inline unsigned int GetWidth() const override { return m_Data.Width; }

		// Get windows height
		inline unsigned int GetHeight() const override { return m_Data.Height; }

		// Set event callback
		inline void SetEventCallback(const EventCallbackFn& callback) override { m_Data.EventCallback = callback; }
		
		// Set vsync enable or disable
		void SetVSync(bool enabled) override;

		// If windows is using vsync
		bool IsVSync() const override;

		// Get platform specific window
		inline virtual void* GetNativeWindow() const override { return m_Window; }

	private:

		// Initialize using props
		virtual void Init(const WindowProps& props);

		// Shutdown window
		virtual void Shutdown();

	private:
		GLFWwindow* m_Window;
		GraphicsContext* m_Context;

		struct WindowData
		{
			std::string Title;
			unsigned int Width, Height;
			bool VSync;

			EventCallbackFn EventCallback;
		};

		WindowData m_Data;
	};
}

