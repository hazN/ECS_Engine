#include "OpenGLVertexArray.h"
#include <GLFW/glfw3.h>
#include <glad/glad.h>
#include <fstream>
#include <iostream>
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
		unsigned int index = 0;
		//GLint vColour_location = glGetAttribLocation(shaderProgramID, "vColour");
		//glBindAttribLocation(shaderProgramID, index, "vColour");
		glEnableVertexAttribArray(index);
		glVertexAttribPointer(index,
			4, GL_FLOAT,
			GL_FALSE,
			sizeof(sVertex_RGBA_XYZ_N_UV_T_BiN_Bones),						// Stride	(number of bytes)
			(void*)offsetof(sVertex_RGBA_XYZ_N_UV_T_BiN_Bones, r));		// Offset the member variable
		index++;

		//in vec4 vPosition;			
		//GLint vPosition_location = glGetAttribLocation(shaderProgramID, "vPosition");
		//glBindAttribLocation(shaderProgramID, index, "vPosition");
		glEnableVertexAttribArray(index);
		glVertexAttribPointer(index,
			4, GL_FLOAT,
			GL_FALSE,
			sizeof(sVertex_RGBA_XYZ_N_UV_T_BiN_Bones),						// Stride	(number of bytes)
			(void*)offsetof(sVertex_RGBA_XYZ_N_UV_T_BiN_Bones, x));		// Offset the member variable
		index++;

		//in vec4 vNormal;			
		//GLint vNormal_location = glGetAttribLocation(shaderProgramID, "vNormal");
		//glBindAttribLocation(shaderProgramID, index, "vNormal");
		glEnableVertexAttribArray(index);
		glVertexAttribPointer(index,
			4, GL_FLOAT,
			GL_FALSE,
			sizeof(sVertex_RGBA_XYZ_N_UV_T_BiN_Bones),						// Stride	(number of bytes)
			(void*)offsetof(sVertex_RGBA_XYZ_N_UV_T_BiN_Bones, nx));		// Offset the member variable
		index++;

		//in vec4 vUVx2;			
		//GLint vUVx2_location = glGetAttribLocation(shaderProgramID, "vUVx2");
		//glBindAttribLocation(shaderProgramID, index, "vUVx2");
		glEnableVertexAttribArray(index);
		glVertexAttribPointer(index,
			4, GL_FLOAT,
			GL_FALSE,
			sizeof(sVertex_RGBA_XYZ_N_UV_T_BiN_Bones),						// Stride	(number of bytes)
			(void*)offsetof(sVertex_RGBA_XYZ_N_UV_T_BiN_Bones, u0));		// Offset the member variable
		index++;

		//in vec4 vTangent;			
		//GLint vTangent_location = glGetAttribLocation(shaderProgramID, "vTangent");
		//glBindAttribLocation(shaderProgramID, index, "vTangent");
		glEnableVertexAttribArray(index);
		glVertexAttribPointer(index,
			4, GL_FLOAT,
			GL_FALSE,
			sizeof(sVertex_RGBA_XYZ_N_UV_T_BiN_Bones),						// Stride	(number of bytes)
			(void*)offsetof(sVertex_RGBA_XYZ_N_UV_T_BiN_Bones, tx));		// Offset the member variable
		index++;

		//in vec4 vBiNormal;		
		//GLint vBiNormal_location = glGetAttribLocation(shaderProgramID, "vBiNormal");
		//glBindAttribLocation(shaderProgramID, index, "vBiNormal");
		glEnableVertexAttribArray(index);
		glVertexAttribPointer(index,
			4, GL_FLOAT,
			GL_FALSE,
			sizeof(sVertex_RGBA_XYZ_N_UV_T_BiN_Bones),						// Stride	(number of bytes)
			(void*)offsetof(sVertex_RGBA_XYZ_N_UV_T_BiN_Bones, bx));		// Offset the member variable
		index++;

		//in vec4 vBoneID;			
		//GLint vBoneID_location = glGetAttribLocation(shaderProgramID, "vBoneID");
		//glBindAttribLocation(shaderProgramID, index, "vBoneID");
		glEnableVertexAttribArray(index);
		glVertexAttribPointer(index,
			4, GL_FLOAT,
			GL_FALSE,
			sizeof(sVertex_RGBA_XYZ_N_UV_T_BiN_Bones),						// Stride	(number of bytes)
			(void*)offsetof(sVertex_RGBA_XYZ_N_UV_T_BiN_Bones, vBoneID[0]));		// Offset the member variable
		index++;

		//in vec4 vBoneWeight;		
		//GLint vBoneWeight_location = glGetAttribLocation(shaderProgramID, "vBoneWeight");
		//glBindAttribLocation(shaderProgramID, index, "vBoneWeight");
		glEnableVertexAttribArray(index);
		glVertexAttribPointer(index,
			4, GL_FLOAT,
			GL_FALSE,
			sizeof(sVertex_RGBA_XYZ_N_UV_T_BiN_Bones),						// Stride	(number of bytes)
			(void*)offsetof(sVertex_RGBA_XYZ_N_UV_T_BiN_Bones, vBoneWeight[0]));		// Offset the member variable
		index++;



		// Now that all the parts are set up, set the VAO to zero
		/*glBindVertexArray(0);

		glBindBuffer(GL_ARRAY_BUFFER, 0);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

		glDisableVertexAttribArray(0);
		glDisableVertexAttribArray(1);
		glDisableVertexAttribArray(2);
		glDisableVertexAttribArray(3);
		glDisableVertexAttribArray(4);
		glDisableVertexAttribArray(5);
		glDisableVertexAttribArray(6);
		glDisableVertexAttribArray(7);*/

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
	bool OpenGLVertexArray::LoadPlyFiles(std::string fileName, sModelDrawInfo& modelDrawInfo)
	{
		struct sVertex_XYZ_N_RGBA_UV
		{
			float x, y, z;
			float nx, ny, nz;

			float red, green, blue, alpha;
			float texture_u, texture_v;
		};

		struct sTrianglePLY
		{
			unsigned int vertexIndices[3];
		};

		sVertex_XYZ_N_RGBA_UV* pTheModelArray = NULL;
		sTrianglePLY* pTheModelTriangleArray = NULL;

		std::ifstream theFile(fileName);
		if (!theFile.is_open())
		{
			std::cout << "Couldn\'t open the model file";
			return false;
		}

		char buffer[10000];
		theFile.getline(buffer, 10000);

		std::string theNextToken;

		while (theFile >> theNextToken)
			if (theNextToken == "vertex")
				break;

		theFile >> modelDrawInfo.numberOfVertices;

		bool hasColours = false;
		while (theFile >> theNextToken)
		{
			if (theNextToken == "red")
				hasColours = true;
			if (theNextToken == "face")
				break;
		}

		theFile >> modelDrawInfo.numberOfTriangles;

		while (theFile >> theNextToken)
			if (theNextToken == "end_header")
				break;

		pTheModelArray = new sVertex_XYZ_N_RGBA_UV[modelDrawInfo.numberOfVertices];

		std::cout << "Loading";
		for (unsigned int count = 0; count != modelDrawInfo.numberOfVertices; count++)
		{
			theFile >> pTheModelArray[count].x;
			theFile >> pTheModelArray[count].y;
			theFile >> pTheModelArray[count].z;

			theFile >> pTheModelArray[count].nx;
			theFile >> pTheModelArray[count].ny;
			theFile >> pTheModelArray[count].nz;

			if (hasColours)
			{
				theFile >> pTheModelArray[count].red;
				theFile >> pTheModelArray[count].green;
				theFile >> pTheModelArray[count].blue;
				theFile >> pTheModelArray[count].alpha;
			}


			theFile >> pTheModelArray[count].texture_u;
			theFile >> pTheModelArray[count].texture_v;

			if (count % 10000 == 0)
				std::cout << ".";

		}

		std::cout << " done" << std::endl;

		pTheModelTriangleArray = new sTrianglePLY[modelDrawInfo.numberOfTriangles];

		for (unsigned int count = 0; count != modelDrawInfo.numberOfTriangles; count++)
		{
			// to discard first value
			unsigned int discard = 0;
			theFile >> discard;

			theFile >> pTheModelTriangleArray[count].vertexIndices[0];
			theFile >> pTheModelTriangleArray[count].vertexIndices[1];
			theFile >> pTheModelTriangleArray[count].vertexIndices[2];

		}

		theFile.close();

		modelDrawInfo.pVertices = new sVertex_RGBA_XYZ_N_UV_T_BiN_Bones[modelDrawInfo.numberOfVertices];
		glm::vec3 minPoints = glm::vec3(FLT_MAX, FLT_MAX, FLT_MAX);
		glm::vec3 maxPoints = glm::vec3(FLT_MIN, FLT_MIN, FLT_MIN);
		for (unsigned int index = 0; index != modelDrawInfo.numberOfVertices; index++)
		{
			// To shader								from File
			modelDrawInfo.pVertices[index].x = pTheModelArray[index].x;
			modelDrawInfo.pVertices[index].y = pTheModelArray[index].y;
			modelDrawInfo.pVertices[index].z = pTheModelArray[index].z;


			if (minPoints.x > pTheModelArray[index].x)
				minPoints.x = pTheModelArray[index].x;

			if (minPoints.y > pTheModelArray[index].y)
				minPoints.y = pTheModelArray[index].y;

			if (minPoints.z > pTheModelArray[index].z)
				minPoints.z = pTheModelArray[index].z;

			if (maxPoints.x < pTheModelArray[index].x)
				maxPoints.x = pTheModelArray[index].x;

			if (maxPoints.y < pTheModelArray[index].y)
				maxPoints.y = pTheModelArray[index].y;

			if (maxPoints.z < pTheModelArray[index].z)
				maxPoints.z = pTheModelArray[index].z;

			modelDrawInfo.pVertices[index].r = pTheModelArray[index].red;
			modelDrawInfo.pVertices[index].g = pTheModelArray[index].green;
			modelDrawInfo.pVertices[index].b = pTheModelArray[index].blue;

			modelDrawInfo.pVertices[index].nx = pTheModelArray[index].nx;
			modelDrawInfo.pVertices[index].ny = pTheModelArray[index].ny;
			modelDrawInfo.pVertices[index].nz = pTheModelArray[index].nz;

			// Copy the texture coordinates we loaded
			modelDrawInfo.pVertices[index].u0 = pTheModelArray[index].texture_u;
			modelDrawInfo.pVertices[index].v0 = pTheModelArray[index].texture_v;
		}
		std::cout << fileName << " Min values: " << minPoints.x << ", "
			<< minPoints.y << ", " << minPoints.z << "\nMax values: " << maxPoints.x << ", "
			<< maxPoints.y << ", " << maxPoints.z << std::endl;
		modelDrawInfo.numberOfIndices = modelDrawInfo.numberOfTriangles * 3;
		modelDrawInfo.minValues = minPoints;
		modelDrawInfo.maxValues = maxPoints;

		modelDrawInfo.pIndices = new unsigned int[modelDrawInfo.numberOfIndices];

		unsigned int vertex_element_index_index = 0;

		for (unsigned int triangleIndex = 0; triangleIndex != modelDrawInfo.numberOfTriangles; triangleIndex++)
		{
			modelDrawInfo.pIndices[vertex_element_index_index + 0] = pTheModelTriangleArray[triangleIndex].vertexIndices[0];
			modelDrawInfo.pIndices[vertex_element_index_index + 1] = pTheModelTriangleArray[triangleIndex].vertexIndices[1];
			modelDrawInfo.pIndices[vertex_element_index_index + 2] = pTheModelTriangleArray[triangleIndex].vertexIndices[2];

			vertex_element_index_index += 3;
		}

		delete[] pTheModelArray;
		delete[] pTheModelTriangleArray;
		return true;
	}
}