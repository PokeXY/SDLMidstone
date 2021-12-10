#include "Character.h"

void Character::dead()
{
}

Character::Character() : health(3.0f), maxHealth(3.0f), isActive(0), isVisible(0)
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


