#pragma once
#include <string>
#include <glm/glm.hpp>
#include <glm/gtx/quaternion.hpp>

// Material for mesh renderer
// Holds all the values needed to modify the appearance of the mesh
struct Material
{
	glm::vec4 RGBA = glm::vec4(0.8f, 0.1f, 0.8f, 1.f);
	glm::vec4 SPEC = glm::vec4(0.8f, 0.1f, 0.8f, 1.f);
	bool bWireframe = false;
	bool bUseRGBA = true;
	bool bUseLight = false;
	bool bVisible = true;

	std::string Textures[8];
	float TextureRatios[8];
};