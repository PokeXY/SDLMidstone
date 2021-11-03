#ifndef WALL_H
#define WALL_H


#include "GameObject.h"
#include "Plane.h"

class Wall : public GameObject{
private:
	Plane LeftPlane;
	Plane RightPlane;
	Plane UpPlane;
	Plane DownPlane;

public:
	Wall();
	Wall(Plane LeftPlane_, Plane RightPlane_, Plane UpPlane_, Plane DownPlane_);
	~Wall();

	Plane GetLeft() { return LeftPlane; }
	Plane GetRight() { return RightPlane; }
	Plane GetUp() { return UpPlane; }
	Plane GetDown() { return DownPlane; }

};


#endif // WALL_H