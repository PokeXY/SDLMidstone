#ifndef CHARACTER_H
#define CHARACTER_H

#include "GameObject.h"

class Character : public GameObject
{
protected:
	int health, maxHealth;
	bool isVisible, isActive;
	float moveSpeed;

public:
	Character();
	~Character();
};

#endif

