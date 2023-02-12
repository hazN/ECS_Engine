#pragma once
#include <vector>
#include "../Entity.h"
#include "../System.h"
#include "../core/Renderer/VertexArray.h"
#include <memory>
#include <Renderer/Shader.h>

namespace sas
{
	namespace Systems
	{
		class Renderer : public System
		{
		public:
			Renderer();
			~Renderer();
			virtual void Process(const std::vector < Entity* >* entityList, float dt) override;
			void Init(std::vector<Entity*>* entityList, unsigned int shaderID);
		private:
			std::shared_ptr<Shader> m_Shader;
			std::shared_ptr<VertexArray> m_VertexArray;
		};
	}
}