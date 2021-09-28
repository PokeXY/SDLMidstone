#ifndef CHARACTER_H
#define CHARACTER_H

#include "GameObject.h"

class Character : public GameObject
{
protected:
	int health, maxHealth;
	bool isVisible, isActive;
	float moveSpeed = 4.0f;

public:
	Character();
	~Character();
};

#endif

