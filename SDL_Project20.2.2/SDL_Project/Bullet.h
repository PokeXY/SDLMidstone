#ifndef BULLET_H
#define BULLET_H

#include "GameObject.h"

class Bullet : public GameObject 
{
private:
	int remainingBounces;

public:
	Bullet();
	~Bullet();

	float getRemainingBounces() { return remainingBounces; }
	void setRemainingBounces(int remainingBounces_) { remainingBounces = remainingBounces_; }
};

#endif