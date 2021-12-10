#ifndef SCENED_H
#define SCENED_H

#include <SDL.h>
#include <vector>
#include "Scene.h"
#include "GameObject.h"
#include "PlayerCharacter.h"
#include "EnemyCharacter.h"
#include "Bullet.h"
#include "Plane.h"
#include "Level.h"
#include "BossCharacter.h"

using namespace MATH;
struct MATH::Plane;

class SceneD : public Scene {
private:
	SDL_Window* window;
	Matrix4 projectionMatrix;
	SDL_Renderer* renderer;
	SDL_Surface* surfacePtr;
	SDL_Texture* texturePtr;
	SDL_Texture* background;
	bool pressed;
	

public:
	SceneD(SDL_Window* sdlWindow);
	~SceneD();
	bool OnCreate(float GOF);
	void OnDestroy();
	void Update(const float time);
	void Render();
	void HandleEvents(const SDL_Event& sdlEvent);
	bool getDead();
	bool nextScene() { return false; }
	float getHealth() { return 0.0f; }

};

#endif


