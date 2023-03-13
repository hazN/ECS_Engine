#include "Health.h"

namespace sas {

	// Method : Health
	// Summary: Constructor for Health, set currenthp and maxhp
	// Accepts: int curHP, int maxHP
	Health::Health(int curHP, int maxHP)
	{
		this->currentHP = curHP;
		this->maxHP = maxHP;
	}
	// Method : DealDamage
	// Summary: Deal damage with given int, returns TRUE if the health is below 0
	//			and false if the health is still above 0
	// Accepts: int dmg
	bool Health::DealDamage(int dmg)
	{
		currentHP -= dmg;
		if (currentHP <= 0)
			return true;
		return false;
	}
	// Method : GetHP
	// Summary: Returns HP
	int Health::GetHP()
	{
		return currentHP;
	}
	void Health::Update(float dt)
	{
		// TODO
	}
}