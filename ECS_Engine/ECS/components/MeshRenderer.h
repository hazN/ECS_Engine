#pragma once
#include <string>
#include <Renderer/Material.h>
#include "../Component.h"


namespace sas
{
	class MeshRenderer : public Component
	{
	public:
		MeshRenderer();
		virtual ~MeshRenderer();
		bool Enabled;

		std::string Mesh;
		std::string Path;
		std::string MaterialPath;
		Material* material;
	};
}