#include "Scene5.h"
#include <SDL.h>
#include "SDL_image.h"
#include "Randomizer.h"
#include "Physics.h"
#include <iostream>

Scene5::Scene5(SDL_Window* sdlWindow_) {
	window = sdlWindow_;
	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
	nextS = false;
}

Scene5::~Scene5() {// Rember to delete every pointer NO MEMORY LEAKS!!!!!!

	OnDestroy();
}

bool Scene5::OnCreate() {
	int w, h;
	float xAxis = 32.0f;
	float yAxis = 18.0f;
	float zAxis = 1.0f;
	SDL_GetWindowSize(window, &w, &h);

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
	surfacePtr = IMG_Load("Art/grass256.png");
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
	level->makeLevel(5);
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
	player->setBoundingSphere(Sphere(0.5f));
	player->setTexture(texturePtr);

	//character health
	surfacePtr = IMG_Load("Art/BreadHealth.png");
	health = SDL_CreateTextureFromSurface(renderer, surfacePtr);

	if (surfacePtr == nullptr) {
		std::cerr << "Imgage does not work" << std::endl;
		return false;
	}
	if (health == nullptr) {
		printf("%s\n", SDL_GetError());
		return false;
	}

	SDL_FreeSurface(surfacePtr);


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
		enemies[i]->setPos(Vec3(xAxis - 3.0f, yAxis - 4.0f - 3.0f * i, 0.0f));
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

	for (int i = 0; i < 1; ++i)
	{
		boss = new BossCharacter;


	boss->setPos(Vec3(xAxis - 15.0f, yAxis - 10.0f - 3.0f * i, 0.0f));
		boss->setBoundingSphere(Sphere(0.5f));
		boss->setTexture(texturePtr);

	//	//boss->setPos(Vec3(10.0f, 10.0f, 10.0f));
	//	//boss->setBoundingSphere(Sphere(0.5f));
	//	//boss->setTexture(texturePtr);
	}


	return true;
}

void Scene5::OnDestroy() {
	/*if (surfacePtr) delete surfacePtr, surfacePtr = nullptr;
	if (texturePtr) delete texturePtr, texturePtr = nullptr;
	if (background) delete background, background = nullptr;
	if (croutonTexture) delete croutonTexture, croutonTexture = nullptr;*/
	if (player) delete player, player = nullptr;
	if (level) delete level, level = nullptr;
	if (boss) delete boss, boss = nullptr;


	/*for (Wall* Wall : walls) {
		delete Wall;
	}*/
	for (Bullet* Bullet : bullets) {
		delete Bullet;
	}
	for (EnemyCharacter* EnemyCharacter : enemies) {
		delete EnemyCharacter;
	}
	//for (BossCharacter* BossCharacter : boss) {
	//	delete BossCharacter;
	//}
	if (wallLeft) delete wallLeft, wallLeft = nullptr;
	if (wallRight) delete wallRight, wallRight = nullptr;
	if (wallTop) delete wallTop, wallTop = nullptr;
	if (wallBottom) delete wallBottom, wallBottom = nullptr;

	SDL_DestroyRenderer(renderer);
}

