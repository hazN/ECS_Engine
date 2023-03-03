#pragma once
#include "../System.h"
#include "../Physic/Physic.h"

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
			void Init(std::vector<Entity*>* entities, Physic::Physic* phy_movement);
		private:
			Entity* controlEntity;
			Physic::Physic* phyic_movement;
		};
	}
}