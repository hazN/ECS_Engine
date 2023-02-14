#pragma once
#include "KeyCodes.h"
#include <utility>

namespace sas
{
	// Main Input class
	class Input
	{
	public:
		// If the key was Pressed
		inline static bool IsKeyPressed(KeyCode keycode) { return s_Instance->IsKeyPressedImpl(keycode); }
		
		// If the mouse button was Pressed
		inline static bool IsMouseButtonPressed(MouseButton button) { return s_Instance->IsMouseButtonPressedImpl(button); }
		
		// Get mouse position on the screen
		inline static std::pair<float, float> GetMousePosition() { return s_Instance->GetMousePositionImpl(); }
		
		// Get x position of the mouse on the screen
		inline static float GetMouseX() { return s_Instance->GetMouseXImpl(); }
		
		// Get y position of the mouse on the screen
		inline static float GetMouseY() { return s_Instance->GetMouseYImpl(); }

	protected:
		// Platform specific implementations:

		virtual bool IsKeyPressedImpl(KeyCode keycode) = 0;
		virtual bool IsMouseButtonPressedImpl(MouseButton button) = 0;
		virtual std::pair<float, float> GetMousePositionImpl() = 0;
		virtual float GetMouseXImpl() = 0;
		virtual float GetMouseYImpl() = 0;

	private:
		/// <summary>
		/// Singleton instance
		/// </summary>
		static Input* s_Instance;
	};
}