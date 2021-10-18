#include "Character.h"

Character::Character() : health(0), maxHealth(0), isActive(0), isVisible(0)
{
}

Character::~Character()
{
}

bool Character::takeDamage(float damageAmount_) {
	health -= damageAmount_;
	if (health <= 0) {
		return false;
	}
	return true;
}


