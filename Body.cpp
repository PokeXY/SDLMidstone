#include "Body.h"


Body::Body() {
	pos.x = 2.3f;
	pos.y = 12.5f;
	pos.z = 0.0f;

	vel.x = 4.0f;
	vel.y = 0.0f;
	vel.z = 0.0f;

	accel.x = 0.0f;
	accel.y = 0.0f;
	accel.z = 0.0f;

	mass = 1.0f;
	rotation = 0.0;
	image = nullptr;
}

Body::Body(Vec3 pos_, Vec3 vel_, Vec3 accel_, float mass_) :
	/*pos.x = pos_.x;
	pos.y = pos_.y;
	pos.z = pos_.z;

	vel.x = vel_.x;
	vel.y = vel_.y;
	vel.z = vel_.z;

	accel.x = accel_.x;
	accel.y = accel_.y;
	accel.z = accel_.z;
	*/
	pos(pos_), vel(vel_), accel(accel_), mass(mass_), image(nullptr), rotation(0.0), isCapture(false) {

	//mass = mass_;
	//image = nullptr;
	//rotation = 0.0;

}

Body::~Body() {

}

void Body::ApplyForce(Vec3 force_) {
	accel.x = force_.x / mass;
	accel.y = force_.y / mass;
	accel.z = force_.z / mass;
	//accel = force_ / mass;
}

void Body::HandleEvents(const SDL_Event& sdlEvent) {
	if (sdlEvent.type == SDL_KEYDOWN) {
		switch (sdlEvent.key.keysym.scancode) {
		case SDL_SCANCODE_RETURN:
			ApplyForce(Vec3(100.0f, 0.0f, 0.0f));
			break;

		case SDL_SCANCODE_UP:
			ApplyForce(Vec3(0.0f, 2.0f, 0.0f));
			break;

		default:
			break;
		}

	}
	else if (sdlEvent.type == SDL_KEYUP && sdlEvent.key.keysym.scancode == SDL_SCANCODE_RETURN) {
		ApplyForce(Vec3(0.0f, 0.0f, 0.0f));

	}
	else if (sdlEvent.type == SDL_MOUSEBUTTONDOWN || sdlEvent.button.button == SDL_BUTTON_LEFT) {
		printf("LEFT MOUSE!!! x= %d y= %d\n", sdlEvent.motion.x, sdlEvent.motion.y);

	}
	else if (sdlEvent.type == SDL_MOUSEMOTION) {
		printf("Mouse in motion x= %d y= %d\n", sdlEvent.motion.x, sdlEvent.motion.y);
	}
}

void Body::Update(float deltaTime) {

	pos += vel * deltaTime + 0.5f * accel * deltaTime * deltaTime;
	vel += accel * deltaTime;

	rotation += (360.0f * vel.x * deltaTime) / (2.0f * M_PI * imageSizeWorldCoords.x / 2.0f);


	if (pos.y - getRadius() < -15.0f) { /// Floor 15
		if (vel.y < 0.0f) {
			vel.y *= -1.0f;
		}
	}

	if (pos.x - getRadius() < -15.0f) { /// Left wall
		if (vel.x < 0.0f) {
			vel.x *= -1.0f;
		}
	}

	if (pos.x + getRadius() > 15.0f) { ///Right wall
		if (vel.x > 0.0f) {
			vel.x *= -1.0f;
		}
	}

	if (pos.y + getRadius() > 15.0) {
		if (vel.y > 0.0f) {
			vel.y *= -1.0f;
		}
	}

}
