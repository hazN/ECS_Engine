#pragma once
#include "../Renderer/Shader.h"
#include <glm/glm.hpp>
#include <glad/glad.h>
#include <vector>

namespace sas
{
	class OpenGLShader : public Shader
	{
	public:
		OpenGLShader(const std::string& vertexShaderFile, const std::string& fragmentShaderFile);
		virtual ~OpenGLShader();
		virtual void Bind() const override;
		virtual void UnBind() const override;

		void UploadUniformInt(const std::string& uniformName, int value);

		void UploadUniformFloat(const std::string& uniformName, float value);
		void UploadUniformFloat2(const std::string& uniformName, const glm::vec2& values);
		void UploadUniformFloat3(const std::string& uniformName, const glm::vec3& values);
		void UploadUniformFloat4(const std::string& uniformName, const glm::vec4& values);

		void UploadUniformMat3(const std::string& uniformName, const glm::mat3& matrix);
		void UploadUniformMat4(const std::string& uniformName, const glm::mat4& matrix);


		inline const uint32_t GetID() { return m_RendererID; }
	private:
		bool Init(const std::string& vertexShaderFile, const std::string& fragmentShaderFile);
		bool m_loadSourceFromFile(std::string fileName, std::vector<std::string>* srcVector);
		std::string m_basepath;

		bool m_compileShaderFromSource(std::vector<std::string>* srcVector,GLuint id, std::string& error);
		bool m_wasThereACompileError(GLuint shaderID, std::string& errorText);
		bool m_wasThereALinkerError(GLuint progID, std::string& errorText);

	private:
		uint32_t m_RendererID;
		std::string m_LastError;
	};
}