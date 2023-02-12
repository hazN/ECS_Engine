#include "JSONPersitence.h"

namespace sas {
	namespace persistence
	{

		// Loads data from modelData file into provided cMeshObject pointer vector
		//void LoadModels(std::vector<cMeshObject*>& modelsToLoad)
		//{
		//	std::ifstream file("./savedata/modelData.json", std::ifstream::in);
		//	json f;

		//	// Handle any exceptions
		//	try
		//	{
		//		file >> f;
		//	}
		//	catch (json::exception& e)
		//	{
		//		std::cout << e.what() << std::endl;
		//	}
		//	if (f == nlohmann::detail::value_t::null)
		//	{
		//		std::cout << "Error loading modelData.json, save file may be corrupted." << std::endl;
		//		return;
		//	}
		//	for (json header : f)
		//	{

		//		for (json m : header)
		//		{
		//			cMeshObject* model = new cMeshObject();
		//			model->id = m.at("id");
		//			model->meshName = m.at("meshName");
		//			model->friendlyName = m.at("friendlyName");
		//			model->position.x = m.at("position")[0];
		//			model->position.y = m.at("position")[1];
		//			model->position.z = m.at("position")[2];
		//			model->qRotation.w = m.at("qRotation")[0];
		//			model->qRotation.x = m.at("qRotation")[1];
		//			model->qRotation.y = m.at("qRotation")[2];
		//			model->qRotation.z = m.at("qRotation")[3];
		//			model->scaleXYZ.x = m.at("scaleXYZ")[0];
		//			model->scaleXYZ.y = m.at("scaleXYZ")[1];
		//			model->scaleXYZ.z = m.at("scaleXYZ")[2];
		//			model->isWireframe = m.at("isWireframe");
		//			model->bUse_RGBA_colour = m.at("bUse_RGBA_colour");
		//			model->RGBA_colour.x = m.at("RGBA_colour")[0];
		//			model->RGBA_colour.y = m.at("RGBA_colour")[1];
		//			model->RGBA_colour.z = m.at("RGBA_colour")[2];
		//			model->RGBA_colour.w = m.at("RGBA_colour")[3];
		//			model->specular_colour_and_power.x = m.at("specular_colour_and_power")[0];
		//			model->specular_colour_and_power.y = m.at("specular_colour_and_power")[1];
		//			model->specular_colour_and_power.z = m.at("specular_colour_and_power")[2];
		//			model->specular_colour_and_power.w = m.at("specular_colour_and_power")[3];
		//			model->bDoNotLight = m.at("bDoNotLight");
		//			model->bIsVisible = m.at("bIsVisible");
		//			model->textures[0] = m.at("textures")[0];
		//			model->textures[1] = m.at("textures")[1];
		//			model->textures[2] = m.at("textures")[2];
		//			model->textures[3] = m.at("textures")[3];
		//			model->textures[4] = m.at("textures")[4];
		//			model->textures[5] = m.at("textures")[5];
		//			model->textures[6] = m.at("textures")[6];
		//			model->textures[7] = m.at("textures")[7];
		//			model->textureRatios[0] = m.at("textureRatios")[0];
		//			model->textureRatios[1] = m.at("textureRatios")[1];
		//			model->textureRatios[2] = m.at("textureRatios")[2];
		//			model->textureRatios[3] = m.at("textureRatios")[3];
		//			model->textureRatios[4] = m.at("textureRatios")[4];
		//			model->textureRatios[5] = m.at("textureRatios")[5];
		//			model->textureRatios[6] = m.at("textureRatios")[6];
		//			model->textureRatios[7] = m.at("textureRatios")[7];
		//			// Check if it already exists in the system and replace if it does
		//			// If it doesn't then add it to the vector
		//			bool replaced = false;
		//			for (int i = 0; i < modelsToLoad.size(); i++)
		//			{
		//				if (modelsToLoad[i]->friendlyName == model->friendlyName)
		//				{
		//					modelsToLoad[i] = model;
		//					replaced = true;
		//				}
		//			}
		//			if (!replaced)
		//				modelsToLoad.push_back(model);
		//		}
		//	}
		//	file.close();
		//}
		void SaveGameObjects(std::vector<Entity*> gameObjectsToSave)
		{
			//TESTING 
			Entity* gameObject = new Entity;
			gameObject->name = "testObject";
			Light light;
			light.Attenuation = glm::vec4(0.11, 0.54, 0.3, 1);
			light.Diffuse = glm::vec4(0.41, 0.14, 0.5, 1);
			light.Specular = glm::vec4(0.01, 0.04, 0.03, 1);
			light.Enabled = true;
			light.InnerAngle = 10;
			light.OuterAngle = 30;
			gameObject->light = light;
			Transform transform;
			transform.Enabled = true;
			transform.Position = glm::vec3(50, 90, 20);
			transform.Rotation = glm::quat(glm::vec3(90, 0, 0));
			transform.Scale = glm::vec3(5, 5, 5);
			gameObject->transform = transform;
			MeshRenderer mesh;
			mesh.Enabled = true;
			mesh.Mesh = "Zombie";
			mesh.Path = "assets/models/Zombie.ply";
			/*mesh.RGBA = glm::vec4(1, 0, 0, 1);
			mesh.SPEC = glm::vec4(0, 1, 1, 1);
			mesh.bUseRGBA = true;
			mesh.bUseLight = true;
			mesh.bVisible = true;
			mesh.Textures[0] = "ZombieTexture";
			mesh.TextureRatios[0] = 1.f;*/
			gameObject->mesh = mesh;
			gameObjectsToSave.push_back(gameObject);
			std::ofstream saveFile;
			saveFile.open("./savedata/gameObjectData.json");
			json gameObjects;
			for (Entity* go : gameObjectsToSave)
			{
				json jGameObject;
				jGameObject.push_back(json{ {"ID", go->GetID()} });
				jGameObject.push_back(json{ {"Name", go->name} });
				// Check if it has a Transform component, will be fixed later using hasComponent
				if (1)
				{
					json jTransform = json{ {"Enabled", go->transform.Enabled},
						{"Position", json::array({go->transform.Position.x, go->transform.Position.y, go->transform.Position.z})},
						{"Rotation", json::array({go->transform.Rotation.w, go->transform.Rotation.x, go->transform.Rotation.y, go->transform.Rotation.z})},
						{"Scale", json::array({go->transform.Scale.x, go->transform.Scale.y, go->transform.Scale.z})}
				};
					jGameObject.push_back(json{ {"Transform", jTransform} });
				}
				// Check if it has a Mesh component, will be fixed later using hasComponent
				/*if (1)
				{
					json jMesh = json{ {"Enabled", go->mesh.Enabled},
						{"Mesh", go->mesh.Mesh}, {"Path", go->mesh.Path }, 
						{"RGBA", json::array( {go->mesh.RGBA.x, go->mesh.RGBA.y, go->mesh.RGBA.z, go->mesh.RGBA.w} )},
						{"SPEC", json::array( {go->mesh.SPEC.x, go->mesh.SPEC.y, go->mesh.SPEC.z, go->mesh.SPEC.w} )},
						{"bWireFrame", go->mesh.bWireframe}, {"bUseRGBA", go->mesh.bUseRGBA}, {"bUseLight", go->mesh.bUseLight},
						{"bVisible", go->mesh.bVisible}, {"Textures", json::array({go->mesh.Textures[0], go->mesh.Textures[1], go->mesh.Textures[2],
							go->mesh.Textures[3], go->mesh.Textures[4], go->mesh.Textures[5], go->mesh.Textures[6],go->mesh.Textures[7]})},
						{"TextureRatios", json::array({go->mesh.TextureRatios[0], go->mesh.TextureRatios[1], go->mesh.TextureRatios[2], go->mesh.TextureRatios[3],
							go->mesh.TextureRatios[4], go->mesh.TextureRatios[5], go->mesh.TextureRatios[6],go->mesh.TextureRatios[7]})},
					};
					jGameObject.push_back(json{ { "MeshRenderer", jMesh } });
				}*/
				// Check if it has a Light component, will be fixed later using hasComponent
				if (1)
				{
					json jLight = json{ {"Enabled", go->light.Enabled}, { "LightType", go->light.LightType},
						{"Diffuse", json::array({go->light.Diffuse.x, go->light.Diffuse.y, go->light.Diffuse.z, go->light.Diffuse.w })},
						{"Specular", json::array({go->light.Specular.x, go->light.Specular.y, go->light.Specular.z, go->light.Specular.w })},
						{"Attenuation", json::array({go->light.Attenuation.x, go->light.Attenuation.y, go->light.Attenuation.z, go->light.Attenuation.w })},
						{"OuterAngle", go->light.OuterAngle}, {"InnerAngle", go->light.InnerAngle}
				};
					jGameObject.push_back(json{ {"Light", jLight} });
				}
				gameObjects.push_back(json{ { "Name", jGameObject} });
			}
			saveFile << gameObjects;
			saveFile.close();
		}
		void LoadGameObjects(std::vector<Entity*>& gameObjectsToLoad)
		{
		}
}
}