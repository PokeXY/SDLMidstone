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
	if (background) delete background, background = nullptr;
	if (croutonTexture) delete croutonTexture, croutonTexture = nullptr;
	if (player) delete player, player = nullptr;
	
	for (GameObject* GameObject : walls) {
		delete GameObject;
	}
	for (Bullet* Bullet : bullets) {
		delete Bullet;
	}
	if (wallLeft) delete wallLeft, wallLeft = nullptr;
	if (wallRight) delete wallRight, wallRight = nullptr;
	if (wallTop) delete wallTop, wallTop = nullptr;
	if (wallBottom) delete wallBottom, wallBottom = nullptr;

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

	//temporary border walls
	wallLeft = new Plane(Vec3(1.0f, 0.0f, 0.0f), 0.0f);
	wallRight = new Plane(Vec3(-1.0f, 0.0f, 0.0f), xAxis);
	wallTop = new Plane(Vec3(0.0f, -1.0f, 0.0f), yAxis);
	wallBottom = new Plane(Vec3(0.0f, 1.0f, 0.0f), 0.0f);

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


	//Load the crouton image and set the texture as well
	surfacePtr = IMG_Load("Art/placeholderCrouton.png");
	croutonTexture = SDL_CreateTextureFromSurface(renderer, surfacePtr);

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
	player->setBoundingSphere(Sphere(2.0f));
	player->setTexture(texturePtr);


	return true;
}

void Scene0::OnDestroy() {  
}

void Scene0::Update(const float time) {
	/// This is the physics in the x and y dimension don't mess with z

	

	//test ethan player collide wall
	std::cout << "x" << player->getPos().x << std::endl;
	if (player->getPos().x  < 1)// wallLeft
	{
		printf("touch wallLeft");	
		player->setPos(Vec3(1.0f, player->getPos().y, player->getPos().z ));
	}
	if (player->getPos().x > 31)// wallRight
	{
		printf("touch wallRight");
		player->setPos(Vec3(31.0f, player->getPos().y, player->getPos().z));
	}
	std::cout << "y" << player->getPos().y << std::endl;
	if (player->getPos().y > 17)// wallTop
	{
		printf("touch wallTop");
		player->setPos(Vec3(player->getPos().x, 17.0f, player->getPos().z));
	}
	if (player->getPos().y < 1)// wallBottom
	{
		printf("touch wallBottom");
		player->setPos(Vec3(player->getPos().x, 1.0f, player->getPos().z));
	}

//Player Movement
	Physics::SimpleNewtonMotion(*player, time);
	//Bullets Movement
	for (int i = 0; i < bullets.size(); ++i) {
		Physics::SimpleNewtonMotion(*bullets[i], time);
	}
	//Bullet Border Wall Collisions
	for (int i = 0; i < bullets.size(); ++i) {
		if (Physics::PlaneSphereCollision(*bullets[i], *wallLeft) == true) {
			Physics::PlaneSphereCollisionResponse(*bullets[i], *wallLeft);
			bullets[i]->setRemainingBounces(bullets[i]->getRemainingBounces() - 1);
			if (bullets[i]->getRemainingBounces() < 0) {
				bullets.erase(bullets.begin()+i);
				break;
			}
		}
		if (Physics::PlaneSphereCollision(*bullets[i], *wallRight) == true) {
			Physics::PlaneSphereCollisionResponse(*bullets[i], *wallRight);
			bullets[i]->setRemainingBounces(bullets[i]->getRemainingBounces() - 1);
			if (bullets[i]->getRemainingBounces() < 0) {
				bullets.erase(bullets.begin() + i);
				break;
			}
		}
		if (Physics::PlaneSphereCollision(*bullets[i], *wallTop) == true) {
			Physics::PlaneSphereCollisionResponse(*bullets[i], *wallTop);
			bullets[i]->setRemainingBounces(bullets[i]->getRemainingBounces() - 1);
			if (bullets[i]->getRemainingBounces() < 0) {
				bullets.erase(bullets.begin() + i);
				break;
			}
		}
		if (Physics::PlaneSphereCollision(*bullets[i], *wallBottom) == true) {
			Physics::PlaneSphereCollisionResponse(*bullets[i], *wallBottom);
			bullets[i]->setRemainingBounces(bullets[i]->getRemainingBounces() - 1);
			if (bullets[i]->getRemainingBounces() < 0) {
				bullets.erase(bullets.begin() + i);
				break;
			}
		}
	}
}

void Scene0::HandleEvents(const SDL_Event& sdlEvent) {
	//Make stuff happen here with the clickety clack
	player->HandleEvents(sdlEvent, projectionMatrix);

	if (sdlEvent.type == SDL_EventType::SDL_MOUSEBUTTONDOWN) {
		Bullet bullet = player->FireWeapon();
		bullets.push_back(new Bullet(bullet));
		int newBullet = bullets.size() - 1;
		bullets[newBullet]->setTexture(croutonTexture);
		bullets[newBullet]->setBoundingSphere(Sphere(1.0f));
	}
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
	playerRect.x = static_cast<int>(playerScreenCoords.x) - playerW;
	playerRect.y = static_cast<int>(playerScreenCoords.y) - playerH;
	playerRect.w = playerW * 2;
	playerRect.h = playerH * 2;
	SDL_RenderCopyEx(renderer, player->getTexture(), nullptr, &playerRect, player->getAngle(), nullptr, SDL_FLIP_NONE);

	//Draw Bullets
	SDL_Rect bulletRect;
	Vec3 bulletScreenCoords;
	int bulletW, bulletH;

	for (int i = 0; i < bullets.size(); ++i) {
		bulletScreenCoords = projectionMatrix * bullets[i]->getPos();
		SDL_QueryTexture(bullets[i]->getTexture(), nullptr, nullptr, &bulletW, &bulletH);
		bulletRect.x = static_cast<int>(bulletScreenCoords.x - bulletW / 20);
		bulletRect.y = static_cast<int>(bulletScreenCoords.y - bulletH / 20);
		bulletRect.w = bulletW / 10;
		bulletRect.h = bulletH / 10;

		SDL_RenderCopy(renderer, bullets[i]->getTexture(), nullptr, &bulletRect);
	}
	
	//Update screen
	SDL_RenderPresent(renderer);

	
}
