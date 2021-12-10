#ifndef PLAYERCHARACTER_H
#define PLAYERCHARACTER_H

#include "Character.h"
#include "Bullet.h"
#include <vector>

class PlayerCharacter : public Character
{
private:
	bool mouseDown;
	bool isInvincible;
	bool isDead;
	Vec3 lookDirection;
	int weaponType;
	bool altWeaponAvailable;

	void LookDirection(float x, float y);
	void dead();

	std::vector<Bullet*> newBullets;

public:
	PlayerCharacter();
	~PlayerCharacter();

	std::vector<Bullet*> FireWeapon();
	bool restoreHealth(float healingAmount_);
	void HandleEvents(const SDL_Event& sdlEvent, const Matrix4 projectionMatrix);

	const bool getMouseDown() const { return mouseDown; }
	const Vec3 getLookDirection() const { return lookDirection; }
	const void setAltWeaponAvailable(bool altWeaponAvailable_) { altWeaponAvailable = altWeaponAvailable_; }
	const void setWeaponType(int weaponType_) { weaponType = weaponType_; }
};

#endif
