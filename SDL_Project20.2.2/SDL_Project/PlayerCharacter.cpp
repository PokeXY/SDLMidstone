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
}

void PlayerCharacter::FireWeapon() {
	//launch bullet and stuff
}

void PlayerCharacter::HandleEvents(const SDL_Event& sdlEvent) {
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
		LookDirection(sdlEvent.button.x, sdlEvent.button.y);
	}

	if (sdlEvent.type == SDL_EventType::SDL_MOUSEBUTTONDOWN) {
		FireWeapon();
	}
}
