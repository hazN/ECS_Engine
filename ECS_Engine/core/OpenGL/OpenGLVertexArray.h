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

		virtual bool LoadModelIntoVAO(std::string filename, sModelDrawInfo& drawInfo, unsigned int shaderProgramID) override;
		virtual bool FindDrawInfoByModelName(std::string filename, sModelDrawInfo& drawinfo) override;
		virtual bool LoadPlyFiles(std::string filename, sModelDrawInfo& drawinfo) override;

	private:
		// Store model info with mesh name
		// TEMPORARY
		std::map<std::string, sModelDrawInfo> m_Map_Model_to_VAOID;
	};
}