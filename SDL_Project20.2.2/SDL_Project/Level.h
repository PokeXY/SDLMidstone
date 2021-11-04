#ifndef LEVEL_H
#define LEVEL_H
#include "Wall.h"

class Level{
private:
	Wall** walls;
	int wallNum;

public:
	Level(int wallNum_);
	
	~Level();

	void makeLevel(int sceneNum);
	void setWallTextures(SDL_Texture* texturePtr);
	Wall* getWall(int i) { return walls[i]; }

};

#endif // LEVEL_H