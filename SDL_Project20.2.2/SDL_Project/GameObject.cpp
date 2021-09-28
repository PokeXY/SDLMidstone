#include "GameObject.h"

GameObject::GameObject() : texture(nullptr) {}

GameObject::GameObject(SDL_Texture* texture_) : texture(texture_) {
}

GameObject::~GameObject() {}

bool GameObject::OnCreate() { return true; }

void GameObject::OnDestroy() {}

void GameObject::Update(float deltaTime_) {}

void GameObject::Render() const {}

void GameObject::HandleEvents(const SDL_Event & event) {} /// Just a stub