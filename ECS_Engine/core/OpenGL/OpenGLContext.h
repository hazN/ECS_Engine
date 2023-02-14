#pragma once

#include "Renderer/GraphicsContext.h"
struct GLFWwindow;

namespace sas
{
	// OpenGL context
	// Links glfw and glad
	class OpenGLContext : public GraphicsContext
	{
	public:
		OpenGLContext(GLFWwindow* windowHandle);

		// Initialize the context
		virtual void Init() override;

		// Swap buffers
		virtual void SwapBuffers() override;
	private:
		GLFWwindow* m_WindowHandle;
	};
}
