#pragma once
#include <glm/fwd.hpp>

namespace sas
{
	class RendererAPI
	{
	public:

		enum class API
		{
			None = 0,
			OpenGL = 1, 
			Direct3D = 2,
		};

	public:
		virtual void SetClearColor(const glm::vec4& color) = 0;
		virtual void Clear() = 0;

		virtual void DrawIndexed(const uint32_t& vaID, unsigned int numberOfIndices) = 0;

		virtual void SetViewport(int x, int y, int width, int height) = 0;

		virtual void SetCullFace() = 0;

		virtual void EnableDepth() = 0;

		virtual void SetDepthMask(bool) = 0;

		virtual void SetPolygonMode(bool) = 0;
		inline static API GetAPI() { return s_API; }

	private:
		static API s_API;
	};
}