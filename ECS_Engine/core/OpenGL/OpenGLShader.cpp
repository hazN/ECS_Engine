#include "OpenGLShader.h"
#include <sstream>
#include <iostream>
#include <fstream>
#include <glm/gtc/type_ptr.hpp>

namespace sas
{
	OpenGLShader::OpenGLShader(const std::string& vertexShaderFile, const std::string& fragmentShaderFile)
	{
		std::cout << "Compiling shaders....." << std::endl;
		if (Init(vertexShaderFile, fragmentShaderFile))
		{
			std::cout << "Shaders compiled successfully." << std::endl;
		}
		
	}
	OpenGLShader::~OpenGLShader()
	{
		glDeleteProgram(m_RendererID);
	}
	void OpenGLShader::Bind() const
	{
		glUseProgram(m_RendererID);
	}
	void OpenGLShader::UnBind() const
	{
		glUseProgram(0);
	}
	
	void OpenGLShader::UploadUniformInt(const std::string& uniformName, int value)
	{
		GLint location = glGetUniformLocation(m_RendererID, uniformName.c_str());
		glUniform1i(location, value);
	}

	void OpenGLShader::UploadUniformFloat(const std::string& uniformName, float value)
	{
		GLint location = glGetUniformLocation(m_RendererID, uniformName.c_str());
		glUniform1f(location,(GLfloat) value);
	}

	void OpenGLShader::UploadUniformFloat2(const std::string& uniformName, const glm::vec2& values)
	{
		GLint location = glGetUniformLocation(m_RendererID, uniformName.c_str());
		glUniform2f(location, values.x, values.y);
	}

	void OpenGLShader::UploadUniformFloat3(const std::string& uniformName, const glm::vec3& values)
	{
		GLint location = glGetUniformLocation(m_RendererID, uniformName.c_str());
		glUniform3f(location, values.x, values.y, values.z);
	}

	void OpenGLShader::UploadUniformFloat4(const std::string& uniformName, const glm::vec4& values)
	{
		GLint location = glGetUniformLocation(m_RendererID, uniformName.c_str());
		glUniform4f(location, values.x, values.y, values.z, values.w);
	}

	void OpenGLShader::UploadUniformMat3(const std::string& uniformName, const glm::mat3& matrix)
	{
		GLint location = glGetUniformLocation(m_RendererID, uniformName.c_str());
		glUniformMatrix3fv(location, 1, false, glm::value_ptr(matrix));
	}

	void OpenGLShader::UploadUniformMat4(const std::string& uniformName, const glm::mat4& matrix)
	{
		//glUseProgram(m_RendererID);
		GLint location = glGetUniformLocation(m_RendererID, uniformName.c_str());
		glUniformMatrix4fv(location, 1, false, glm::value_ptr(matrix));
	}

	bool OpenGLShader::Init(const std::string& vertexShaderFile, const std::string& fragmentShaderFile)
	{
		std::string errorText = "";
		printf("Compiling shaders...");

		GLuint vertexShaderID = glCreateShader(GL_VERTEX_SHADER);
		std::vector<std::string>* verSource = new std::vector<std::string>;
		if (!this->m_loadSourceFromFile(vertexShaderFile, verSource))
			return false;

		errorText = "";
		if (!this->m_compileShaderFromSource(verSource, vertexShaderID, errorText))
		{
			this->m_LastError = errorText;
			std::cout << errorText << std::endl;
			return false;
		}

		errorText = "";

		GLuint fragmentShaderID = glCreateShader(GL_FRAGMENT_SHADER);

		std::vector<std::string>* fraSource = new std::vector<std::string>;
		if (!this->m_loadSourceFromFile(fragmentShaderFile, fraSource))
			return false;

		if (!this->m_compileShaderFromSource(fraSource, fragmentShaderID, errorText))
		{
			this->m_LastError = errorText;
			std::cout << errorText << std::endl;
			return false;
		}

		m_RendererID = glCreateProgram();

		glAttachShader(m_RendererID, vertexShaderID);
		glAttachShader(m_RendererID, fragmentShaderID);
		glLinkProgram(m_RendererID);

		errorText = "";

		if (this->m_wasThereALinkerError(m_RendererID, errorText))
		{
			std::stringstream ssError;
			ssError << "Shader program link error";
			ssError << errorText;
			this->m_LastError = ssError.str();
			std::cout << ssError.str() << std::endl;
			return false;
		}
		delete verSource;
		delete fraSource;
		return true;
	}
	const unsigned int MAXLINELENGTH = 65536;

