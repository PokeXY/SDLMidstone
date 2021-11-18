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
	OnDestroy();
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
	surfacePtr = IMG_Load("Art/Crouton256.png");
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

	//Making the level
	level = new Level(NUMWALL);
	level->makeLevel(0); 
	level->setWallTextures(texturePtr);

	//load player character
	surfacePtr = IMG_Load("Art/BreadManConcept.png");
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
	player->setBoundingSphere(Sphere(1.0f));
	player->setTexture(texturePtr);

	//load enemy characters
	surfacePtr = IMG_Load("Art/The Unbread.png");
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

	for (int i = 0; i < 4; ++i) {
		enemies.push_back(new EnemyCharacter());
		enemies[i]->setPos(Vec3(xAxis - 2.0f, yAxis - 4.0f - 3.0f * i, 0.0f));
		enemies[i]->setBoundingSphere(Sphere(0.5f));
		enemies[i]->setTexture(texturePtr);
	}

	//load boss characters
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

	boss = new BossCharacter();
	boss->setPos(Vec3(2.0f, 2.0f, 2.0f));
	boss->setBoundingSphere(Sphere(0.5f));
	boss->setTexture(texturePtr);


	return true;
}

void Scene0::OnDestroy() {  
	/*if (surfacePtr) delete surfacePtr, surfacePtr = nullptr;
	if (texturePtr) delete texturePtr, texturePtr = nullptr;
	if (background) delete background, background = nullptr;
	if (croutonTexture) delete croutonTexture, croutonTexture = nullptr;*/
	if (player) delete player, player = nullptr;
	if (level) delete level, level = nullptr;


	/*for (Wall* Wall : walls) {
		delete Wall;
	}*/
	for (Bullet* Bullet : bullets) {
		delete Bullet;
	}
	for (EnemyCharacter* EnemyCharacter : enemies) {
		delete EnemyCharacter;
	}
	if (wallLeft) delete wallLeft, wallLeft = nullptr;
	if (wallRight) delete wallRight, wallRight = nullptr;
	if (wallTop) delete wallTop, wallTop = nullptr;
	if (wallBottom) delete wallBottom, wallBottom = nullptr;

	SDL_DestroyRenderer(renderer);
}

