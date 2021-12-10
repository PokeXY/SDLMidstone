#ifndef SCENE2_H
#define SCENE2_H

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

class Scene2 : public Scene {
private:
	SDL_Window* window;
	Matrix4 projectionMatrix;
	SDL_Renderer* renderer;
	SDL_Surface* surfacePtr;
	SDL_Texture* texturePtr;
	SDL_Texture* background;
	SDL_Texture* croutonTexture;
	SDL_Texture* health;
	//SDL_Texture* health1;
	//SDL_Texture* health2;

	PlayerCharacter* player;
	BossCharacter* boss;



	Level* level;

	//std::vector<Wall*> walls;
	std::vector<Bullet*> bullets;
	std::vector<EnemyCharacter*> enemies;



	Plane* wallLeft;
	Plane* wallRight;
	Plane* wallTop;
	Plane* wallBottom;

	bool nextS;

public:
	Scene2(SDL_Window* sdlWindow);
	~Scene2();
	bool OnCreate(float GOF);
	void OnDestroy();
	void Update(const float time);
	void Render();
	void HandleEvents(const SDL_Event& sdlEvent);
	bool getDead();
	bool nextScene();
	float getHealth() { return player->getHealth(); }

};

#endif
