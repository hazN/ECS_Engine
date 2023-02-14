#pragma once
#include "../Renderer/Shader.h"
#include <glm/glm.hpp>
#include <glad/glad.h>
#include <vector>

namespace sas
{
	// OpenGL specific Shader
	class OpenGLShader : public Shader
	{
	public:
		// Create shader from given files
		OpenGLShader(const std::string& vertexShaderFile, const std::string& fragmentShaderFile);
		virtual ~OpenGLShader();

		// Use opengl Shader
		virtual void Bind() const override;

		// Do not use any shader
		virtual void UnBind() const override;

		// Upload one Integer value to shader
		void UploadUniformInt(const std::string& uniformName, int value);
		
		// Upload one Float value to shader
		void UploadUniformFloat(const std::string& uniformName, float value);

		// Upload two Float values to shader
		void UploadUniformFloat2(const std::string& uniformName, const glm::vec2& values);

		// Upload three Float values to shader
		void UploadUniformFloat3(const std::string& uniformName, const glm::vec3& values);

		// Upload four Float values to shader
		void UploadUniformFloat4(const std::string& uniformName, const glm::vec4& values);

		// Upload 3 x 3 matrix to shader
		void UploadUniformMat3(const std::string& uniformName, const glm::mat3& matrix);

		// Upload 4 x 4 matrix to shader
		void UploadUniformMat4(const std::string& uniformName, const glm::mat4& matrix);

		// Returns opengl shader ID
		inline const uint32_t GetID() { return m_RendererID; }
	private:
		// Create shaders from given files
		bool Init(const std::string& vertexShaderFile, const std::string& fragmentShaderFile);

		// Read the file and save the lines into the vector
		bool m_loadSourceFromFile(std::string fileName, std::vector<std::string>* srcVector);
		std::string m_basepath;

		// Compile the shader from the vector of string
		bool m_compileShaderFromSource(std::vector<std::string>* srcVector,GLuint id, std::string& error);

		// Check for compilation error (For vertex shader and fragment shader)
		bool m_wasThereACompileError(GLuint shaderID, std::string& errorText);

		// Check for linking error (For shader program)
		bool m_wasThereALinkerError(GLuint progID, std::string& errorText);

	private:
		uint32_t m_RendererID;
		std::string m_LastError;
	};
}