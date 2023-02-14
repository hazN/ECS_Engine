#pragma once
#include <nlohmann/json.hpp>
#include <fstream>
#include <iostream>
#include <istream>
#include <sstream>
#include <glm/glm.hpp>
#include <glm/gtx/quaternion.hpp>
#include "../ECS/Entity.h"
using json = nlohmann::json;
static std::string SAVE_LOCATION = "./savedata/gameObjectData.json";
namespace sas {
	namespace persistence
	{
		void SaveGameObjects(std::vector<Entity*> gameObjectsToSave);
		void LoadGameObjects(std::vector<Entity*>& gameObjectsToLoad);
		void LoadMaterial(Material* materialToLoad, std::string path);
	}
}