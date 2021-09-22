#include "Scene1.h"
#include <SDL.h>
#include <SDL_image.h>


Scene1::Scene1(SDL_Window* sdlWindow_) {
	window = sdlWindow_;
	float xpos = 2.0f;
	ren = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
	Wall = new Ball(Vec3(0.0f, 6.0f, 0.0f), Vec3(0.0f, 0.0f, 0.0f), Vec3(0.0f, 0.0f, 0.0f), 1.0f);
	for(int i = 0; i < NUME; ++i) {
		bird[i] = new Bird(Vec3(xpos, 5.0f, 0.0f), Vec3(0.0f, 0.0f, 0.0f), Vec3(0.0f, -9.81f, 0.0f), 2.0f);
	}
		//xpos += 3.0f;
	
}

Scene1::~Scene1() {
	for (int i = 0; i < NUME; ++i) { 
		delete bird[i]; 
	}
	delete Wall;
	SDL_DestroyRenderer(ren);
}

bool Scene1::OnCreate() {
	int w, h;
	float xAxis = 30.0f;
	float yAxis = 15.0f;
	float zAxis = 1.0f;
	SDL_GetWindowSize(window, &w, &h);

	Matrix4 ndc = MMath::viewportNDC(w, h);
	Matrix4 ortho = MMath::orthographic(0.0f, xAxis, 0.0f, yAxis, 0.0f, zAxis);
	projectionMatrix = ndc * ortho;

	//loading in the bird or ball
	IMG_Init(IMG_INIT_PNG);
	SDL_Surface* birdImage = IMG_Load("Art/FlappyBird1.png");
	SDL_Texture* birdTexture = SDL_CreateTextureFromSurface(ren, birdImage);
	//loading in the cliff
	SDL_Surface* cliffImage = IMG_Load("Art/cliff.png");
	SDL_Texture* wallTexture = SDL_CreateTextureFromSurface(ren, cliffImage);
	if (birdImage == nullptr) {
		std::cerr << "ballImgage does not work" << std::endl;
	}
	else {
		Vec3 wcfsc;
		Vec3 wcfsc1;
		wcfsc.x = xAxis / static_cast<float>(w) * static_cast<float>(birdImage->w);
		wcfsc.y = yAxis / static_cast<float>(h) * static_cast<float>(birdImage->h);
		//Cliff set up
		wcfsc1.x =  xAxis / static_cast<float>(w) * static_cast<float>(cliffImage->w);
		wcfsc1.y =  yAxis / static_cast<float>(h) * static_cast<float>(cliffImage->h);
		

		for (int i = 0; i < NUME; ++i) {
			bird[i]->setTexture(birdTexture);
			bird[i]->setImageSizeWorldCoords(wcfsc);
		}
		//cliff set up
		Wall->setTexture(wallTexture);
		Wall->setImageSizeWorldCoords(wcfsc1);
		SDL_FreeSurface(birdImage);
		SDL_FreeSurface(cliffImage);
	}
	return true;
}

void Scene1::OnDestroy() {
	for (int i = 0; i < NUME; ++i) {
		delete bird[i];
	}
	delete Wall;
	SDL_DestroyRenderer(ren);
}

void Scene1::Update(const float deltaTime) {
	for (int i = 0; i < NUME; ++i) {
		bird[i]->Update(deltaTime);
	}
	Wall->Update(deltaTime);
}

void Scene1::HandleEvents(const SDL_Event& sdlEvent) {
	for (int i = 0; i < NUME; ++i)
		bird[i]->HandleEvents(sdlEvent);

}

void Scene1::Render() {
	SDL_SetRenderDrawColor(ren, 0, 0, 200, 0);
	SDL_Renderer* ren = SDL_GetRenderer(window);
	//Clear screen
	SDL_RenderClear(ren);


	static double rot = 0.0;
	Vec3 screenCoords;
	Vec3 test;
	int w, h;
	int w1, h1;
	SDL_Rect ball;
	SDL_Rect wall;
	SDL_QueryTexture(Wall->getTexture(), nullptr, nullptr, &w1, &h1);
	test = projectionMatrix * Wall->getPos();
	wall.x = static_cast<int> (test.x);
	wall.y = static_cast<int> (test.y);
	wall.w = w1;
	wall.h = h1;
	
	SDL_RenderCopy(ren, Wall->getTexture(), nullptr, &wall);
	for (int i = 0; i < NUME; ++i ) {
		SDL_QueryTexture(bird[i]->getTexture(), nullptr, nullptr, &w, &h);
		screenCoords = projectionMatrix * bird[i]->getPos();
		ball.x = static_cast<int> (screenCoords.x);
		ball.y = static_cast<int> (screenCoords.y);
		ball.w = w;
		ball.h = h;
		SDL_RenderCopyEx(ren, bird[i]->getTexture(), nullptr, &ball, rot, nullptr, SDL_FLIP_NONE);


	}
	
	//Updates the screen
	SDL_RenderPresent(ren);


}


