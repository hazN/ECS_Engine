#pragma once
#include <string>
#include <glm/glm.hpp>
#include <memory>


namespace sas
{
	// Stride layout
	struct sVertex_RGBA_XYZ_N_UV_T_BiN_Bones
	{
		float r, g, b, a;		//	in vec4 vColour;			// Was vec3
		float x, y, z, w;		//	in vec4 vPosition;			// Was vec3
		float nx, ny, nz, nw;	//	in vec4 vNormal;			// Vertex normal
		float u0, v0, u1, v1;	//	in vec4 vUVx2;				// 2 x Texture coords
		float tx, ty, yz, tw;	//	in vec4 vTangent;			// For bump mapping
		float bx, by, bz, bw;	//	in vec4 vBiNormal;			// For bump mapping
		float vBoneID[4];		//	in vec4 vBoneID;		// For skinned mesh (FBX)
		float vBoneWeight[4];	//	in vec4 vBoneWeight;		// For skinned mesh (FBX)
	};

	// Drawing information
	struct sModelDrawInfo
	{
		sModelDrawInfo();

		std::string meshName;

		unsigned int VAO_ID;

		unsigned int VertexBufferID;
		unsigned int VertexBuffer_Start_Index;
		unsigned int numberOfVertices;

		unsigned int IndexBufferID;
		unsigned int IndexBuffer_Start_Index;
		unsigned int numberOfIndices;
		unsigned int numberOfTriangles;

		sVertex_RGBA_XYZ_N_UV_T_BiN_Bones* pVertices;

		unsigned int* pIndices;

		glm::vec3 maxValues;
		glm::vec3 minValues;
	};

	// Parent Vertex Array
	class VertexArray
	{
	public:
		virtual ~VertexArray() = default;

		// Load models into API specific Vertex Array
		virtual bool LoadModelIntoVAO(std::string filename, sModelDrawInfo& drawInfo, unsigned int shaderProgramID) = 0;
		
		// Find drawing information using mesh name [TEMPORARY]
		virtual bool FindDrawInfoByModelName(std::string filename, sModelDrawInfo& drawinfo) = 0;
		
		// Read 3D files with .ply extension and store information in drawinfo
		virtual bool LoadPlyFiles(std::string filename, sModelDrawInfo& drawinfo) = 0;

		// Create API specific vertex array
		static std::shared_ptr<VertexArray> Create();
	};




}