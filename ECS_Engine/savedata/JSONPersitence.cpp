#include "JSONPersitence.h"

namespace sas {
	namespace persistence
	{
		void SaveAll(std::vector<cMeshObject*> modelsToSave, std::vector<cLight*> lightsToSave)
		{
			SaveModels(modelsToSave);
			// TBA SaveLights(lightsToSave);
		}

		void LoadAll(std::vector<cMeshObject*>& modelsToLoad, std::vector<cLight*>& lightsToLoad)
		{
			LoadModels(modelsToLoad);
			// TBA LoadLights(lightsToLoad);
		}

		// Saves vector of cMeshObject pointers to JSON
		void SaveModels(std::vector<cMeshObject*> modelsToSave)
		{
			std::ofstream saveFile;
			saveFile.open("./savedata/modelData.json");
			json models;
			for (cMeshObject* model : modelsToSave)
			{
				json m = json{ {"id", model->id}, {"meshName", model->meshName}, {"friendlyName", model->friendlyName},
					{"position", json::array({model->position.x,model->position.y,model->position.z})},
					{"qRotation", json::array({model->qRotation.w, model->qRotation.x, model->qRotation.y, model->qRotation.z})},
					{"scaleXYZ", json::array({model->scaleXYZ.x,model->scaleXYZ.y, model->scaleXYZ.z})},
					{"isWireframe", model->isWireframe},{"bUse_RGBA_colour", model->bUse_RGBA_colour},
					{"RGBA_colour", json::array({model->RGBA_colour.x, model->RGBA_colour.y, model->RGBA_colour.z, model->RGBA_colour.w})},
					{"specular_colour_and_power", json::array({model->specular_colour_and_power.x, model->specular_colour_and_power.y, model->specular_colour_and_power.z, model->specular_colour_and_power.w})},
					{"bDoNotLight", model->bDoNotLight}, {"bIsVisible", model->bIsVisible},
					{"textures", json::array({model->textures[0],model->textures[1], model->textures[2], model->textures[3], model->textures[4],
					model->textures[5], model->textures[6], model->textures[7]})},
						{"textureRatios", json::array({model->textureRatios[0], model->textureRatios[1], model->textureRatios[2], model->textureRatios[3], model->textureRatios[4],
						model->textureRatios[5], model->textureRatios[6], model->textureRatios[7]})}
				};
				models.push_back(json{ { model->friendlyName, m } });
			}
			saveFile << models;
			saveFile.close();
		}

		void SaveLights(std::vector<cLight*> lightsToSave)
		{
		}

		// Loads data from modelData file into provided cMeshObject pointer vector
		void LoadModels(std::vector<cMeshObject*>& modelsToLoad)
		{
			std::ifstream file("./savedata/modelData.json", std::ifstream::in);
			json f;

			// Handle any exceptions
			try
			{
				file >> f;
			}
			catch (json::exception& e)
			{
				std::cout << e.what() << std::endl;
			}
			if (f == nlohmann::detail::value_t::null)
			{
				std::cout << "Error loading modelData.json, save file may be corrupted." << std::endl;
				return;
			}
			for (json header : f)
			{

				for (json m : header)
				{
					cMeshObject* model = new cMeshObject();
					model->id = m.at("id");
					model->meshName = m.at("meshName");
					model->friendlyName = m.at("friendlyName");
					model->position.x = m.at("position")[0];
					model->position.y = m.at("position")[1];
					model->position.z = m.at("position")[2];
					model->qRotation.w = m.at("qRotation")[0];
					model->qRotation.x = m.at("qRotation")[1];
					model->qRotation.y = m.at("qRotation")[2];
					model->qRotation.z = m.at("qRotation")[3];
					model->scaleXYZ.x = m.at("scaleXYZ")[0];
					model->scaleXYZ.y = m.at("scaleXYZ")[1];
					model->scaleXYZ.z = m.at("scaleXYZ")[2];
					model->isWireframe = m.at("isWireframe");
					model->bUse_RGBA_colour = m.at("bUse_RGBA_colour");
					model->RGBA_colour.x = m.at("RGBA_colour")[0];
					model->RGBA_colour.y = m.at("RGBA_colour")[1];
					model->RGBA_colour.z = m.at("RGBA_colour")[2];
					model->RGBA_colour.w = m.at("RGBA_colour")[3];
					model->specular_colour_and_power.x = m.at("specular_colour_and_power")[0];
					model->specular_colour_and_power.y = m.at("specular_colour_and_power")[1];
					model->specular_colour_and_power.z = m.at("specular_colour_and_power")[2];
					model->specular_colour_and_power.w = m.at("specular_colour_and_power")[3];
					model->bDoNotLight = m.at("bDoNotLight");
					model->bIsVisible = m.at("bIsVisible");
					model->textures[0] = m.at("textures")[0];
					model->textures[1] = m.at("textures")[1];
					model->textures[2] = m.at("textures")[2];
					model->textures[3] = m.at("textures")[3];
					model->textures[4] = m.at("textures")[4];
					model->textures[5] = m.at("textures")[5];
					model->textures[6] = m.at("textures")[6];
					model->textures[7] = m.at("textures")[7];
					model->textureRatios[0] = m.at("textureRatios")[0];
					model->textureRatios[1] = m.at("textureRatios")[1];
					model->textureRatios[2] = m.at("textureRatios")[2];
					model->textureRatios[3] = m.at("textureRatios")[3];
					model->textureRatios[4] = m.at("textureRatios")[4];
					model->textureRatios[5] = m.at("textureRatios")[5];
					model->textureRatios[6] = m.at("textureRatios")[6];
					model->textureRatios[7] = m.at("textureRatios")[7];
					// Check if it already exists in the system and replace if it does
					// If it doesn't then add it to the vector
					bool replaced = false;
					for (int i = 0; i < modelsToLoad.size(); i++)
					{
						if (modelsToLoad[i]->friendlyName == model->friendlyName)
						{
							modelsToLoad[i] = model;
							replaced = true;
						}
					}
					if (!replaced)
						modelsToLoad.push_back(model);
				}
			}
			file.close();
		}

		void LoadLights(std::vector<cLight*>& lightsToLoad)
		{
		}
	}
}