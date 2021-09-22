#include "Scene0.h"
#include <SDL.h>
#include "SDL_image.h"
#include "Randomizer.h"
#include <iostream>


Scene0::Scene0(SDL_Window* sdlWindow_){
	window = sdlWindow_;
	renderer = SDL_CreateRenderer(window, -1,SDL_RENDERER_ACCELERATED);
	backGround = new Body(Vec3(0.0f,15.0f,0.0f ),Vec3(),Vec3(), 1.0f);
	float xpos = 0.0;
	for (int i = 0; i < NUMWALL; ++i) {
		wall[i] = new Wall(Vec3(xpos, 15.0f, 0.0f));
		xpos++;
	}
	
}

Scene0::~Scene0(){// Rember to delete every pointer NO MEMORY LEAKS!!!!!!
	for (int i = 0; i < NUMWALL; ++i) {
		delete wall[i];
	}
	delete backGround;
	SDL_DestroyRenderer(renderer);
}

bool Scene0::OnCreate() {
	int w, h;
	float xAxis = 30.0f;
	float yAxis = 15.0f;
	float zAxis = 1.0f;
	SDL_GetWindowSize(window,&w,&h);
	
	Matrix4 ndc = MMath::viewportNDC(w, h);
	Matrix4 ortho = MMath::orthographic(0.0, xAxis, 0.0, yAxis, 0.0, zAxis);
	projectionMatrix = ndc * ortho;
	


	IMG_Init(IMG_INIT_PNG); //Make loading PNGs easer so only use PNGs
	//Load the Back ground image and set the texture as well
	SDL_Surface* bgImage = IMG_Load("Art/bgSample.png");
	SDL_Texture* bgTexture = SDL_CreateTextureFromSurface(renderer,bgImage);
	if (bgTexture == nullptr) printf("%s\n", SDL_GetError());
	if (bgImage == nullptr) {
		std::cerr << "Imgage does not work" << std::endl;
	}
	else {
		Vec3 wcfsc;
		wcfsc.x = xAxis / static_cast<float>(w) * static_cast<float>(bgImage->w);
		wcfsc.y = yAxis / static_cast<float>(h) * static_cast<float>(bgImage->h);
		backGround->setTexture(bgTexture);
		backGround->setImageSizeWorldCoords(wcfsc);
		SDL_FreeSurface(bgImage);
		
	}

	//Loads in the wall image and set the texture to the walls
	SDL_Surface* wallImage = IMG_Load("Art/Wall02.png");
	SDL_Texture* wallTexture = SDL_CreateTextureFromSurface(renderer, wallImage);
	if (wallTexture == nullptr) printf("%s\n", SDL_GetError());
	if (wallImage == nullptr) {
		std::cerr << "Imgage does not work" << std::endl;
	}
	else {
		Vec3 wallcfsc;
		wallcfsc.x = xAxis / static_cast<float>(w) * static_cast<float>(wallImage->w);
		wallcfsc.y = yAxis / static_cast<float>(h) * static_cast<float>(wallImage->h);
		for (int i = 0; i < NUMWALL; i++) {
			wall[i]->setTexture(wallTexture);
			wall[i]->setImageSizeWorldCoords(wallcfsc);
		}
		SDL_FreeSurface(wallImage);

	}

	return true;
}

void Scene0::OnDestroy() {  

	
	SDL_DestroyRenderer(renderer);
}

void Scene0::Update(const float time) {
	/// This is the physics in the x and y dimension don't mess with z
	
}

void Scene0::HandleEvents(const SDL_Event& sdlEvent) {
	//Make stuff happen here with the clickety clack
	
}

void Scene0::Render() {
	SDL_SetRenderDrawColor(renderer, 0,0,0,0);
	SDL_Renderer* renderer = SDL_GetRenderer(window);
	//Clear screen
	SDL_RenderClear(renderer);
	
	//Draws the back ground
	Vec3 bgScreenCoords;
	SDL_Rect bg;
	bgScreenCoords = projectionMatrix * backGround->getPos();
	bg.x = static_cast<int> (bgScreenCoords.x);
	bg.y = static_cast<int> (bgScreenCoords.y);
	bg.w = 1280;
	bg.h = 720;
	SDL_RenderCopy(renderer, backGround->getTexture(), nullptr, &bg);

	//Draws all the walls
	Vec3 wallScreenCoords;
	int WallW, WallH;
	SDL_Rect WallRect;
	for (int i = 0; i < NUMWALL; ++i) {
		SDL_QueryTexture(wall[i]->getTexture(), nullptr, nullptr, &WallW, &WallH);
		wallScreenCoords = projectionMatrix * wall[i]->getPos();
		WallRect.x = static_cast<int> (wallScreenCoords.x);
		WallRect.y = static_cast<int> (wallScreenCoords.y);
		WallRect.w = WallW*2;
		WallRect.h = WallH*2;
		SDL_RenderCopy(renderer, wall[i]->getTexture(), nullptr, &WallRect);


	}
	
	
	//Update screen
	SDL_RenderPresent(renderer);

	
}