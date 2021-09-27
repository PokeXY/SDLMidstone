#ifndef PLAYERCHARACTER_H
#define PLAYERCHARACTER_H

#include "Character.h"

class PlayerCharacter : public Character
{
private:
	bool mouseDown;
	bool isInvincible;
	Vec3 lookDirection;
	int weaponType;

	void LookDirection(float x, float y);
	void FireWeapon();

public:
	PlayerCharacter();
	~PlayerCharacter();

	void HandleEvents(const SDL_Event& sdlEvent);

	const bool getMouseDown() const { return mouseDown; }
	const Vec3 getLookDirection() const { return lookDirection; }
};

#endif
