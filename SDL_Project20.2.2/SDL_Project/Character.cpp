#include "Character.h"

Character::Character() : health(0), maxHealth(0), isActive(0), isVisible(0)
{
}

Character::~Character()
{
}

void Character::takeDamage(float damageAmount_) {
	health -= damageAmount_;
	if (health <= 0) {
		//call a function for player death
	}
	//potentially add brief invulnerability and other effects when hit
}

bool Character::restoreHealth(float healingAmount_) {
	bool destroyHealthPickup;	//if player full on health, keep health pickup on ground
	if (health == maxHealth) {
		destroyHealthPickup = false;
	}
	else {
		health += healingAmount_;
		if (health > maxHealth) {
			health = maxHealth;
		}
		destroyHealthPickup = true;
	}

	return destroyHealthPickup;

}
