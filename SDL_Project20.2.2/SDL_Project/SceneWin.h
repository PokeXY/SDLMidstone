#ifndef SCENEWWIN_H
#define SCENEWIN_H

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

class SceneWin : public Scene {
private:
	SDL_Window* window;
	Matrix4 projectionMatrix;
	SDL_Renderer* renderer;
	SDL_Surface* surfacePtr;
	SDL_Texture* texturePtr;
	int wait;
	bool pressed;


public:
	SceneWin(SDL_Window* sdlWindow);
	~SceneWin();
	bool OnCreate();
	void OnDestroy();
	void Update(const float time);
	void Render();
	void HandleEvents(const SDL_Event& sdlEvent);
	bool getDead();
	bool nextScene() { return false; }
};

#endif


