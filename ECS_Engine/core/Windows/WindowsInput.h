#pragma once
#include <Input.h>

namespace sas
{
	// Windows specific input class
	class WindowsInput : public Input
	{
	protected:
		// If key was pressed
		virtual bool IsKeyPressedImpl(KeyCode keycode) override;

		// If mouse button was pressed
		virtual bool IsMouseButtonPressedImpl(MouseButton button) override;

		// Get mouse position in x,y format
		virtual std::pair<float, float> GetMousePositionImpl() override;

		// Get mouse x position
		virtual float GetMouseXImpl() override;

		// Get mouse y position
		virtual float GetMouseYImpl() override;
	};
}
