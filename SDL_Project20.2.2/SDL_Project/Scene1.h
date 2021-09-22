#ifndef SCENE1_H
#define SCENE1_H

#include "MMath.h"
#include "Scene.h"
#include <SDL.h>
#include"Bird.h"
#include"Ball.h"

#define NUME 1
#define NUMEE 2
using namespace MATH;
class Scene1 : public Scene {
private:
	SDL_Window* window;
	Matrix4 projectionMatrix;
	SDL_Renderer* ren;
	Bird* bird[NUME];
	Ball* Wall;


public:
	
	
	Scene1(SDL_Window* sdlWindow);
	~Scene1();
	bool OnCreate();
	void OnDestroy();
	void Update(const float time);
	void Render();
	void HandleEvents(const SDL_Event& sdlEvent);
};

#endif
