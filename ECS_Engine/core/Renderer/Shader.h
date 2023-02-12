#pragma once
#include <string>
#include <memory>

namespace sas
{
	class Shader
	{
	public:
		virtual ~Shader() = default;

		virtual void Bind() const = 0;
		virtual void UnBind() const = 0;

		static std::shared_ptr<Shader> Create(const std::string& vertexShaderFile, const std::string& fragmentShaderFile);
	};
}