#include "Shader.h"
#include "RendererAPI.h"
#include <iostream>
#include "../OpenGL/OpenGLShader.h"

namespace sas
{
	Shader* Shader::Create(const std::string& vertexShaderFile, const std::string& fragmentShaderFile)
	{
		switch (RendererAPI::GetAPI())
		{
		case RendererAPI::API::None:
			std::cout << "Renderer API None is not supported" << std::endl;
			return nullptr;

		case RendererAPI::API::OpenGL: return new OpenGLShader(vertexShaderFile, fragmentShaderFile);
		}
		std::cout << "Unknown Renderer API" << std::endl;
		return nullptr;
	}
}