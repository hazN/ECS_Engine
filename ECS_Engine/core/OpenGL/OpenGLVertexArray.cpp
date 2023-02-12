#include "OpenGLVertexArray.h"
#include <GLFW/glfw3.h>
#include <glad/glad.h>
namespace sas
{
	OpenGLVertexArray::OpenGLVertexArray()
	{
	}
	OpenGLVertexArray::~OpenGLVertexArray()
	{
		for (std::map<std::string, sModelDrawInfo>::iterator it = m_Map_Model_to_VAOID.begin();
			it != m_Map_Model_to_VAOID.end(); it++)
		{
			glDeleteVertexArrays(1, &it->second.VAO_ID);
		}
	}
	bool OpenGLVertexArray::LoadModelIntoVAO(std::string filename, sModelDrawInfo& drawInfo, unsigned int shaderProgramID)
	{
		drawInfo.meshName = filename;
		// Ask OpenGL for a new buffer ID...
		glGenVertexArrays(1, &(drawInfo.VAO_ID));
		// "Bind" this buffer:
		// - aka "make this the 'current' VAO buffer
		glBindVertexArray(drawInfo.VAO_ID);

		// Now ANY state that is related to vertex or index buffer
		//	and vertex attribute layout, is stored in the 'state' 
		//	of the VAO... 


		// NOTE: OpenGL error checks have been omitted for brevity
	//	glGenBuffers(1, &vertex_buffer);
		glGenBuffers(1, &(drawInfo.VertexBufferID));

		//	glBindBuffer(GL_ARRAY_BUFFER, vertex_buffer);
		glBindBuffer(GL_ARRAY_BUFFER, drawInfo.VertexBufferID);
		// sVert vertices[3]
		glBufferData(GL_ARRAY_BUFFER,
			sizeof(sVertex_RGBA_XYZ_N_UV_T_BiN_Bones) * drawInfo.numberOfVertices,	// ::g_NumberOfVertsToDraw,	// sizeof(vertices), 
			(GLvoid*)drawInfo.pVertices,							// pVertices,			//vertices, 
			GL_STATIC_DRAW);


		// Copy the index buffer into the video card, too
		// Create an index buffer.
		glGenBuffers(1, &(drawInfo.IndexBufferID));

		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, drawInfo.IndexBufferID);

		glBufferData(GL_ELEMENT_ARRAY_BUFFER,			// Type: Index element array
			sizeof(unsigned int) * drawInfo.numberOfIndices,
			(GLvoid*)drawInfo.pIndices,
			GL_STATIC_DRAW);


		//   __     __        _              _                            _   
		//   \ \   / /__ _ __| |_ _____  __ | |    __ _ _   _  ___  _   _| |_ 
		//    \ \ / / _ \ '__| __/ _ \ \/ / | |   / _` | | | |/ _ \| | | | __|
		//     \ V /  __/ |  | ||  __/>  <  | |__| (_| | |_| | (_) | |_| | |_ 
		//      \_/ \___|_|   \__\___/_/\_\ |_____\__,_|\__, |\___/ \__,_|\__|
		//                                              |___/                 

			// in vec4 vColour;
		GLint vColour_location = glGetAttribLocation(shaderProgramID, "vColour");
		glEnableVertexAttribArray(vColour_location);
		glVertexAttribPointer(vColour_location,
			4, GL_FLOAT,
			GL_FALSE,
			sizeof(sVertex_RGBA_XYZ_N_UV_T_BiN_Bones),						// Stride	(number of bytes)
			(void*)offsetof(sVertex_RGBA_XYZ_N_UV_T_BiN_Bones, r));		// Offset the member variable

		//in vec4 vPosition;			
		GLint vPosition_location = glGetAttribLocation(shaderProgramID, "vPosition");
		glEnableVertexAttribArray(vPosition_location);
		glVertexAttribPointer(vPosition_location,
			4, GL_FLOAT,
			GL_FALSE,
			sizeof(sVertex_RGBA_XYZ_N_UV_T_BiN_Bones),						// Stride	(number of bytes)
			(void*)offsetof(sVertex_RGBA_XYZ_N_UV_T_BiN_Bones, x));		// Offset the member variable

