#pragma once
#include <string>
#include <functional>
#include "Core.h"
#include "Events/Event.h"

namespace sas
{
	// Data to make a window
	struct WindowProps
	{
		std::string Title;
		unsigned int Width;
		unsigned int Height;

		WindowProps(const std::string& title = "SaS Engine",
			unsigned int width = 1280,
			unsigned int height = 720)
			: Title(title), Width(width), Height(height)
		{}
	};

	class Window
	{
	public:
		using EventCallbackFn = std::function<void(Event&)>;
		virtual ~Window() {}

		// Frame update
		virtual void OnUpdate() = 0;
		
		// Get windows Width
		virtual unsigned int GetWidth() const = 0;

		// Get windows Height
		virtual unsigned int GetHeight() const = 0;

		// Set event callback
		virtual void SetEventCallback(const EventCallbackFn& callback) = 0;
		// Set vsync enable or disable
		virtual void SetVSync(bool enabled) = 0;
		// If windows is using vsync
		virtual bool IsVSync() const = 0;

		// Get platform specific window
		virtual void* GetNativeWindow() const = 0;

		// Create Platform specific window
		static Window* Create(const WindowProps& props = WindowProps());
	};
}