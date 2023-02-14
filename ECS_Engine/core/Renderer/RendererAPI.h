#pragma once
#include <glm/fwd.hpp>
#include "VertexArray.h"

namespace sas
{
	// Renderer API
	class RendererAPI
	{
	public:
		// Types of API to be supported
		enum class API
		{
			None = 0,
			OpenGL = 1, 
			Direct3D = 2,
		};

	public:
		// Set Clear Color for the window
		virtual void SetClearColor(const glm::vec4& color) = 0;
		
		// Clear buffers
		virtual void Clear() = 0;

		// Draw mesh using index pointer
		virtual void DrawIndexed(const sModelDrawInfo& drawInfo) = 0;

		// Set viewport's size
		virtual void SetViewport(int x, int y, int width, int height) = 0;

		// Set culling mode
		virtual void SetCullFace() = 0;

		// Enable depth calculation
		virtual void EnableDepth() = 0;

		// Enable or disable depth mask
		virtual void SetDepthMask(bool) = 0;

		// Set Polygon mode
		// Wireframe or Filled
		virtual void SetPolygonMode(bool) = 0;

		// Get current working API
		inline static API GetAPI() { return s_API; }

	private:
		static API s_API;
	};
}