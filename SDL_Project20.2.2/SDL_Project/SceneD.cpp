#include "SceneD.h"

#include <SDL.h>
#include "SDL_image.h"
#include "Randomizer.h"
#include "Physics.h"
#include <iostream>

SceneD::SceneD(SDL_Window* sdlWindow_) {
	window = sdlWindow_;
	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
	pressed = false;
}

SceneD::~SceneD() {// Rember to delete every pointer NO MEMORY LEAKS!!!!!!
	OnDestroy();
}

bool SceneD::OnCreate(float GOF) {
	int w, h;
	float xAxis = 32.0f;
	float yAxis = 18.0f;
	float zAxis = 1.0f;
	SDL_GetWindowSize(window, &w, &h);

	Matrix4 ndc = MMath::viewportNDC(w, h);
	Matrix4 ortho = MMath::orthographic(0.0f, xAxis, 0.0f, yAxis, 0.0f, zAxis);
	projectionMatrix = ndc * ortho;

	//temporary border walls

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
	
	surfacePtr = IMG_Load("Art/YouDied.png");
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

	

	


	return true;
}

void SceneD::OnDestroy() {
	SDL_DestroyRenderer(renderer);
}

void SceneD::Update(const float time) {

}

void SceneD::HandleEvents(const SDL_Event& sdlEvent) { //Make stuff happen here with the clickety clack
	if (sdlEvent.type == SDL_KEYDOWN || sdlEvent.type == SDL_EventType::SDL_MOUSEBUTTONDOWN) { //Move you to the menu when you press any key 
		pressed = true;
	}

}

void SceneD::Render() {
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
	SDL_Renderer* renderer = SDL_GetRenderer(window);
	//Clear screen
	SDL_RenderClear(renderer);


	SDL_Rect youDied;
	youDied.x = 310;
	youDied.y = 0;
	youDied.w = 720;
	youDied.h = 720;
	SDL_RenderCopy(renderer, texturePtr, nullptr, &youDied);


	//Update screen
	SDL_RenderPresent(renderer);


}

bool SceneD::getDead() {
	return pressed;
}