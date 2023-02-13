#include "OpenGLRendererAPI.h"
#include <glad/glad.h>
#include <glm/glm.hpp>
#include <string>
#include <iostream>

namespace sas
{
	OpenGLRendererAPI::OpenGLRendererAPI()
	{
	}
	void OpenGLRendererAPI::SetClearColor(const glm::vec4& color)
	{
		glClearColor(color.r, color.g, color.b, color.a);
	}

	void OpenGLRendererAPI::Clear()
	{
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	}

	GLenum glCheckError_()
	{
		GLenum errorCode;
		while ((errorCode = glGetError()) != GL_NO_ERROR)
		{
			std::string error;
			switch (errorCode)
			{
			case GL_INVALID_ENUM:                  error = "INVALID_ENUM"; break;
			case GL_INVALID_VALUE:                 error = "INVALID_VALUE"; break;
			case GL_INVALID_OPERATION:             error = "INVALID_OPERATION"; break;
			case GL_STACK_OVERFLOW:                error = "STACK_OVERFLOW"; break;
			case GL_STACK_UNDERFLOW:               error = "STACK_UNDERFLOW"; break;
			case GL_OUT_OF_MEMORY:                 error = "OUT_OF_MEMORY"; break;
			case GL_INVALID_FRAMEBUFFER_OPERATION: error = "INVALID_FRAMEBUFFER_OPERATION"; break;
			}
			//std::cout << error << std::endl;
		}
		return errorCode;
	}

	void OpenGLRendererAPI::DrawIndexed(const sModelDrawInfo& drawInfo)
	{
		glBindVertexArray(drawInfo.VAO_ID);
		glDrawElements(GL_TRIANGLES, drawInfo.numberOfIndices, GL_UNSIGNED_INT, nullptr);

		GLenum error = glCheckError_();

		if (error != GL_NO_ERROR)
		{

			std::cout <<  "OpenGL error!!" << std::endl;
		}
		glBindVertexArray(0);
	}

	void OpenGLRendererAPI::SetViewport(int x, int y, int width, int height)
	{
		glViewport(x, y, width, height);
	}

	void OpenGLRendererAPI::SetCullFace()
	{
		glCullFace(GL_BACK);
		glEnable(GL_CULL_FACE);
	}

	void OpenGLRendererAPI::EnableDepth()
	{
		glEnable(GL_DEPTH_TEST);
	}

	void OpenGLRendererAPI::SetDepthMask(bool enable)
	{
		if (enable)
			glDepthMask(GL_TRUE);
		else glDepthMask(GL_FALSE);
	}

	void OpenGLRendererAPI::SetPolygonMode(bool isFilled)
	{
		if (isFilled)
			glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
		else
			glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	}

}