#ifndef SCENE0_H
#define SCENE0_H

#include <SDL.h>
#include <vector>
#include "Scene.h"
#include "GameObject.h"
#include "PlayerCharacter.h"

using namespace MATH;
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
	PlayerCharacter* player;

	std::vector<GameObject*> walls;

	
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

