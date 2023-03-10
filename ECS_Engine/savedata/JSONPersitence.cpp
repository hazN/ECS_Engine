#include "JSONPersitence.h"

namespace sas {
	namespace persistence
	{
		// Method : SaveEntities
		// Summary: Saves entities in JSON format to SAVE_LOCATION
		// Accepts: vector<Entity*> 
		void SaveEntities(std::vector<Entity*> entitiesToSave)
		{
			// Open file
			std::ofstream saveFile;
			saveFile.open(SAVE_LOCATION);

			// Parent JSON Object
			json gameObjects;
			// Loop through each gameObject inside the entity vector
			for (Entity* go : entitiesToSave)
			{
				// GameObject JSON object that will be later added to the parent
				json jEntity;

				// Save basic gameObject info such as id, name, more can be added later
				jEntity.push_back(json{ {"ID", go->GetID()}, {"Name", go->name } });

				// Check if it has a Transform component
				// Transform block
				{
					Transform* goTransform = &go->transform;
					json jTransform = json{ {"Enabled", goTransform->Enabled},
						{"Position", json::array({goTransform->Position.x, goTransform->Position.y, goTransform->Position.z})},
						{"Rotation", json::array({goTransform->Rotation.w, goTransform->Rotation.x, goTransform->Rotation.y, goTransform->Rotation.z})},
						{"Scale", json::array({goTransform->Scale.x, goTransform->Scale.y, goTransform->Scale.z})}
				};
					jEntity.push_back(json{ {"Transform", jTransform} });
				}
				// Check if it has a Mesh component
				if (go->HasComponent<MeshRenderer>())
				{
					MeshRenderer* goMesh = go->GetComponentByType<MeshRenderer>();
					json jMesh = json{ {"Enabled", goMesh->Enabled},
						{"Mesh", goMesh->Mesh}, {"Path", goMesh->Path }, {"MaterialPath", goMesh->MaterialPath}
					};
					jEntity.push_back(json{ { "MeshRenderer", jMesh } });
					if (goMesh->MaterialPath != "")
					{
						std::ofstream Material;
						Material.open(goMesh->MaterialPath);
						json jMaterial = json{ {"RGBA", json::array({goMesh->material->RGBA.x, goMesh->material->RGBA.y, goMesh->material->RGBA.z, goMesh->material->RGBA.w})},
							{"SPEC", json::array({goMesh->material->SPEC.x, goMesh->material->SPEC.y, goMesh->material->SPEC.z, goMesh->material->SPEC.w})},
							{"bWireframe", goMesh->material->bWireframe}, {"bUseRGBA", goMesh->material->bUseRGBA}, {"bUseLight", goMesh->material->bUseRGBA},
							{"bUseLight", goMesh->material->bUseLight}, {"bVisible", goMesh->material->bVisible},
							{"Textures", json::array({goMesh->material->Textures[0], goMesh->material->Textures[1],goMesh->material->Textures[2], goMesh->material->Textures[3],
								goMesh->material->Textures[4], goMesh->material->Textures[5], goMesh->material->Textures[6], goMesh->material->Textures[7]})},
							{"TextureRatios", json::array({goMesh->material->TextureRatios[0], goMesh->material->TextureRatios[1],goMesh->material->TextureRatios[2], goMesh->material->TextureRatios[3],
								goMesh->material->TextureRatios[4], goMesh->material->TextureRatios[5], goMesh->material->TextureRatios[6], goMesh->material->TextureRatios[7]})}
						};
						Material << jMaterial;
						Material.close();
					}
				}
				// Check if it has a Light component
				if (go->HasComponent<Light>())
				{
					Light* goLight = go->GetComponentByType<Light>();
					json jLight = json{ {"Enabled", goLight->Enabled}, { "LightType", goLight->LightType},
						{"Diffuse", json::array({goLight->Diffuse.x, goLight->Diffuse.y, goLight->Diffuse.z, goLight->Diffuse.w })},
						{"Specular", json::array({goLight->Specular.x, goLight->Specular.y, goLight->Specular.z, goLight->Specular.w })},
						{"Attenuation", json::array({goLight->Attenuation.x, goLight->Attenuation.y, goLight->Attenuation.z, goLight->Attenuation.w })},
						{"OuterAngle", goLight->OuterAngle}, {"InnerAngle", goLight->InnerAngle}
				};
					jEntity.push_back(json{ {"Light", jLight} });
				}
				gameObjects.push_back(json{ { go->name, jEntity} });
			}
			saveFile << gameObjects;
			saveFile.close();
		}
		
