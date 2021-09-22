#include "Wall.h"

Wall::Wall(Vec3 pos_){
	pos = pos_;
}

Wall::~Wall(){}

//Check to see if the player collided with the wall 
void Wall::colUpdate(float deltaTime, Body Player) { //Don't use not ready I'll fix later

}