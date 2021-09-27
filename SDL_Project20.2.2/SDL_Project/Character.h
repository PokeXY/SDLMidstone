#ifndef CHARACTER_H
#define CHARACTER_H

#include "Body.h"

class Character : public Body
{
protected:
	int health, maxHealth;
	bool isVisible, isActive;

public:
	Character();
	~Character();
};

#endif