void Scene0::Update(const float time) {
	/// This is the physics in the x and y dimension don't mess with z

    //Player Movement
	Physics::SimpleNewtonMotion(*player, time);
	


	//Enemy Movement
	for (int i = 0; i < enemies.size(); ++i) {
		enemies[i]->seekPlayer(player->getPos());
		Physics::SimpleNewtonMotion(*enemies[i], time);
	}

	//Player Hits Wall
	if (Physics::PlaneSphereCollision(*player, *wallLeft) == true) {
		player->setPos(Vec3(player->getBoundingSphere().r, player->getPos().y, player->getPos().z));
	}
	if (Physics::PlaneSphereCollision(*player, *wallRight) == true) {
		player->setPos(Vec3(-wallRight->d - player->getBoundingSphere().r, player->getPos().y, player->getPos().z));
	}
	if (Physics::PlaneSphereCollision(*player, *wallTop) == true) {
		player->setPos(Vec3(player->getPos().x, -wallTop->d - player->getBoundingSphere().r, player->getPos().z));
	}
	if (Physics::PlaneSphereCollision(*player, *wallBottom) == true) {
		player->setPos(Vec3(player->getPos().x, player->getBoundingSphere().r, player->getPos().z));
	}

	//Bullets Movement
	for (int i = 0; i < bullets.size(); ++i) {
		Physics::SimpleNewtonMotion(*bullets[i], time);
	}

	//Bullet Hits Enemy
	for (int i = 0; i < bullets.size(); ++i) {
		for (int j = 0; j < enemies.size(); ++j) {
			if (Physics::SphereSphereCollision(*bullets[i], *enemies[j]) == true) {
				bullets.erase(bullets.begin() + i);
				enemies[j]->takeDamage(1.0f);
				if (enemies[j]->getHealth() <= 0) {
					enemies.erase(enemies.begin() + j);
				}
				break;
			}
		}
	}

	//Bullet Hits Player
	for (int i = 0; i < bullets.size(); ++i) {
		if (Physics::SphereSphereCollision(*bullets[i], *player) == true) {
				bullets.erase(bullets.begin() + i);
				player->takeDamage(1.0f);
		}
	}

	//TODO : Enemy Hits Enemy
	//Prevent overlapping

	//Enemy Hits Player
	for (int i = 0; i < enemies.size(); ++i) {
		if (Physics::SphereSphereCollision(*enemies[i], *player) == true) {
			player->takeDamage(1.0f);
			enemies.erase(enemies.begin() + i);
		}
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



	//Bullet hit walls collison
	/*for (int i = 0; i < 1; ++i) {
		for (int i = 0; i < bullets.size(); ++i) {
			if (bullets[i]->getPos().y < level->getWall(i)->getPos().y && bullets[i]->getPos().y > level->getWall(i)->getPos().y - 80.0f ){
				if (Physics::PlaneSphereCollision(*bullets[i], level->getWall(i)->GetLeft()) == true) {
					Physics::PlaneSphereCollisionResponse(*bullets[i], level->getWall(i)->GetLeft());
					bullets[i]->setRemainingBounces(bullets[i]->getRemainingBounces() - 1);
					if (bullets[i]->getRemainingBounces() < 0) {
						bullets.erase(bullets.begin() + i);
						break;
					}
				}
			}
		}
	}*/

}

void Scene0::HandleEvents(const SDL_Event& sdlEvent) { //Make stuff happen here with the clickety clack

	player->HandleEvents(sdlEvent, projectionMatrix);

	if (sdlEvent.type == SDL_EventType::SDL_MOUSEBUTTONDOWN) {
		Bullet bullet = player->FireWeapon();
		bullets.push_back(new Bullet(bullet));
		int newBullet = bullets.size() - 1;
		bullets[newBullet]->setTexture(croutonTexture);
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
		SDL_QueryTexture(level->getWall(i)->getTexture(), nullptr, nullptr, &WallW, &WallH);
		wallScreenCoords = projectionMatrix * level->getWall(i)->getPos();
		WallRect.x = static_cast<int> (wallScreenCoords.x);
		WallRect.y = static_cast<int> (wallScreenCoords.y);
		WallRect.w = 80;
		WallRect.h = 80;
		SDL_RenderCopy(renderer, level->getWall(i)->getTexture(), nullptr, &WallRect);
	}

	//Draw Enemies
	SDL_Rect enemyRect;
	Vec3 enemyScreenCoords;
	int enemyW, enemyH;

	for (int i = 0; i < enemies.size(); ++i) {
		enemyScreenCoords = projectionMatrix * enemies[i]->getPos();
		SDL_QueryTexture(enemies[i]->getTexture(), nullptr, nullptr, &enemyW, &enemyH);
		enemyRect.x = static_cast<int>(enemyScreenCoords.x - enemyW / 2);
		enemyRect.y = static_cast<int>(enemyScreenCoords.y - enemyH / 2);
		enemyRect.w = enemyW;
		enemyRect.h = enemyH;

		SDL_RenderCopy(renderer, enemies[i]->getTexture(), nullptr, &enemyRect);
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

	SDL_Rect bossRect;
	Vec3 bossScreenCoords;
	int bossW, bossH;


	SDL_QueryTexture(boss->getTexture(), nullptr, nullptr, &bossW, &bossH);
	bossScreenCoords = projectionMatrix * boss->getPos();
	bossRect.x = static_cast<int>(bossScreenCoords.x) - bossW;
	bossRect.y = static_cast<int>(bossScreenCoords.y) - bossH;
	bossRect.w = playerW * 2;
	bossRect.h = playerH * 2;

	SDL_RenderCopy(renderer, boss->getTexture(), nullptr, &bossRect);

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
