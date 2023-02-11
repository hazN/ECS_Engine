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

namespace sas {
	namespace persistence
	{
		void SaveGameObjects(std::vector<Entity*> gameObjectsToSave);
		void LoadGameObjects(std::vector<Entity*>& gameObjectsToLoad);
	}
}