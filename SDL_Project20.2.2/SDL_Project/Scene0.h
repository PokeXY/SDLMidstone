#ifndef SCENE0_H
#define SCENE0_H

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

//Numbers of walls 
#define NUMWALL 58

class Scene0 : public Scene {
private:
	SDL_Window *window;
	Matrix4 projectionMatrix;
	SDL_Renderer* renderer;
	SDL_Surface* surfacePtr;
	SDL_Texture* texturePtr;
	SDL_Texture* background;
	SDL_Texture* croutonTexture;
	SDL_Texture* health;
	
	PlayerCharacter* player;
	BossCharacter* boss;

	//Health* health; // if need to create a health class
	
	Level* level;

	//std::vector<Wall*> walls;
	std::vector<Bullet*> bullets;
	std::vector<EnemyCharacter*> enemies;


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

