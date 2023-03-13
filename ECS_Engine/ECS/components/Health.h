#pragma once
#include <string>
#include "../Component.h"


namespace sas
{
	// Health Component
	class Health : public Component
	{
	public:
		Health();
		Health(int curHP, int maxHP);
		virtual ~Health() = default;
		bool Enabled;
		bool DealDamage(int dmg);
		int GetHP();
		void Update(float dt);
	private:
		int currentHP = 100;
		int maxHP = 100;
	};
}