#pragma once

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
		inline static API GetAPI() { return s_API; }

	private:
		static API s_API;
	};
}