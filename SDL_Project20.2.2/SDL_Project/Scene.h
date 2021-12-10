#ifndef SCENE_H
#define SCENE_H
#include <SDL.h>
class Scene {
public:
	virtual bool OnCreate(float GOF) = 0;
	virtual void OnDestroy() = 0;
	virtual void Update(const float time) = 0;
	virtual void Render() = 0;
	virtual void HandleEvents(const SDL_Event& sdlEvent) = 0;
	virtual bool getDead() = 0; //To check if you're dead
	virtual bool nextScene() = 0; //Check if to load next scene
	virtual float getHealth() = 0; //Get the player health
};
#endif
