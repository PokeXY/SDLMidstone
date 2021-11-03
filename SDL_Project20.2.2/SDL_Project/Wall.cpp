#include "Wall.h"


Wall::Wall() {
	LeftPlane = Plane(0.0f, 0.0f, 0.0f, 0.0f);
	RightPlane = Plane(0.0f, 0.0f, 0.0f, 0.0f);
	UpPlane = Plane(0.0f, 0.0f, 0.0f, 0.0f);
	DownPlane = Plane(0.0f, 0.0f, 0.0f, 0.0f);

}

Wall::Wall(Plane LeftPlane_, Plane RightPlane_, Plane UpPlane_, Plane DownPlane_) {
	LeftPlane = LeftPlane_;
	RightPlane = RightPlane_;
	UpPlane = UpPlane_;
	DownPlane = DownPlane_;

}

Wall::~Wall(){ }