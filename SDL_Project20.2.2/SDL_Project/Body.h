#ifndef BODY_H
#define BODY_H

#include "Vector.h"
#include "SDL_image.h"
#include "MMath.h"
#include "VMath.h"
using namespace MATH;

class Body
{
public:
	Vec3 pos;
	Vec3 vel;
	Vec3 accel;
	float mass;
	double rotation;
	Vec3 centerPoint;
	SDL_Surface* image;
	SDL_Texture* texture;
	Vec3 imageSizeWorldCoords;
	bool isCap;
public:
	Body();
	Body(Vec3 pos_, Vec3 vel_, Vec3 accel_, float mass_);
	~Body();
	void Update(float deltaTime);
	void ApplyForce(Vec3 force_);
	void setCenterPoint();
	Vec3 getCenterPoint();
	void GetSpeed(float speed, float angle);
	float GetRotion(float w, float speed,float deltaTime);
	void setRotation(float deltaTime);
	double getRotation() { return rotation; }
	void HandleEvents(const SDL_Event& sdlEvent);
	void Pause();
	Vec3 getPos() { return pos; };
	void setCap(bool isCap_) { isCap = isCap_; }
	bool getCap() { return isCap; }
	void Cap() { isCap = true; }
	void Rel() { isCap = false; }
	void setImage(SDL_Surface* image_) { image = image_; }
	SDL_Surface* getImage(){return image;}
	void setImageSizeWorldCoords(Vec3 imageSizeWorldCoords_){ 
		imageSizeWorldCoords.x = imageSizeWorldCoords_.x;
		imageSizeWorldCoords.y = imageSizeWorldCoords_.y;
		imageSizeWorldCoords.z = imageSizeWorldCoords_.z;
	}
	Vec3 getImageWorldCoords() { return imageSizeWorldCoords;}

	void setTexture(SDL_Texture* texture_) { texture = texture_; }
	SDL_Texture* getTexture() { return texture; }
};


#endif