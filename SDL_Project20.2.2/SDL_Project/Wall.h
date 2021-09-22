#ifndef WALL_H
#define WALL_H
#include "Body.h"

class Wall: public Body{
private:

public:
	
	Wall(Vec3 pos_);
	~Wall();
	void colUpdate(float delatTime, Body Player);

};

#endif //WALL_H