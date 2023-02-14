#pragma once
#include "../Renderer/VertexArray.h"
#include <map>

namespace sas
{
	// Vertex Array Manager, OpenGL specific
	class OpenGLVertexArray : public VertexArray
	{
	public:
	public:
		OpenGLVertexArray();
		virtual ~OpenGLVertexArray();

		// Load models into API specific Vertex Array
		virtual bool LoadModelIntoVAO(std::string filename, sModelDrawInfo& drawInfo, unsigned int shaderProgramID) override;
		
		// Find drawing information using mesh name [TEMPORARY]
		virtual bool FindDrawInfoByModelName(std::string filename, sModelDrawInfo& drawinfo) override;

		// Read 3D files with .ply extension and store information in drawinfo
		virtual bool LoadPlyFiles(std::string filename, sModelDrawInfo& drawinfo) override;

	private:
		// Store model info with mesh name
		// TEMPORARY
		std::map<std::string, sModelDrawInfo> m_Map_Model_to_VAOID;
	};
}