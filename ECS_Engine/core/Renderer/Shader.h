#pragma once
#include <string>
#include <memory>

namespace sas
{
	// Shader parent class
	class Shader
	{
	public:
		virtual ~Shader() = default;

		// Use Shader
		virtual void Bind() const = 0;

		// Stop using shader
		virtual void UnBind() const = 0;

		// Create API specific shader object
		static std::shared_ptr<Shader> Create(const std::string& vertexShaderFile, const std::string& fragmentShaderFile);
	};
}