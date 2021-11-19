#ifndef PHYSICS_H
#define PHYSICS_H
#include "PhysicsObject.h"
#include "Plane.h"

class Physics {
public:

	static void SimpleNewtonMotion(PhysicsObject& object, const float deltaTime);
	static void RigidBodyRotation(PhysicsObject& object, const float deltaTime);
	static bool PlaneSphereCollision(const PhysicsObject& object, const Plane& p);
	static void PlaneSphereCollisionResponse(PhysicsObject& object, const Plane& p);
	static bool SphereSphereCollision(const PhysicsObject& object1, const PhysicsObject& object2);
	static void SphereSphereCollisionResponse(PhysicsObject& object1, PhysicsObject& object2);
	static bool CircleRectCollision(const PhysicsObject& circle, const PhysicsObject& rect);
	static void CircleRectCollisionResponse(PhysicsObject& circle, PhysicsObject& rect);
};

#endif
