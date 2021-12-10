#include "SceneMenu.h"


#include <SDL.h>
#include "SDL_image.h"
#include "Randomizer.h"
#include "Physics.h"
#include <iostream>

SceneMenu::SceneMenu(SDL_Window* sdlWindow_) {
	window = sdlWindow_;
	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
	play = false;
}

SceneMenu::~SceneMenu() {// Rember to delete every pointer NO MEMORY LEAKS!!!!!!
	OnDestroy();
}

bool SceneMenu::OnCreate(float GOF) {
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

	surfacePtr = IMG_Load("Art/BreadMenu.png");
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

void SceneMenu::OnDestroy() {
	SDL_DestroyRenderer(renderer);
}

void SceneMenu::Update(const float time) {

}

void SceneMenu::HandleEvents(const SDL_Event& sdlEvent) { //Make stuff happen here with the clickety clack
	Vec3 mousePosView = Vec3(sdlEvent.button.x, sdlEvent.button.y, 0.0f);
	Vec3 mousePosWorld = MMath::inverse(projectionMatrix) * mousePosView;
	//This is the play button it'll load scene zero
	if (sdlEvent.type == SDL_EventType::SDL_MOUSEBUTTONDOWN  && 12 < mousePosWorld.x && mousePosWorld.x < 19 && 7 < mousePosWorld.y && mousePosWorld.y < 10) {
		play = true;

	}
	//This is the exit button which will exit and quit the game
	else if (sdlEvent.type == SDL_EventType::SDL_MOUSEBUTTONDOWN  && 12 < mousePosWorld.x && mousePosWorld.x < 19 && 2.5 < mousePosWorld.y && mousePosWorld.y < 5) {
		std::cout << mousePosWorld.x << "  ,  " << mousePosWorld.y << std::endl;
		SDL_Event sdlevent;
		sdlevent.type = SDL_QUIT;
		SDL_PushEvent(&sdlevent);
	}
	
}

void SceneMenu::Render() {
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

bool SceneMenu::getDead() {
	
	return play;
}