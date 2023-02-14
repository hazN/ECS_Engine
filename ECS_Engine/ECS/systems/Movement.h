#pragma once
#include "../System.h"

namespace sas
{
	namespace Systems
	{
		// Move object
		class Movement : public System
		{
		public:
			Movement();
			~Movement();

			// Check for input and move the object
			virtual void Process(const std::vector < Entity* >* entites, float dt) override;

			// Get the object
			void Init(std::vector<Entity*>* entities);
		private:
			Entity* controlEntity;
		};
	}
}