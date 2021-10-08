#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include "SDL_image.h"
#include "PhysicsObject.h"

using namespace MATH;

class GameObject : public PhysicsObject {

private:
	SDL_Texture* texture;

public:
	GameObject();
	GameObject(SDL_Texture* texture_);
	~GameObject();

	virtual bool OnCreate();
	virtual void OnDestroy();
	virtual void Update(const float deltaTime_);
	virtual void Render() const;
	virtual void HandleEvents(const SDL_Event& event);

	void setTexture(SDL_Texture* texture_) { texture = texture_; }
	SDL_Texture* getTexture() { return texture; }
};

#endif
