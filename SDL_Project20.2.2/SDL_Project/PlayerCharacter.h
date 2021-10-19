#ifndef PLAYERCHARACTER_H
#define PLAYERCHARACTER_H

#include "Character.h"
#include "Bullet.h"

class PlayerCharacter : public Character
{
private:
	bool mouseDown;
	bool isInvincible;
	Vec3 lookDirection;
	int weaponType;

	void LookDirection(float x, float y);
	void dead();

public:
	PlayerCharacter();
	~PlayerCharacter();

	Bullet FireWeapon();
	bool restoreHealth(float healingAmount_);
	void HandleEvents(const SDL_Event& sdlEvent, const Matrix4 projectionMatrix);

	const bool getMouseDown() const { return mouseDown; }
	const Vec3 getLookDirection() const { return lookDirection; }
};

#endif
