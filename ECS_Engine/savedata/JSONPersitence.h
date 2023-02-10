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

	std::string MeshName;
	glm::vec4 RGBA;
	glm::vec4 SPEC;
	bool bWireframe;
	bool bUseRGBA;
	bool bUseLight;
	bool bVisible;

	std::string Textures[8];
	float TextureRatios[8];
};
struct cLight{


};

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