#include "VertexArray.h"
#include "RendererAPI.h"
#include <iostream>
#include <OpenGL/OpenGLVertexArray.h>

namespace sas
{

	sModelDrawInfo::sModelDrawInfo()
	{
		this->VAO_ID = 0;
		this->VertexBufferID = 0;
		this->numberOfVertices = 0;
		this->IndexBufferID = 0;
		this->IndexBuffer_Start_Index = 0;
		this->numberOfIndices = 0;
		this->numberOfTriangles = 0;

		this->pVertices = 0;
		this->pIndices = 0;

		return;
	}

	std::shared_ptr<VertexArray> VertexArray::Create()
	{
		switch (RendererAPI::GetAPI())
		{
		case RendererAPI::API::None:
			std::cout << "Renderer API None is not supported" << std::endl;
			return nullptr;

		case RendererAPI::API::OpenGL: return std::make_shared<OpenGLVertexArray>();
		}
		std::cout << "Unknown Renderer API" << std::endl;

		return nullptr;
	}
}