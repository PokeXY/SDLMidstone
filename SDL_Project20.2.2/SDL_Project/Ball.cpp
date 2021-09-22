#include "Ball.h"




Ball::~Ball() {

}


void Ball::colUpdate(float deltaTime, Ball Isac) {
	Vec3 L = Isac.getCenterPoint() - getCenterPoint();
	Vec3 n = VMath::normalize(L);

}