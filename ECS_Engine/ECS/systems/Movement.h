#pragma once
#include "../System.h"

namespace sas
{
	namespace Systems
	{
		class Movement : public System
		{
		public:
			Movement();
			~Movement();
			virtual void Process(const std::vector < Entity* >* entites, float dt) override;
			void Init(std::vector<Entity*>* entities);
		private:
			Entity* controlEntity;
		};
	}
}