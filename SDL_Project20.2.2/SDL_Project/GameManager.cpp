#include "GameManager.h"
#include "Window.h"
#include "Timer.h"
#include "Scene0.h"

#include <iostream>

GameManager::GameManager() {
	windowPtr = nullptr;
	timer = nullptr;
	isRunning = true;
	currentScene = nullptr;
}


/// In this OnCreate() method, fuction, subroutine, whatever the word, 
bool GameManager::OnCreate() {
	const int SCREEN_WIDTH = 1280;
	const int SCREEN_HEIGHT = 720;
	windowPtr = new Window(SCREEN_WIDTH, SCREEN_HEIGHT);
	if (windowPtr == nullptr) {
		OnDestroy();
		return false;
	}
	if (windowPtr->OnCreate() == false) {
		OnDestroy();
		return false;
	}

	timer = new Timer();
	if (timer == nullptr) {
		OnDestroy();
		return false;
	}
	if (currentScene == nullptr) {
		currentScene = new Scene0(windowPtr->GetSDL_Window());
	}

	if (currentScene == nullptr) {
		OnDestroy();
		return false;
	}

	if (currentScene->OnCreate() == false) {
		OnDestroy();
		return false;
	}

	return true;
}

/// Here's the whole game
void GameManager::Run() {
	SDL_Event sdlEvent;
	timer->Start();
	while (isRunning) {
		
		while (SDL_PollEvent(&sdlEvent)) {
			currentScene->HandleEvents(sdlEvent);
			if (sdlEvent.type == SDL_QUIT) {
				isRunning = false;

			}
			else if (sdlEvent.type == SDL_KEYDOWN) {
				switch (sdlEvent.key.keysym.scancode) {
				case SDL_SCANCODE_ESCAPE:
					isRunning = false;
					break;
				/*case SDL_SCANCODE_F1:
					currentScene->OnDestroy();
					delete currentScene;
					currentScene = new Scene1(windowPtr->GetSDL_Window());
					currentScene->OnCreate();
					break;

					// If we need more scenes later I don't wanna rewrite this 
				case SDL_SCANCODE_F2:
					currentScene->OnDestroy();
					delete currentScene;
					currentScene = new Scene2(windowPtr->GetSDL_Window());
					currentScene->OnCreate();
					break;
				case SDL_SCANCODE_F3:
					currentScene->OnDestroy();
					delete currentScene;
					currentScene = new Scene3(windowPtr->GetSDL_Window());
					currentScene->OnCreate();
					break;


				case SDL_SCANCODE_F4:
					currentScene->OnDestroy();
					delete currentScene;
					currentScene = new Scene4(windowPtr->GetSDL_Window());
					currentScene->OnCreate();
					break;*/

				case SDL_SCANCODE_F10:
					currentScene->OnDestroy();
					delete currentScene;
					currentScene = new Scene0(windowPtr->GetSDL_Window());
					currentScene->OnCreate();
					break;


				case SDL_SCANCODE_RETURN:
					ToggleFullscreen(windowPtr->GetSDL_Window());
					break;
				default:
					
					break;

				}

			}
		}
		currentScene->Update(timer->GetDeltaTime());
		currentScene->Render();
		
		/// Keeep the event loop running at a proper rate
		SDL_Delay(timer->GetSleepTime(60)); ///60 frames per sec
		timer->UpdateFrameTicks();
		
	}

}

void GameManager::ToggleFullscreen(SDL_Window* Window) {
	Uint32 FullscreenFlag = SDL_WINDOW_FULLSCREEN;
	bool IsFullscreen = SDL_GetWindowFlags(Window) & FullscreenFlag;
	SDL_SetWindowFullscreen(Window, IsFullscreen ? 0 : FullscreenFlag);
	SDL_ShowCursor(IsFullscreen);
}

GameManager::~GameManager() {}

void GameManager::OnDestroy(){
	if (windowPtr) delete windowPtr;
	if (timer) delete timer;
	if (currentScene) delete currentScene;
}