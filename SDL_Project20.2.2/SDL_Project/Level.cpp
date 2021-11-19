#include "Level.h"
//#include "Physics.h"


Level::Level(int wallNum_) {
	wallNum = wallNum_;
	walls = new Wall * [wallNum];
	for (int i = 0; i < wallNum; i++) {
		walls[i] = new Wall;
		walls[i]->setBoundingBoxWidth(2.0f);
		walls[i]->setBoundingBoxHeight(2.0f);
	}



}

Level::~Level() {
	for (int i = 0; i < wallNum; i++) {
		delete walls[i];
	}

	delete walls;

}

void Level::makeLevel(int sceneNum) { //Makes the level by placing all the walls
	//For outside walls
	float xpos1 = 1.0;
	float ypos1 = 1.0f;
	float xpos2 = 3.0f;
	float ypos2 = 3.0f;

	//For interior walls
	float xpos3 = 0.0f;
	float ypos3 = 0.0f;


	switch (sceneNum){
		
	case 0:
		//Surronding walls plus a hole for a door
		//Xpos1 is supose to go here
		for (int i = 0; i < 16; ++i) { //Top line of walls 16 wall needed
			walls[i]->setPos(Vec3(xpos1, 17.0f, 0.0f));
			xpos1 += 2;
		}
		
		for (int i = 16; i < 24; ++i) { //Left line of walls 8 walls needed
				walls[i]->setPos(Vec3(1.0f, ypos1, 0.0f));
				ypos1 += 2;
		}
		
		for (int i = 24; i < 40; ++i) { //Bottom line of walls 15 wall needed
			walls[i]->setPos(Vec3(xpos2, 1.0f, 0.0f));
			xpos2 += 2;
		}
		
		for (int i = 40; i < 43; ++i) { //Right bottom under door 3 walls needed
			walls[i]->setPos(Vec3(31.0f, ypos2, 0.0f));
			ypos2 += 2;
		}

		ypos2 += 2;
		for (int i = 43; i < 46; ++i) { //Right upper under door 3 walls needed
			walls[i]->setPos(Vec3(31.0f, ypos2, 0.0f));
			ypos2 += 2;
		}

		//Interior walls       x.x    y.y    z.z
		walls[46]->setPos(Vec3(10.0f, 13.0f, 0.0f));
		walls[47]->setPos(Vec3(10.0f, 11.0f, 0.0f));
		walls[48]->setPos(Vec3(12.0f, 13.0f, 0.0f));

		walls[49]->setPos(Vec3(10.0f, 7.0f, 0.0f));
		walls[50]->setPos(Vec3(10.0f, 5.0f, 0.0f));
		walls[51]->setPos(Vec3(12.0f, 5.0f, 0.0f));

		walls[52]->setPos(Vec3(20.0f, 13.0f, 0.0f));
		walls[53]->setPos(Vec3(22.0f, 13.0f, 0.0f));
		walls[54]->setPos(Vec3(22.0f, 11.0f, 0.0f));

		walls[55]->setPos(Vec3(20.0f, 5.0f, 0.0f));
		walls[56]->setPos(Vec3(22.0f, 5.0f, 0.0f));
		walls[57]->setPos(Vec3(22.0f, 7.0f, 0.0f));


		break;


	case 1: // ## walls needed in scene1
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

		//Interior walls     using xpos3 strating at 4 I'm making a big pryamid
		xpos3 = 2.0f;
		for (int i = 46; i < 60; i++) { //Frist row
			walls[i]->setPos(Vec3(xpos3, 16.0f, 0.0f));
			xpos3 += 2.0f;
		}


		xpos3 = 6.0f;
		for (int i = 60; i < 70; i++) { //Second row
			walls[i]->setPos(Vec3(xpos3, 14.0f, 0.0f));
			xpos3 += 2.0f;
		}

		xpos3 = 10.0f;
		for (int i = 70; i < 76; i++) { //Third row
			walls[i]->setPos(Vec3(xpos3, 12.0f, 0.0f));
			xpos3 += 2.0f;
		}

		xpos3 = 14.0f;
		for (int i = 76; i < 78; i++) { //Forth row last row
			walls[i]->setPos(Vec3(xpos3, 10.0f, 0.0f));
			xpos3 += 2.0f;
		}

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
