#ifndef SCENEMENU_H
#define SCENEMENU_H

#include <SDL.h>
#include <vector>
#include "Scene.h"
#include "GameObject.h"
#include "PlayerCharacter.h"
#include "EnemyCharacter.h"
#include "Bullet.h"
#include "Plane.h"


using namespace MATH;
struct MATH::Plane;

class SceneMenu : public Scene {
private:
	SDL_Window* window;
	Matrix4 projectionMatrix;
	SDL_Renderer* renderer;
	SDL_Surface* surfacePtr;
	SDL_Texture* texturePtr;

	GameObject* player; //Not the player just a a guy jumping around the screen 

	bool play;



public:
	SceneMenu(SDL_Window* sdlWindow);
	~SceneMenu();
	bool OnCreate(float GOF);
	void OnDestroy();
	void Update(const float time);
	void Render();
	void HandleEvents(const SDL_Event& sdlEvent);
	bool getDead();
	bool nextScene() { return false; }\
	float getHealth() { return 0.0f; }
};

#endif
