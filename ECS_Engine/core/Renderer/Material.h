#pragma once
#include <string>
#include <glm/glm.hpp>
#include <glm/gtx/quaternion.hpp>

struct Material
{
	glm::vec4 RGBA;
	glm::vec4 SPEC;
	bool bWireframe;
	bool bUseRGBA;
	bool bUseLight;
	bool bVisible;

	std::string Textures[8];
	float TextureRatios[8];
};