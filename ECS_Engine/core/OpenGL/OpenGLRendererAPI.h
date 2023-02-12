#pragma once
#include "../Renderer/RendererAPI.h"

namespace sas
{
	class OpenGLRendererAPI : public RendererAPI
	{
	public:
		OpenGLRendererAPI();
		virtual void SetClearColor(const glm::vec4& color) override;
		virtual void Clear() override;

		virtual void DrawIndexed(const uint32_t& vaID, unsigned int numberOfIndices) override;
		virtual void SetViewport(int x, int y, int width, int height) override;

		virtual void SetCullFace() override;

		virtual void EnableDepth() override;

		virtual void SetDepthMask(bool) override;

		virtual void SetPolygonMode(bool) override;
	};
}