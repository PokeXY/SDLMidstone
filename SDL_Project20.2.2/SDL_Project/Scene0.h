#ifndef SCENE0_H
#define SCENE0_H
#include "Body.h"
#include "MMath.h"
#include "Scene.h"
#include <SDL.h>
#include "Wall.h"

using namespace MATH;
//Numbers of walls 
#define NUMWALL 30

class Scene0 : public Scene {
private:
	SDL_Window *window;
	Matrix4 projectionMatrix;
	SDL_Renderer* renderer;
	Body* backGround;
	Wall* wall[NUMWALL];

	
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

