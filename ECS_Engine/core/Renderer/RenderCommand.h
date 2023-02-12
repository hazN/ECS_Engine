#pragma once
#include "RendererAPI.h"
#include "VertexArray.h"

namespace sas
{
	class RenderCommand
	{
	public:
		inline static void SetClearColor(const glm::vec4& color)
		{
			s_RendererAPI->SetClearColor(color);
		}
		inline static void Clear()
		{
			s_RendererAPI->Clear();
		}
		inline static void DrawIndexed(const sModelDrawInfo& drawInfo)
		{
			s_RendererAPI->DrawIndexed(drawInfo);
		}
		inline static void SetViewport(int x, int y, int width, int height)
		{
			s_RendererAPI->SetViewport(x, y, width, height);
		}

		inline static void SetCullFace()
		{
			s_RendererAPI->SetCullFace();
		}

		inline static void EnableDepth()
		{
			s_RendererAPI->EnableDepth();
		}

		inline static void SetDepthMask(bool enable)
		{
			s_RendererAPI->SetDepthMask(enable);
		}

		inline static void SetPolygonMode(bool isFilled)
		{
			s_RendererAPI->SetPolygonMode(isFilled);
		}
	private:
		static RendererAPI* s_RendererAPI;
	};
}