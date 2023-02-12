#pragma once
#include <string>
#include <Renderer/Material.h>


namespace sas
{
	class MeshRenderer
	{
	public:
		bool Enabled;

		std::string Mesh;
		std::string Path;
		std::string MaterialPath;
		Material* material;
	};
}