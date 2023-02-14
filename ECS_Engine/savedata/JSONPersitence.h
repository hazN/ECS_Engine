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
static std::string SAVE_LOCATION = "./savedata/entityData.json";
namespace sas {
	// Persistence namespace to isolate all save/load functions
	namespace persistence
	{
		// Saves all the entities provided to the SAVE_LOCATION
		void SaveEntities(std::vector<Entity*> entitiesToSave);
		// Loads all entities to the provided vector from the SAVE_LOCATION
		void LoadEntities(std::vector<Entity*>& entitiesToLoad);
		// Loads Material from given path
		void LoadMaterial(Material* materialToLoad, std::string path);
	}
}