	bool OpenGLShader::m_loadSourceFromFile(std::string fileName, std::vector<std::string>* srcVector)
	{
		std::ifstream theFile(fileName.c_str());

		if (!theFile.is_open())
			return false;

		srcVector->clear();

		char* pLineTemp = new char[MAXLINELENGTH];

		while (theFile.getline(pLineTemp, MAXLINELENGTH))
		{
			std::string tempString(pLineTemp);
			srcVector->push_back(tempString);
		}
		theFile.close();
		return true;
	}
	bool OpenGLShader::m_compileShaderFromSource(std::vector<std::string>* srcVector, GLuint id, std::string& error)
	{
		error = "";

		const unsigned int MAXLINESIZE = 8 * 1024;

		unsigned int numberOfLines = static_cast<unsigned int>(srcVector->size());

		char** arraySource = new char* [numberOfLines];

		memset(arraySource, 0, numberOfLines);

		for (unsigned int indexLine = 0; indexLine != numberOfLines; indexLine++)
		{
			unsigned int numCharacters = (unsigned int)srcVector->at(indexLine).length();

			arraySource[indexLine] = new char[numCharacters + 2];	// for the '\n' and '\0'
			memset(arraySource[indexLine], 0, numCharacters + 2);

			for (unsigned int indexChar = 0; indexChar != srcVector->at(indexLine).length(); indexChar++)
			{
				arraySource[indexLine][indexChar] = srcVector->at(indexLine)[indexChar];
			}

			arraySource[indexLine][numCharacters + 0] = '\n';
			arraySource[indexLine][numCharacters + 1] = '\0';
		}

		glShaderSource(id, numberOfLines, arraySource, NULL);
		glCompileShader(id);

		for (unsigned int indexLine = 0; indexLine != numberOfLines; indexLine++)
			delete[] arraySource[indexLine];

		delete[] arraySource;

		std::string errorText = "";
		if (this->m_wasThereACompileError(id, errorText))
		{
			std::stringstream ssError;
			ssError << "Shader compile error: ";
			ssError << errorText;
			error = ssError.str();
			return false;
		}
		return true;
	}
	bool OpenGLShader::m_wasThereACompileError(GLuint shaderID, std::string& errorText)
	{
		errorText = "";

		GLint isCompiled = 0;
		glGetShaderiv(shaderID, GL_COMPILE_STATUS, &isCompiled);
		if (isCompiled == GL_FALSE)
		{
			GLint maxLength = 0;
			glGetShaderiv(shaderID, GL_INFO_LOG_LENGTH, &maxLength);

			char* pLogText = new char[maxLength];
			glGetShaderInfoLog(shaderID, maxLength, &maxLength, pLogText);
			errorText.append(pLogText);

			this->m_LastError.append("\n");
			this->m_LastError.append(errorText);

			delete[] pLogText;
			return true;
		}
		return false;
	}
	bool OpenGLShader::m_wasThereALinkerError(GLuint progID, std::string& errorText)
	{
		errorText = "";

		GLint wasError = 0;
		glGetProgramiv(progID, GL_LINK_STATUS, &wasError);
		if (wasError == GL_FALSE)
		{
			GLint maxLength = 0;
			glGetProgramiv(progID, GL_INFO_LOG_LENGTH, &maxLength);

			char* pLogText = new char[maxLength];

			glGetProgramInfoLog(progID, maxLength, &maxLength, pLogText);
			errorText.append(pLogText);

			this->m_LastError.append("\n");
			this->m_LastError.append(errorText);

			delete[] pLogText;

			return true;
		}
		return false;
	}
}