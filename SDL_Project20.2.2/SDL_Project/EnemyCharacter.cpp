#include "EnemyCharacter.h"

EnemyCharacter::EnemyCharacter() : enemyType(0)
{
}

EnemyCharacter::~EnemyCharacter()
{
}

void EnemyCharacter::seekPlayer(Vec3 playerLocation_) {
	Vec3 enemyToPlayer = playerLocation_ - pos;
	int signx;
	int signy;

	if (signbit(enemyToPlayer.x) == 1) {
		signx = -1;
	}
	else {
		signx = 1;
	}

	if (signbit(enemyToPlayer.y) == 1) {
		signy = -1;
	}
	else {
		signy = 1;
	}
	
	if (fabs(enemyToPlayer.x) > 2 * fabs(enemyToPlayer.y)) {
		vel = Vec3(signx * moveSpeed, 0.0f, 0.0f);
	}
	else if (fabs(enemyToPlayer.y) > 2 * fabs(enemyToPlayer.x)) {
		vel = Vec3(0.0f, signy * moveSpeed, 0.0f);
	}
	else {
		vel = Vec3(signx * moveSpeed, signy * moveSpeed, 0.0f);
	}

}

void EnemyCharacter::dead() {
	printf("Enemy killed \n");

}

void EnemyCharacter::projectile()
{

}

