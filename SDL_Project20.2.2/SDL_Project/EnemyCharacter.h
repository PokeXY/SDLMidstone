#ifndef ENEMYCHARACTER_H
#define ENEMYCHARACTER_H

#include "Character.h"

class EnemyCharacter : public Character 
{
private:
	int enemyType;

	void dead();

public:
	EnemyCharacter();
	~EnemyCharacter();

	void seekPlayer(Vec3 playerLocation_);
};

#endif

