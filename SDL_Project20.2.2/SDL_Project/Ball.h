#ifndef BALL_H
#define BALL_H
#include "Body.h"

class Ball : public Body {
public:

	
	Ball(Vec3 pos_, Vec3 vel_, Vec3 accel_, float mass_) :

		Body(pos_, vel_, accel_, mass_) {

	}

	~Ball();
	void colUpdate(float delatTime, Ball Isac);
	void setTexture(SDL_Texture* texture_) { texture = texture_; }
	SDL_Texture* getTexture() { return texture; }


private:
	SDL_Texture* texture;


};





#endif
