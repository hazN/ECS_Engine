#pragma once
#include "../Renderer/RendererAPI.h"

namespace sas
{
	// OpenGL specific render calls
	class OpenGLRendererAPI : public RendererAPI
	{
	public:
		// OpenGL renderer API
		OpenGLRendererAPI();

		// Set Clear Color for the window
		virtual void SetClearColor(const glm::vec4& color) override;
		
		// Clear buffers
		virtual void Clear() override;

		// Draw mesh using index pointer
		virtual void DrawIndexed(const sModelDrawInfo& drawInfo) override;
		
		// Set viewport's size
		virtual void SetViewport(int x, int y, int width, int height) override;

		// Set culling mode
		virtual void SetCullFace() override;

		// Enable depth calculation
		virtual void EnableDepth() override;

		// Enable or disable depth mask
		virtual void SetDepthMask(bool) override;

		// Set Polygon mode
		// Wireframe or Filled
		virtual void SetPolygonMode(bool) override;
	};
}