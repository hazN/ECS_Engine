#include "OpenGLContext.h"
#include <GLFW/glfw3.h>
#include <glad/glad.h>
#include <iostream>
#include <sstream>

namespace sas
{
	OpenGLContext::OpenGLContext(GLFWwindow* windowHandle)
		:m_WindowHandle(windowHandle)
	{
		if(!windowHandle)
			std::cout << "Window handle is null!" << std::endl;
	}
	void OpenGLContext::Init()
	{
		glfwMakeContextCurrent(m_WindowHandle);
		int status = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
		if(!status)
			std::cout << "Failed to initiaize glad!" << std::endl;
		std::stringstream ssvendor, ssrenderer, ssversion;
		std::string vendor, renderer, version;

		ssvendor << glGetString(GL_VENDOR);
		vendor = ssvendor.str();

		ssrenderer << glGetString(GL_RENDERER);
		renderer = ssrenderer.str();

		ssversion << glGetString(GL_VERSION);
		version = ssversion.str();

		std::cout << "OpenGLInfo: " << std::endl;
		std::cout << "  Vendor: " << vendor << std::endl;
		std::cout << "  Renderer: " << renderer << std::endl;
		std::cout << "  Version: " << version << std::endl;

	}
	void OpenGLContext::SwapBuffers()
	{
		glfwSwapBuffers(m_WindowHandle);
	}
}
