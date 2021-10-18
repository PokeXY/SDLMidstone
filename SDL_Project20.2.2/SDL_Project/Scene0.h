#ifndef SCENE0_H
#define SCENE0_H

#include <SDL.h>
#include <vector>
#include "Scene.h"
#include "GameObject.h"
#include "PlayerCharacter.h"
#include "Bullet.h"
#include "Plane.h"

using namespace MATH;
struct MATH::Plane;

//Numbers of walls 
#define NUMWALL 16

class Scene0 : public Scene {
private:
	SDL_Window *window;
	Matrix4 projectionMatrix;
	SDL_Renderer* renderer;
	SDL_Surface* surfacePtr;
	SDL_Texture* texturePtr;
	SDL_Texture* background;
	SDL_Texture* croutonTexture;
	PlayerCharacter* player;

	std::vector<GameObject*> walls;
	std::vector<Bullet*> bullets;

	Plane* wallLeft; 
	Plane* wallRight; 
	Plane* wallTop; 
	Plane* wallBottom;

public:
	Scene0(SDL_Window* sdlWindow);
	~Scene0();
	bool OnCreate();
	void OnDestroy();
	void Update(const float time);
	void Render();
	void HandleEvents(const SDL_Event &sdlEvent );
};

#endif

