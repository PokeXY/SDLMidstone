#include "Scene0.h"
#include <SDL.h>
#include "SDL_image.h"
#include "Randomizer.h"
#include "Physics.h"
#include <iostream>


Scene0::Scene0(SDL_Window* sdlWindow_){
	window = sdlWindow_;
	renderer = SDL_CreateRenderer(window, -1,SDL_RENDERER_ACCELERATED);
}

Scene0::~Scene0(){// Rember to delete every pointer NO MEMORY LEAKS!!!!!!
	if (surfacePtr) delete surfacePtr, surfacePtr = nullptr;
	if (texturePtr) delete texturePtr, texturePtr = nullptr;
	if (player) delete player, player = nullptr;
	
	for (GameObject* GameObject : walls) {
		delete GameObject;
	}
	SDL_DestroyRenderer(renderer);
}

bool Scene0::OnCreate() {
	int w, h;
	float xAxis = 32.0f;
	float yAxis = 18.0f;
	float zAxis = 1.0f;
	SDL_GetWindowSize(window,&w,&h);
	
	Matrix4 ndc = MMath::viewportNDC(w, h);
	Matrix4 ortho = MMath::orthographic(0.0f, xAxis, 0.0f, yAxis, 0.0f, zAxis);
	projectionMatrix = ndc * ortho;
	


	IMG_Init(IMG_INIT_PNG); //Make loading PNGs easer so only use PNGs
	//Load the Back ground image and set the texture as well
	surfacePtr = IMG_Load("Art/bgSample.png");
	background = SDL_CreateTextureFromSurface(renderer, surfacePtr);
	
	if (surfacePtr == nullptr) {
		std::cerr << "Imgage does not work" << std::endl;
		return false;
	}
	if (background == nullptr) {
		printf("%s\n", SDL_GetError());
		return false;
	}

	SDL_FreeSurface(surfacePtr);
	

	//Loads in the wall image and set the texture to the walls
	surfacePtr = IMG_Load("Art/Wall02.png");
	texturePtr = SDL_CreateTextureFromSurface(renderer, surfacePtr);

	if (surfacePtr == nullptr) {
		std::cerr << "Imgage does not work" << std::endl;
		return false;
	}
	if (texturePtr == nullptr) {
		printf("%s\n", SDL_GetError());
		return false;
	}

	SDL_FreeSurface(surfacePtr);

	float xpos = 0.0;
	for (int i = 0; i < NUMWALL; ++i) {
		walls.push_back(new GameObject(texturePtr));
		walls[i]->setPos(Vec3(xpos, 18.0f, 0.0f));
		xpos +=2;
	}

	//load player character
	surfacePtr = IMG_Load("Art/flappybird1.png");
	texturePtr = SDL_CreateTextureFromSurface(renderer, surfacePtr);

	if (surfacePtr == nullptr) {
		std::cerr << "Imgage does not work" << std::endl;
		return false;
	}
	if (texturePtr == nullptr) {
		printf("%s\n", SDL_GetError());
		return false;
	}

	SDL_FreeSurface(surfacePtr);

	player = new PlayerCharacter();
	player->setPos(Vec3(5.0f, 5.0f, 0.0f));
	player->setTexture(texturePtr);


	return true;
}

void Scene0::OnDestroy() {  
}

void Scene0::Update(const float time) {
	/// This is the physics in the x and y dimension don't mess with z
	Physics::SimpleNewtonMotion(*player, time);
}

void Scene0::HandleEvents(const SDL_Event& sdlEvent) {
	//Make stuff happen here with the clickety clack
	player->HandleEvents(sdlEvent);
}

void Scene0::Render() {
	SDL_SetRenderDrawColor(renderer, 0,0,0,0);
	SDL_Renderer* renderer = SDL_GetRenderer(window);
	//Clear screen
	SDL_RenderClear(renderer);
	
	//Draws the back ground
	SDL_Rect bg;
	bg.x = 0;
	bg.y = 0;
	bg.w = 1280;
	bg.h = 720;
	SDL_RenderCopy(renderer, background, nullptr, &bg);

	//Draws all the walls
	SDL_Rect WallRect;
	Vec3 wallScreenCoords;
	int WallW, WallH;

	for (int i = 0; i < NUMWALL; ++i) {
		SDL_QueryTexture(walls[i]->getTexture(), nullptr, nullptr, &WallW, &WallH);
		wallScreenCoords = projectionMatrix * walls[i]->getPos();
		WallRect.x = static_cast<int> (wallScreenCoords.x);
		WallRect.y = static_cast<int> (wallScreenCoords.y);
		WallRect.w = 80;
		WallRect.h = 80;
		SDL_RenderCopy(renderer, walls[i]->getTexture(), nullptr, &WallRect);
	}
	
	//Draw player
	SDL_Rect playerRect;
	Vec3 playerScreenCoords;
	int playerW, playerH;

	SDL_QueryTexture(player->getTexture(), nullptr, nullptr, &playerW, &playerH);
	playerScreenCoords = projectionMatrix * player->getPos();
	playerRect.x = static_cast<int> (playerScreenCoords.x);
	playerRect.y = static_cast<int> (playerScreenCoords.y);
	playerRect.w = playerW * 2;
	playerRect.h = playerH * 2;
	SDL_RenderCopy(renderer, player->getTexture(), nullptr, &playerRect);

	//Update screen
	SDL_RenderPresent(renderer);

	
}