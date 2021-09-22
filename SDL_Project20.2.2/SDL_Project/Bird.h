#ifndef BIRD_H
#define BIRD_H
#include "Body.h"

class Bird : public Body {
public:

	
	Bird(Vec3 pos_, Vec3 vel_, Vec3 accel_, float mass_) :

		Body(pos_, vel_, accel_, mass_) {

	}

	//~Bird();
	void setTexture(SDL_Texture* texture_) { texture = texture_; }
	SDL_Texture* getTexture() { return texture; }


private:
	SDL_Texture* texture;


};





#endif