		// Method : LoadEntities
		// Summary: Loads entities from JSON to given vector
		// Accepts: vector<Entity*>&
		void LoadEntities(std::vector<Entity*>& entitiesToLoad)
		{
			std::ifstream file(SAVE_LOCATION, std::ifstream::in);
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
				std::cout << "Error loading "<<SAVE_LOCATION<<".json, save file may be corrupted." << std::endl;
				return;
			}
			for (json header : f)
			{
				for (json header2 : header)
				{
					Entity* entity = new Entity();
					for (json jGO : header2)
					{
						// Check for INFO Field
						if (jGO.contains("ID"))
						{
							entity->SetID(jGO.at("ID"));
							entity->name = jGO.at("Name");
						}
						// Check for Transform Field
						if (jGO.contains("Transform"))
						{
							entity->transform.Enabled = jGO.at("Transform").at("Enabled");
							entity->transform.Position.x = jGO.at("Transform").at("Position")[0];
							entity->transform.Position.y = jGO.at("Transform").at("Position")[1];
							entity->transform.Position.z = jGO.at("Transform").at("Position")[2];
							entity->transform.Rotation.w = jGO.at("Transform").at("Rotation")[0];
							entity->transform.Rotation.x = jGO.at("Transform").at("Rotation")[1];
							entity->transform.Rotation.y = jGO.at("Transform").at("Rotation")[2];
							entity->transform.Rotation.z = jGO.at("Transform").at("Rotation")[3];
							entity->transform.Scale.x = jGO.at("Transform").at("Scale")[0];
							entity->transform.Scale.y = jGO.at("Transform").at("Scale")[1];
							entity->transform.Scale.z = jGO.at("Transform").at("Scale")[2];
						}
						// Check for MeshRenderer Field
						if (jGO.contains("MeshRenderer"))
						{ 
							MeshRenderer* meshRenderer = new MeshRenderer();
							meshRenderer->Enabled = jGO.at("MeshRenderer").at("Enabled");
							meshRenderer->Mesh = jGO.at("MeshRenderer").at("Mesh");
							meshRenderer->Path = jGO.at("MeshRenderer").at("Path");
							meshRenderer->MaterialPath = jGO.at("MeshRenderer").at("MaterialPath");
							// Check if there is a material to get aswell
							Material* material = new Material();
							if (meshRenderer->MaterialPath != "")
							{
								LoadMaterial(material, meshRenderer->MaterialPath);
								meshRenderer->material = material;
							}
							entity->AddComponent(meshRenderer);
						}
						// Check for Light field
						//tba
					}
					entitiesToLoad.push_back(entity);
				}
			}
		}

		// LoadMaterial
		// Load a material from the given path
		// Accepts: Material*, String
		void LoadMaterial(Material* materialToLoad, std::string path)
		{
			std::ifstream file(path, std::ifstream::in);
			json jMaterial;

			// Handle any exceptions
			try
			{
				file >> jMaterial;
			}
			catch (json::exception& e)
			{
				std::cout << e.what() << std::endl;
			}
			if (jMaterial == nlohmann::detail::value_t::null)
			{
				std::cout << "Error loading "<<path<<".json, save file may be corrupted." << std::endl;
				return;
			}
			// Load in the material
			materialToLoad->RGBA.x = jMaterial.at("RGBA")[0];
			materialToLoad->RGBA.y = jMaterial.at("RGBA")[1];
			materialToLoad->RGBA.z = jMaterial.at("RGBA")[2];
			materialToLoad->RGBA.w = jMaterial.at("RGBA")[3];
			materialToLoad->SPEC.x = jMaterial.at("SPEC")[0];
			materialToLoad->SPEC.y = jMaterial.at("SPEC")[1];
			materialToLoad->SPEC.z = jMaterial.at("SPEC")[2];
			materialToLoad->SPEC.w = jMaterial.at("SPEC")[3];
			materialToLoad->bUseLight = jMaterial.at("bUseLight");
			materialToLoad->bUseRGBA = jMaterial.at("bUseRGBA");
			materialToLoad->bVisible = jMaterial.at("bVisible");
			materialToLoad->bWireframe = jMaterial.at("bWireframe");
			materialToLoad->Textures[0] = jMaterial.at("Textures")[0];
			materialToLoad->Textures[1] = jMaterial.at("Textures")[1];
			materialToLoad->Textures[2] = jMaterial.at("Textures")[2];
			materialToLoad->Textures[3] = jMaterial.at("Textures")[3];
			materialToLoad->Textures[4] = jMaterial.at("Textures")[4];
			materialToLoad->Textures[5] = jMaterial.at("Textures")[5];
			materialToLoad->Textures[6] = jMaterial.at("Textures")[6];
			materialToLoad->Textures[7] = jMaterial.at("Textures")[7];
			materialToLoad->TextureRatios[0] = jMaterial.at("TextureRatios")[0];
			materialToLoad->TextureRatios[1] = jMaterial.at("TextureRatios")[1];
			materialToLoad->TextureRatios[2] = jMaterial.at("TextureRatios")[2];
			materialToLoad->TextureRatios[3] = jMaterial.at("TextureRatios")[3];
			materialToLoad->TextureRatios[4] = jMaterial.at("TextureRatios")[4];
			materialToLoad->TextureRatios[5] = jMaterial.at("TextureRatios")[5];
			materialToLoad->TextureRatios[6] = jMaterial.at("TextureRatios")[6];
			materialToLoad->TextureRatios[7] = jMaterial.at("TextureRatios")[7];
		}
}
}