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


	case 1: // 78 walls needed in scene1 for a upside down pyramid
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

		//Interior walls     using xpos3 strating at 4 I'm making a big pryamid
		xpos3 = 3.0f;
		for (int i = 46; i < 60; i++) { //Frist row
			walls[i]->setPos(Vec3(xpos3, 15.0f, 0.0f));
			xpos3 += 2.0f;
		}


		xpos3 = 7.0f;
		for (int i = 60; i < 70; i++) { //Second row
			walls[i]->setPos(Vec3(xpos3, 13.0f, 0.0f));
			xpos3 += 2.0f;
		}

		xpos3 = 11.0f;
		for (int i = 70; i < 76; i++) { //Third row
			walls[i]->setPos(Vec3(xpos3, 11.0f, 0.0f));
			xpos3 += 2.0f;
		}

		xpos3 = 15.0f;
		for (int i = 76; i < 78; i++) { //Forth row last row
			walls[i]->setPos(Vec3(xpos3, 9.0f, 0.0f));
			xpos3 += 2.0f;
		}

		break;

	case 2: // Circle thing requari 58 walls
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

		//Interior walls the circle bit I could write a loop but this is easier 

		walls[46]->setPos(Vec3(15.0f, 3.0f, 0.0f));
		walls[47]->setPos(Vec3(17.0f, 3.0f, 0.0f));
									 
		walls[48]->setPos(Vec3(13.0f, 5.0f, 0.0f));
		walls[49]->setPos(Vec3(19.0f, 5.0f, 0.0f));
									  
		walls[50]->setPos(Vec3(11.0f, 7.0f, 0.0f));
		walls[51]->setPos(Vec3(21.0f, 7.0f, 0.0f));
									  
		walls[52]->setPos(Vec3(11.0f, 11.0f, 0.0f));
		walls[53]->setPos(Vec3(21.0f, 11.0f, 0.0f));
									  
		walls[54]->setPos(Vec3(13.0f, 13.0f, 0.0f));
		walls[55]->setPos(Vec3(19.0f, 13.0f, 0.0f));
									  
		walls[56]->setPos(Vec3(15.0f, 15.0f, 0.0f));
		walls[57]->setPos(Vec3(17.0f, 15.0f, 0.0f));

		break;

	case 3://78 walls needed
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

		//Inner bit
		xpos3 = 3.0f;
		for (int i = 46; i < 60; i++) { //Frist row
			walls[i]->setPos(Vec3(xpos3, 3.0f, 0.0f));
			xpos3 += 2.0f;
		}


		xpos3 = 7.0f;
		for (int i = 60; i < 70; i++) { //Second row
			walls[i]->setPos(Vec3(xpos3, 5.0f, 0.0f));
			xpos3 += 2.0f;
		}

		xpos3 = 11.0f;
		for (int i = 70; i < 76; i++) { //Third row
			walls[i]->setPos(Vec3(xpos3, 7.0f, 0.0f));
			xpos3 += 2.0f;
		}

		xpos3 = 15.0f;
		for (int i = 76; i < 78; i++) { //Forth row last row
			walls[i]->setPos(Vec3(xpos3, 9.0f, 0.0f));
			xpos3 += 2.0f;
		}

		break;


		break;

	case 4: //102 walls needed
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

		//Inner bit long hallway
		xpos2 = 3.0f;
		for (int i = 46; i < 60; ++i) { 
			walls[i]->setPos(Vec3(xpos2, 3.0f, 0.0f));
			xpos2 += 2;
		}
		xpos2 = 3.0f;
		for (int i = 60; i < 74; ++i) {
			walls[i]->setPos(Vec3(xpos2, 5.0f, 0.0f));
			xpos2 += 2;
		}
		xpos2 = 3.0f;
		for (int i = 74; i < 88; ++i) {
			walls[i]->setPos(Vec3(xpos2, 13.0f, 0.0f));
			xpos2 += 2;
		}
		xpos2 = 3.0f;
		for (int i = 88; i < 102; ++i) {
			walls[i]->setPos(Vec3(xpos2, 15.0f, 0.0f));
			xpos2 += 2;
		}

		break;


	case 5: //Boss Room  46 walls needed
		//Surronding walls plus a hole for a door
		//Xpos1 is supose to go here
		for (int i = 0; i < 16; ++i) { //Top line of walls 16 wall needed
			walls[i]->setPos(Vec3(xpos1, 17.0f, 0.0f));
			xpos1 += 2;
		}

		for (int i = 16; i < 24; ++i) { //Left line of walls 8 walls needed
			walls[i]->setPos(Vec3(31.0f, ypos1, 0.0f));
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
			walls[i]->setPos(Vec3(1.0f, ypos2, 0.0f));
			ypos2 += 2;
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