void Scene5::Update(const float time) {
	/// This is the physics in the x and y dimension don't mess with z

	//Player Movement
	Physics::SimpleNewtonMotion(*player, time);

	//Enemy Movement
	for (int i = 0; i < enemies.size(); ++i) {
		enemies[i]->seekPlayer(player->getPos());
		Physics::SimpleNewtonMotion(*enemies[i], time);
	}

	//Boss Movement
	if (boss)
	{
		boss->seekPlayer(player->getPos());
	Physics::SimpleNewtonMotion(*boss, time);
	}


	//Player Hits Edge of Window Walls
	//Potentially Obsolete with working circle rect collision
	if (Physics::PlaneSphereCollision(*player, *wallLeft) == true) {
		player->setPos(Vec3(player->getBoundingSphere().r, player->getPos().y, player->getPos().z));
	}
	//Load in new scene here
	if (Physics::PlaneSphereCollision(*player, *wallRight) == true) {
		player->setPos(Vec3(-wallRight->d - player->getBoundingSphere().r, player->getPos().y, player->getPos().z));
	}
	if (Physics::PlaneSphereCollision(*player, *wallTop) == true) {
		player->setPos(Vec3(player->getPos().x, -wallTop->d - player->getBoundingSphere().r, player->getPos().z));
	}
	if (Physics::PlaneSphereCollision(*player, *wallBottom) == true) {
		player->setPos(Vec3(player->getPos().x, player->getBoundingSphere().r, player->getPos().z));
	}

	//Player Hits Walls
	for (int i = 0; i < level->getWallNum(); ++i) {
		if (Physics::CircleRectCollision(*player, *level->getWall(i)) == true) {
			Physics::SimpleNewtonMotion(*player, -time);
		}
	}
	//Bullets Movement
	for (int i = 0; i < bullets.size(); ++i) {
		Physics::SimpleNewtonMotion(*bullets[i], time);
	}

	//Bullet Hits Enemy
	//Will include boss in this next
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

	// Bullets hit boss
	for (int i = 0; i < bullets.size(); ++i)
	{
		if (boss)
		{
			if (Physics::SphereSphereCollision(*bullets[i], *boss) == true) {
				bullets.erase(bullets.begin() + i);
				boss->takeDamage(1.0f);
				if (boss->getHealth() <= 0)
				{
					delete boss; boss = nullptr;
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

	//Enemies Hit Walls as well as boss
	//TODO : Improve enemy pathfinding
	for (int i = 0; i < level->getWallNum(); ++i) {
		for (int j = 0; j < enemies.size(); ++j) {
			if (Physics::CircleRectCollision(*enemies[j], *level->getWall(i)) == true) {
				Physics::SimpleNewtonMotion(*enemies[j], -2 * time);
			}
		}




	}

	for (int i = 0; i < level->getWallNum(); ++i)
	{
		if (boss)
		{
			if (Physics::CircleRectCollision(*boss, *level->getWall(i)) == true) {
				Physics::SimpleNewtonMotion(*boss, -2 * time);
			}
		}
	}

	//Enemy Hits Player
	for (int i = 0; i < enemies.size(); ++i) {
		if (Physics::SphereSphereCollision(*enemies[i], *player) == true) {
			player->takeDamage(1.0f);
			enemies.erase(enemies.begin() + i);
		}
	}

	//Bullet Hits Walls
	for (int i = 0; i < bullets.size(); ++i) {  //Idk who wrote this, but it's beatiful
		for (int j = 0; j < level->getWallNum(); ++j) {
			if (Physics::CircleRectCollision(*bullets[i], *level->getWall(j)) == true) {
				Physics::CircleRectCollisionResponse(*bullets[i], *level->getWall(j));
				bullets[i]->setRemainingBounces(bullets[i]->getRemainingBounces() - 1);
				if (bullets[i]->getRemainingBounces() < 0) {
					bullets.erase(bullets.begin() + i);
					break;
				}
			}
		}
	}

	//Bullet Border Wall Collisions
	//Potentially Obsolete with working circle rect collision
	for (int i = 0; i < bullets.size(); ++i) {
		if (Physics::PlaneSphereCollision(*bullets[i], *wallLeft) == true) {
			Physics::PlaneSphereCollisionResponse(*bullets[i], *wallLeft);
			bullets[i]->setRemainingBounces(bullets[i]->getRemainingBounces() - 1);
			if (bullets[i]->getRemainingBounces() < 0) {
				bullets.erase(bullets.begin() + i);
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

void Scene5::HandleEvents(const SDL_Event& sdlEvent) { //Make stuff happen here with the clickety clack

	player->HandleEvents(sdlEvent, projectionMatrix);

	if (sdlEvent.type == SDL_EventType::SDL_MOUSEBUTTONDOWN) {
		Bullet bullet = player->FireWeapon();
		bullets.push_back(new Bullet(bullet));
		int newBullet = bullets.size() - 1;
		bullets[newBullet]->setTexture(croutonTexture);
	}
}

void Scene5::Render() {
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
	SDL_Renderer* renderer = SDL_GetRenderer(window);
	//Clear screen
	SDL_RenderClear(renderer);

	//Draws the background
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
		WallRect.x = static_cast<int> (wallScreenCoords.x) - 40;
		WallRect.y = static_cast<int> (wallScreenCoords.y) - 40;
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

	// draw boss
	if (boss)
	{
		SDL_Rect bossRect;
		Vec3 bossScreenCoords;
		int bossW, bossH;


		bossScreenCoords = projectionMatrix * boss->getPos();
		SDL_QueryTexture(boss->getTexture(), nullptr, nullptr, &bossW, &bossH);
		bossRect.x = static_cast<int>(bossScreenCoords.x - bossW / 2);
		bossRect.y = static_cast<int>(bossScreenCoords.y - bossH / 2);
		bossRect.w = bossW;
		bossRect.h = bossH;

		SDL_RenderCopy(renderer, boss->getTexture(), nullptr, &bossRect);
	}


	//SDL_QueryTexture(boss->getTexture(), nullptr, nullptr, &bossW, &bossH);
	//bossScreenCoords = projectionMatrix * boss->getPos();
	//bossRect.x = static_cast<int>(bossScreenCoords.x) - bossW;
	//bossRect.y = static_cast<int>(bossScreenCoords.y) - bossH;
	//bossRect.w = playerW * 2;
	//bossRect.h = playerH * 2;

	//SDL_RenderCopy(renderer, boss->getTexture(), nullptr, &bossRect);

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


	if (player->getHealth() > 0)
	{
		SDL_Rect healthRect;

		healthRect.x = 10;
		healthRect.y = 0;
		healthRect.w = 100;
		healthRect.h = 100;
		SDL_RenderCopy(renderer, health, nullptr, &healthRect);

		if (player->getHealth() > 1)
		{
			SDL_Rect health1Rect;

			health1Rect.x = 40;
			health1Rect.y = 0;
			health1Rect.w = 100;
			health1Rect.h = 100;
			SDL_RenderCopy(renderer, health, nullptr, &health1Rect);

			if (player->getHealth() > 2)
			{
				SDL_Rect health2Rect;

				health2Rect.x = 70;
				health2Rect.y = 0;
				health2Rect.w = 100;
				health2Rect.h = 100;
				SDL_RenderCopy(renderer, health, nullptr, &health2Rect);
			}
		}
	}

	//Update screen
	SDL_RenderPresent(renderer);


}


bool Scene5::getDead() {
	if (player->getHealth() <= 0) return true;
	return false;
}

bool Scene5::nextScene() { //Check if boss is dead to make win later
	if (boss || enemies.size() > 0) return false;
	return true;
}
