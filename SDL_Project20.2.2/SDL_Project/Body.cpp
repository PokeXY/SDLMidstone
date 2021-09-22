#include "Body.h"

#define PI 3.1415926535

Body::Body() {

	pos.x = 0.0f;
	pos.y = 0.0f; // Meter
	pos.z = 0.0f;

	vel.x = 0.0f;
	vel.y = 0.0f;// Meter per second 
	vel.z = 0.0f;

	accel.x = 0.0f;
	accel.y = 0.0f; //Meters per second square
	accel.z = 0.0f;

	mass = 1.0f;// Kilogram

	rotation = 0.0;
}

Body::Body(Vec3 pos_, Vec3 vel_, Vec3 accel_, float mass_):
	pos(pos_), vel(vel_), accel(accel_), mass(mass_), rotation(0.0f),image(nullptr),isCap(false){


	


}




Body::~Body() {



}

void Body::GetSpeed(float speed, float angle) {
	angle *= PI / 180;
	vel.x = cos(angle) * speed;
	vel.y = sin(angle) * speed;
	
	
}

float Body::GetRotion(float w, float speed, float deltaTime) {
	float cir =  PI * w;
	float rot;
	if (speed < 0 || 0 < speed) {
		float t = speed / cir;
		rot =  ((speed * deltaTime * 360.0f)/cir) ;
	}
	else {
		rot = 0.0f;
	}
	return rot;

	
}

void Body::Pause() {
	vel.x = vel.y = vel.z = 0.0f;
	accel.x = accel.y = accel.z = 0.0f;


}


void Body::ApplyForce(Vec3 force_) {
	accel.x = force_.x / mass;
	accel.y = force_.y / mass;
	accel.z = force_.z / mass;
}

void Body::HandleEvents(const SDL_Event& sdlEvent) {
	float xForce = 0.0f;
	float yForce = 0.0f;
	float df = (-0.2 * vel.y) + (accel.y * mass);
	float spd = 5.0f;
	Vec3 GF(0.0f,-9.8f * mass , 0.0f);
	Vec3 WF(-30.0, 0.0f,0.0f);
	Vec3 DF = (-0.2 * vel);
	Vec3 TF= GF + WF + DF;

	if (sdlEvent.type == SDL_KEYDOWN) {
		Matrix4 rot = MMath::rotate(27.0f, Vec3(0.0f,0.0f,1.0f));
		Vec3 dir(1.0f, 0.0f, 0.0f);
		Vec3 rA(0.0f, 0.0f, 1.0f);
		Vec3 origPos(0.0f, 2.3f, 0.0f);
		dir = rot * dir * 2.0f;
		switch (sdlEvent.key.keysym.scancode){
			
			case SDL_SCANCODE_W:
				//pos = origPos;
				vel = dir;



				//rotation = MMath::rotate(90.0, rA);
				//pos = MMath::translate(2.5f, 15.0f, 0.0f) * pos;
				////ApplyForce(Vec3(xForce, yForce, 0.0f));
				break;
			case SDL_SCANCODE_S:
				vel.y -= spd;
				//ApplyForce(Vec3(xForce, yForce, 0.0f));
				break;
			case SDL_SCANCODE_A:
				vel.x -= spd;
				//ApplyForce(Vec3(xForce, yForce, 0.0f));
				break;
			case SDL_SCANCODE_D:
				vel.x += spd;
				//ApplyForce(Vec3(xForce, yForce, 0.0f));
				break;
				
			case SDL_SCANCODE_SPACE:
				pos.x = 2.0f;
				pos.y = 5.0f;
				vel.x = 0.0f;
				vel.y = 0.0f;// Meter per second 
				accel.x = 0.0f;
				accel.y = 0.0f;
				//Meters per second square
				GetSpeed(30.0f, 27.0f);
				accel.y = -9.8;
				ApplyForce(TF);
				break;

			case SDL_SCANCODE_P:
				Pause();
				break;

			default:
				break;
		}
	

	}

}

void Body::Update(float deltaTime) {
	pos.x += vel.x * deltaTime + 0.5f * accel.x * deltaTime * deltaTime;
	pos.y += vel.y * deltaTime + 0.5f * accel.y * deltaTime * deltaTime;
	pos.z += vel.z * deltaTime + 0.5f * accel.z * deltaTime * deltaTime;


	vel.x += accel.x * deltaTime;
	vel.y += accel.y * deltaTime;
	vel.z += accel.z * deltaTime;
	//if (pos.y - imagesizeworldcoords.y < 0.0f) { // floor
	//	vel.y *= -1.0f;
	//	//std::cout << "postion" << pos.x << " , " << pos.y;
	//}
	//if (pos.x < 0.0f) {
	//	vel.x *= -1.0f;
	//}
	//if (pos.x + imagesizeworldcoords.x > 30.0f ) {
	//	vel.x *= -1.0f;
	//}
	//if (pos.y > 15.0f) {
	//	vel.y *= -1.0f;
	//}
	//
	//if (pos.y <= 5.0f && pos.x <= 2.0f) {
	//	vel.y *= -1.0f;
	//	vel.x *= -1.0f;
	//	

	//}
	
	// The ROTATION but it works, also Scott why I'm I multiplying the vel.x by deltaTime ? I don't understand 
	rotation += ((vel.x * 360.0 * deltaTime) / 2.0f * PI * (imageSizeWorldCoords.x/ 2.0f) ) * deltaTime;

	//std::cout <<"pos.x = " << pos.x << " pos.y = " << pos.y << "  Vel.y = "<< vel.y << std::endl;
}

// I'll fill this in later
void Body::setRotation(float deltaTime) {



}

void Body::setCenterPoint() {
	centerPoint.x = pos.x + (imageSizeWorldCoords.x / 2.0);
	centerPoint.y = pos.y - (imageSizeWorldCoords.y / 2.0);
	centerPoint.z = 0.0f;


}


Vec3 Body::getCenterPoint(){
	setCenterPoint();
	
	return centerPoint;
}


