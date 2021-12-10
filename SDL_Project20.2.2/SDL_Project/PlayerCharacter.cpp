#include "PlayerCharacter.h"
#include <SDL.h>

PlayerCharacter::PlayerCharacter() : mouseDown(0), isInvincible(0), weaponType(0), lookDirection(0.0f), isDead(0), altWeaponAvailable(0)
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

std::vector<Bullet*> PlayerCharacter::FireWeapon() {
	newBullets.clear();

	//weaponType 0 is standard weapon, can add other types
	if (weaponType == 0) {	
		float velx = 10.0f * cos(angle * M_PI / 180);
		float vely = -10.0f * sin(angle * M_PI / 180);

		newBullets.push_back(new Bullet);
		newBullets[0]->setBoundingSphere(Sphere(0.25f));

		float offsetx = 0.01 + (boundingSphere.r + newBullets[0]->getBoundingSphere().r) * cos(angle * M_PI / 180);
		float offsety = 0.01 + (boundingSphere.r + newBullets[0]->getBoundingSphere().r) * sin(angle * M_PI / 180);

		newBullets[0]->setPos(Vec3(pos.x + offsetx, pos.y - offsety, 0.0f));
		newBullets[0]->setVel(Vec3(velx, vely, 0.0f));
		
		newBullets[0]->setRemainingBounces(3);
	}
	//weaponType 1 is shotgun
	if (weaponType == 1) {
		for (int i = 0; i < 3; ++i) {
			newBullets.push_back(new Bullet);
			newBullets[i]->setBoundingSphere(Sphere(0.25f));

			if (i == 1) { angle += 15; }
			if (i == 2) { angle -= 30; }

			float velx = 5.0f * cos(angle * M_PI / 180);
			float vely = -5.0f * sin(angle * M_PI / 180);

			float offsetx = 0.01 + (boundingSphere.r + newBullets[i]->getBoundingSphere().r) * cos(angle * M_PI / 180);
			float offsety = 0.01 + (boundingSphere.r + newBullets[i]->getBoundingSphere().r) * sin(angle * M_PI / 180);

			newBullets[i]->setPos(Vec3(pos.x + offsetx, pos.y - offsety, 0.0f));
			newBullets[i]->setVel(Vec3(velx, vely, 0.0f));

			newBullets[i]->setRemainingBounces(0);
		}
	}
	
	return newBullets;
}

bool PlayerCharacter::restoreHealth(float healingAmount_) {
	bool destroyHealthPickup;	//if player full on health, keep health pickup on ground
	if (health == maxHealth) {
		destroyHealthPickup = false;
	}
	else {
		health += healingAmount_;
		if (health > maxHealth) {
			health = maxHealth;
		}
		destroyHealthPickup = true;
	}

	return destroyHealthPickup;
}

void PlayerCharacter::dead() {
	isDead = true;
	printf("You Died\n");
};

void PlayerCharacter::HandleEvents(const SDL_Event& sdlEvent, const Matrix4 projectionMatrix) {
	if (sdlEvent.type == SDL_KEYDOWN) {
		if (sdlEvent.key.keysym.scancode == SDL_SCANCODE_W) {
			vel.y = moveSpeed;
		}
		if (sdlEvent.key.keysym.scancode == SDL_SCANCODE_A) {
			vel.x = -moveSpeed;
		}
		if (sdlEvent.key.keysym.scancode == SDL_SCANCODE_S) {
			vel.y = -moveSpeed;
		}
		if (sdlEvent.key.keysym.scancode == SDL_SCANCODE_D) {
			vel.x = moveSpeed;
		}
	}

	if (sdlEvent.type == SDL_KEYUP) {
		if (sdlEvent.key.keysym.scancode == SDL_SCANCODE_W) {
			if (vel.y > 0.0f) {
				vel.y = 0.0f;
			}
		}
		if (sdlEvent.key.keysym.scancode == SDL_SCANCODE_A) {
			if (vel.x < 0.0f) {
				vel.x = 0.0f;
			}
		}
		if (sdlEvent.key.keysym.scancode == SDL_SCANCODE_S) {
			if (vel.y < 0.0f) {
				vel.y = 0.0f;
			}
		}
		if (sdlEvent.key.keysym.scancode == SDL_SCANCODE_D) {
			if (vel.x > 0.0f) {
				vel.x = 0.0f;
			}
		}
	}

	/*
	if (sdlEvent.type == SDL_KEYDOWN) {

		switch (sdlEvent.key.keysym.scancode) {

			case SDL_SCANCODE_W:
				//pos.y += moveSpeed;
				vel = Vec3(0.0f, moveSpeed, 0.0f);
				break;

			case SDL_SCANCODE_A:
				//pos.x += -moveSpeed;
				vel = Vec3(-moveSpeed, 0.0f, 0.0f);
				break;

			case SDL_SCANCODE_S:
				//pos.y += -moveSpeed;
				vel = Vec3(0.0f, -moveSpeed, 0.0f);
				break;

			case SDL_SCANCODE_D:
				//pos.x += moveSpeed;
				vel = Vec3(moveSpeed, 0.0f, 0.0f);
				break;

			default:
				break;
		}
	}

	if (sdlEvent.type == SDL_KEYUP) {
		vel = Vec3(0.0f);
	}*/

	if (sdlEvent.type == SDL_EventType::SDL_MOUSEMOTION) {
		Vec3 mousePosView = Vec3(sdlEvent.button.x, sdlEvent.button.y, 0.0f);
		Vec3 mousePosWorld = MMath::inverse(projectionMatrix) * mousePosView;
		LookDirection(mousePosWorld.x, mousePosWorld.y);
	}
}