		//in vec4 vNormal;			
		GLint vNormal_location = glGetAttribLocation(shaderProgramID, "vNormal");
		glEnableVertexAttribArray(vNormal_location);
		glVertexAttribPointer(vNormal_location,
			4, GL_FLOAT,
			GL_FALSE,
			sizeof(sVertex_RGBA_XYZ_N_UV_T_BiN_Bones),						// Stride	(number of bytes)
			(void*)offsetof(sVertex_RGBA_XYZ_N_UV_T_BiN_Bones, nx));		// Offset the member variable

		//in vec4 vUVx2;			
		GLint vUVx2_location = glGetAttribLocation(shaderProgramID, "vUVx2");
		glEnableVertexAttribArray(vUVx2_location);
		glVertexAttribPointer(vUVx2_location,
			4, GL_FLOAT,
			GL_FALSE,
			sizeof(sVertex_RGBA_XYZ_N_UV_T_BiN_Bones),						// Stride	(number of bytes)
			(void*)offsetof(sVertex_RGBA_XYZ_N_UV_T_BiN_Bones, u0));		// Offset the member variable

		//in vec4 vTangent;			
		GLint vTangent_location = glGetAttribLocation(shaderProgramID, "vTangent");
		glEnableVertexAttribArray(vTangent_location);
		glVertexAttribPointer(vTangent_location,
			4, GL_FLOAT,
			GL_FALSE,
			sizeof(sVertex_RGBA_XYZ_N_UV_T_BiN_Bones),						// Stride	(number of bytes)
			(void*)offsetof(sVertex_RGBA_XYZ_N_UV_T_BiN_Bones, tx));		// Offset the member variable

		//in vec4 vBiNormal;		
		GLint vBiNormal_location = glGetAttribLocation(shaderProgramID, "vBiNormal");
		glEnableVertexAttribArray(vBiNormal_location);
		glVertexAttribPointer(vBiNormal_location,
			4, GL_FLOAT,
			GL_FALSE,
			sizeof(sVertex_RGBA_XYZ_N_UV_T_BiN_Bones),						// Stride	(number of bytes)
			(void*)offsetof(sVertex_RGBA_XYZ_N_UV_T_BiN_Bones, bx));		// Offset the member variable

		//in vec4 vBoneID;			
		GLint vBoneID_location = glGetAttribLocation(shaderProgramID, "vBoneID");
		glEnableVertexAttribArray(vBoneID_location);
		glVertexAttribPointer(vBoneID_location,
			4, GL_FLOAT,
			GL_FALSE,
			sizeof(sVertex_RGBA_XYZ_N_UV_T_BiN_Bones),						// Stride	(number of bytes)
			(void*)offsetof(sVertex_RGBA_XYZ_N_UV_T_BiN_Bones, vBoneID[0]));		// Offset the member variable

		//in vec4 vBoneWeight;		
		GLint vBoneWeight_location = glGetAttribLocation(shaderProgramID, "vBoneWeight");
		glEnableVertexAttribArray(vBoneWeight_location);
		glVertexAttribPointer(vBoneWeight_location,
			4, GL_FLOAT,
			GL_FALSE,
			sizeof(sVertex_RGBA_XYZ_N_UV_T_BiN_Bones),						// Stride	(number of bytes)
			(void*)offsetof(sVertex_RGBA_XYZ_N_UV_T_BiN_Bones, vBoneWeight[0]));		// Offset the member variable




		// Now that all the parts are set up, set the VAO to zero
		glBindVertexArray(0);

		glBindBuffer(GL_ARRAY_BUFFER, 0);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

		glDisableVertexAttribArray(vColour_location);
		glDisableVertexAttribArray(vPosition_location);
		glDisableVertexAttribArray(vNormal_location);
		glDisableVertexAttribArray(vUVx2_location);
		glDisableVertexAttribArray(vTangent_location);
		glDisableVertexAttribArray(vBiNormal_location);
		glDisableVertexAttribArray(vBoneID_location);
		glDisableVertexAttribArray(vBoneWeight_location);

		// Store the draw information into the map
		this->m_Map_Model_to_VAOID[drawInfo.meshName] = drawInfo;
		return true;
	}
	bool OpenGLVertexArray::FindDrawInfoByModelName(std::string filename, sModelDrawInfo& drawInfo)
	{
		std::map<std::string, sModelDrawInfo>::iterator itDrawInfo = this->m_Map_Model_to_VAOID.find(filename);

		if (itDrawInfo == this->m_Map_Model_to_VAOID.end())
			return false;

		drawInfo = itDrawInfo->second;
		return true;;
	}
}