#include "Level.h"


Level::Level(int wallNum_) {
	wallNum = wallNum_;
	walls = new Wall * [wallNum];
	for (int i = 0; i < wallNum; i++) {
		walls[i] = new Wall;

	}



}

Level::~Level() {
	
	for (int i = 0; i < wallNum; i++) {
		delete walls[i];
	}

	delete walls;

}

void Level::makeLevel(int sceneNum) {
	float xpos1 = 0.0;
	float ypos1 = 2.0f;
	float xpos2 = 2.0f;
	float ypos2 = 4.0f;
	switch (sceneNum){
		
	case 0:
		//Surronding walls plus a hole for a door
		//Xpos1 is supose to go here
		for (int i = 0; i < 16; ++i) { //Top line of walls 16 wall needed
			walls[i]->setPos(Vec3(xpos1, 18.0f, 0.0f));
			xpos1 += 2;
		}
		
		for (int i = 16; i < 24; ++i) { //Left line of walls 8 walls needed
				walls[i]->setPos(Vec3(0.0f, ypos1, 0.0f));
				ypos1 += 2;
		}
		
		for (int i = 24; i < 40; ++i) { //Bottom line of walls 15 wall needed
			walls[i]->setPos(Vec3(xpos2, 2.0f, 0.0f));
			xpos2 += 2;
		}
		
		for (int i = 40; i < 43; ++i) { //Right bottom under door 3 walls needed
			walls[i]->setPos(Vec3(30.0f, ypos2, 0.0f));
			ypos2 += 2;
		}

		ypos2 += 2;
		for (int i = 43; i < 46; ++i) { //Right upper under door 3 walls needed
			walls[i]->setPos(Vec3(30.0f, ypos2, 0.0f));
			ypos2 += 2;
		}

		//Interior walls       x.x    y.y    z.z
		walls[46]->setPos(Vec3(10.0f, 14.0f, 0.0f));
		walls[47]->setPos(Vec3(10.0f, 12.0f, 0.0f));
		walls[48]->setPos(Vec3(12.0f, 14.0f, 0.0f));

		walls[49]->setPos(Vec3(10.0f, 8.0f, 0.0f));
		walls[50]->setPos(Vec3(10.0f, 6.0f, 0.0f));
		walls[51]->setPos(Vec3(12.0f, 6.0f, 0.0f));

		walls[52]->setPos(Vec3(20.0f, 14.0f, 0.0f));
		walls[53]->setPos(Vec3(22.0f, 14.0f, 0.0f));
		walls[54]->setPos(Vec3(22.0f, 12.0f, 0.0f));

		walls[55]->setPos(Vec3(20.0f, 6.0f, 0.0f));
		walls[56]->setPos(Vec3(22.0f, 6.0f, 0.0f));
		walls[57]->setPos(Vec3(22.0f, 8.0f, 0.0f));


		break;

	default:
		break;
	}

}

void Level::setWallTextures(SDL_Texture* texturePtr) {
	for (int i = 0; i < wallNum; i++) {
		walls[i]->setTexture(texturePtr);
	}

}