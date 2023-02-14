#pragma once
#include <glm/glm.hpp>
#include <glm/gtx/quaternion.hpp>
namespace sas
{
	// Types of light
	enum LightType { Point, Spot, Directional };
	
	// Light component
	class Light : public Component
	{
	public:
		bool Enabled;
		LightType LightType;

		glm::vec4 Diffuse;
		glm::vec4 Specular;
		glm::vec4 Attenuation;
		float OuterAngle;
		float InnerAngle;
	};
}