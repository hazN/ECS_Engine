#pragma once
#include <string>
#include <glm/glm.hpp>
#include <glm/gtx/quaternion.hpp>

namespace sas
{
	class MeshRenderer
	{
	public:
		bool Enabled;

		std::string Mesh;
		std::string Path;
		glm::vec4 RGBA;
		glm::vec4 SPEC;
		bool bWireframe;
		bool bUseRGBA;
		bool bUseLight;
		bool bVisible;

		std::string Textures[8];
		float TextureRatios[8];
	};
}