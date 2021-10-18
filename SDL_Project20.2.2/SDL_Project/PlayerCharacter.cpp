#include "PlayerCharacter.h"
#include <SDL.h>

PlayerCharacter::PlayerCharacter() : mouseDown(0), isInvincible(0), weaponType(0), lookDirection(0.0f)
{
}

PlayerCharacter::~PlayerCharacter()
{
}

void PlayerCharacter::LookDirection(float x, float y) {
	lookDirection = Vec3(x, y, 0.0f);

	if (x > pos.x) {
		angle = -atan((y - pos.y) / (x - pos.x)) * 180 / M_PI;
	}
	else {
		angle = 180 - atan((y - pos.y) / (x - pos.x)) * 180 / M_PI;
	}
}

Bullet PlayerCharacter::FireWeapon() {
	Bullet bullet;
	//weaponType 0 is standard weapon, can add other types
	if (weaponType == 0) {	
		float velx = 10.0f * cos(angle * M_PI / 180);
		float vely = -10.0f * sin(angle * M_PI / 180);

		bullet.setPos(pos);
		bullet.setVel(Vec3(velx, vely, 0.0f));
		bullet.setRemainingBounces(3);
	}
	
	return bullet;
}

void PlayerCharacter::HandleEvents(const SDL_Event& sdlEvent, const Matrix4 projectionMatrix) {
	if (sdlEvent.type == SDL_KEYDOWN) {

		switch (sdlEvent.key.keysym.scancode) {

			case SDL_SCANCODE_W:
				vel = Vec3(0.0f, moveSpeed, 0.0f);
				break;

			case SDL_SCANCODE_A:
				vel = Vec3(-moveSpeed, 0.0f, 0.0f);
				break;

			case SDL_SCANCODE_S:
				vel = Vec3(0.0f, -moveSpeed, 0.0f);
				break;

			case SDL_SCANCODE_D:
				vel = Vec3(moveSpeed, 0.0f, 0.0f);
				break;

			default:
				break;
		}
	}

	if (sdlEvent.type == SDL_KEYUP) {
		vel = Vec3(0.0f);
	}

	if (sdlEvent.type == SDL_EventType::SDL_MOUSEMOTION) {
		Vec3 mousePosView = Vec3(sdlEvent.button.x, sdlEvent.button.y, 0.0f);
		Vec3 mousePosWorld = MMath::inverse(projectionMatrix) * mousePosView;
		LookDirection(mousePosWorld.x, mousePosWorld.y);
	}
}
