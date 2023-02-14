#pragma once
#include "RendererAPI.h"
#include "VertexArray.h"

namespace sas
{
	// Static render commands needed to render meshes
	// It internally calls the renderer api which further calls
	// the platform specifi API
	class RenderCommand
	{
	public:
		// Set Clear Color for the window
		inline static void SetClearColor(const glm::vec4& color)
		{
			s_RendererAPI->SetClearColor(color);
		}

		// Clear buffers
		inline static void Clear()
		{
			s_RendererAPI->Clear();
		}

		// Draw mesh using index pointer
		inline static void DrawIndexed(const sModelDrawInfo& drawInfo)
		{
			s_RendererAPI->DrawIndexed(drawInfo);
		}

		// Set viewport's size
		inline static void SetViewport(int x, int y, int width, int height)
		{
			s_RendererAPI->SetViewport(x, y, width, height);
		}

		// Set culling mode
		inline static void SetCullFace()
		{
			s_RendererAPI->SetCullFace();
		}

		// Enable depth calculation
		inline static void EnableDepth()
		{
			s_RendererAPI->EnableDepth();
		}

		// Enable or disable depth mask
		inline static void SetDepthMask(bool enable)
		{
			s_RendererAPI->SetDepthMask(enable);
		}

		// Set Polygon mode
		// Wireframe or Filled
		inline static void SetPolygonMode(bool isFilled)
		{
			s_RendererAPI->SetPolygonMode(isFilled);
		}
	private:
		static RendererAPI* s_RendererAPI;
	};
}