#pragma once
#include <nlohmann/json.hpp>
//#include "cLight.h"
//#include "cMeshObject.h"
#include <fstream>
#include <iostream>
#include <istream>
#include <sstream>
#include <glm/glm.hpp>
#include <glm/gtx/quaternion.hpp>
using json = nlohmann::json;

// TEMPORARY STRUCT TO STOP ERROR TEXT
struct cMeshObject
{
	int id;
	std::string meshName;
	std::string friendlyName;
	glm::vec3 position;
	glm::quat qRotation;
	glm::vec3 scaleXYZ;
	bool isWireframe;
	glm::vec4 RGBA_colour;
	bool bUse_RGBA_colour;
	glm::vec4 specular_colour_and_power;
	bool bDoNotLight;
	bool bIsVisible;
	std::string textures[8];
	float textureRatios[8];
};
struct cLight{};

namespace sas {
	namespace persistence
	{
		void SaveAll(std::vector<cMeshObject*> modelsToSave, std::vector<cLight*> lightsToSave);
		void LoadAll(std::vector<cMeshObject*>& modelsToSave, std::vector<cLight*>& lightsToSave);
		void SaveModels(std::vector<cMeshObject*> modelsToSave);
		void SaveLights(std::vector<cLight*> lightsToSave);
		void LoadModels(std::vector<cMeshObject*>& modelsToLoad);
		void LoadLights(std::vector<cLight*>& lightsToLoad);
	}
}