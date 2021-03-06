#ifndef CHARACTER_H
#define CHARACTER_H

#include "GameObject.h"

class Character : public GameObject
{
protected:
	float health, maxHealth;
	bool isVisible, isActive;
	float moveSpeed = 4.0f;

	virtual void dead();

public:
	Character();
	~Character();

	void takeDamage(float damageAmount_);

	float getHealth() { return health; }

	void setHealth(float h) { health = h; }
};

#endif

