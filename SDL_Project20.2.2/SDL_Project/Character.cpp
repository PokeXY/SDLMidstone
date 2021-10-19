#include "Character.h"

void Character::dead()
{
}

Character::Character() : health(3), maxHealth(3), isActive(0), isVisible(0)
{
}

Character::~Character()
{
}

void Character::takeDamage(float damageAmount_) {
	health -= damageAmount_;
	if (health <= 0) {
		dead();
	}
}


