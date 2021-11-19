#include "Physics.h"
#include "VMath.h"

void Physics::SimpleNewtonMotion(PhysicsObject& object, const float deltaTime) {
	object.pos += object.vel * deltaTime + 0.5f * object.accel * deltaTime * deltaTime;
	object.vel += object.accel * deltaTime;
}

void Physics::RigidBodyRotation(PhysicsObject& object, const float deltaTime) {
	object.angle += object.angularVel * deltaTime + 0.5f * object.angularAccel * deltaTime * deltaTime;
	object.angularVel += object.angularAccel * deltaTime;
}

bool Physics::PlaneSphereCollision(const PhysicsObject& object, const Plane& p) {
	float distance = VMath::dot(object.pos, Vec3(p.x, p.y, p.z)) - p.d - object.boundingSphere.r;
	if (distance <= 0) {
		return true;
	}
	else {
		return false;
	}
}

void Physics::PlaneSphereCollisionResponse(PhysicsObject& object, const Plane& p) {
	float e = 1.0f;
	Vec3 normal(p.x, p.y, p.z);
	Vec3 normalizedNormal = MATH::VMath::normalize(normal);
	Vec3 projection = MATH::VMath::dot(-object.vel, normalizedNormal) * normalizedNormal;
	Vec3 newVel = object.vel + 2 * projection;

	float velDirectionCheck = MATH::VMath::dot(projection, normal);   //check if sphere was already moving away from plane
	float angle = acosf(velDirectionCheck / (MATH::VMath::mag(projection)) * (MATH::VMath::mag(normal))) * 180 / M_PI;
	if (angle == 180) {
		return;
	}

	object.setVel(newVel * e);
}

bool Physics::SphereSphereCollision(const PhysicsObject& object1, const PhysicsObject& object2) {
	float distance = VMath::distance(object1.pos, object2.pos) - object1.boundingSphere.r - object2.boundingSphere.r;
	if (distance <= 0) {
		return true;
	}
	else {
		return false;
	}
}

void Physics::SphereSphereCollisionResponse(PhysicsObject& object1, PhysicsObject& object2) {
	float e = 1.0f;
	Vec3 actionLine = Vec3(object1.pos - object2.pos);
	Vec3 actionLineNormalized = MATH::VMath::normalize(actionLine);
	float v1_actionLine = MATH::VMath::dot(object1.vel, actionLineNormalized);
	float v2_actionLine = MATH::VMath::dot(object2.vel, actionLineNormalized);

	if (object1.fixedStatus == true && object2.fixedStatus == true) {    //both spheres are fixed
		return;
	}
	else if (object1.fixedStatus == false && object2.fixedStatus == false) {    //both spheres are dynamic
		if ((v1_actionLine - v2_actionLine) > 0.0f) {    //spheres already moving apart
			return;
		}
		float v1new_actionLine = ((object1.mass - e * object2.mass) * v1_actionLine + (1.0f + e) * object2.mass * v2_actionLine) / (object1.mass + object2.mass);
		float v2new_actionLine = ((object2.mass - e * object1.mass) * v2_actionLine + (1.0f + e) * object1.mass * v1_actionLine) / (object1.mass + object2.mass);
		Vec3 v1new = object1.vel + (v1new_actionLine - v1_actionLine) * actionLineNormalized;
		Vec3 v2new = object2.vel + (v2new_actionLine - v2_actionLine) * actionLineNormalized;
		object1.setVel(v1new);
		object2.setVel(v2new);
	}
	else {
		if (object1.fixedStatus == true) {    //object 1 is fixed sphere
			Vec3 normal = MATH::VMath::normalize(object2.pos - object1.pos);
			Vec3 projection = MATH::VMath::dot(-object2.vel, normal) * normal;

			float velDirectionCheck = MATH::VMath::dot(projection, normal);    //check if sphere was already moving away from fixed sphere
			float angle = acosf(velDirectionCheck / (MATH::VMath::mag(projection)) * (MATH::VMath::mag(normal))) * 180 / M_PI;
			if (angle == 180) {
				return;
			}

			Vec3 newVel = object2.vel + 2 * projection;
			object2.setVel(newVel * e);
		}
		else if (object2.fixedStatus == true) {    //object 2 is fixed sphere
			Vec3 normal = MATH::VMath::normalize(object1.pos - object2.pos);
			Vec3 projection = MATH::VMath::dot(-object1.vel, normal) * normal;

			float velDirectionCheck = MATH::VMath::dot(projection, normal);    //check if sphere was already moving away from fixed sphere
			float angle = acosf(velDirectionCheck / (MATH::VMath::mag(projection)) * (MATH::VMath::mag(normal))) * 180 / M_PI;
			if (angle == 180) {
				return;
			}

			Vec3 newVel = object1.vel + 2 * projection;
			object1.setVel(newVel * e);
		}
	}
}

bool Physics::CircleRectCollision(const PhysicsObject& circle, const PhysicsObject& rect) {
	//absolute distance between center of circle and rectangle
	float circleDistancex = abs(circle.pos.x - rect.pos.x);
	float circleDistancey = abs(circle.pos.y - rect.pos.y);
	//intersection not possible
	if (circleDistancex > (rect.boundingBoxWidth / 2.0f + circle.boundingSphere.r)) { return false; }
	if (circleDistancey > (rect.boundingBoxHeight / 2.0f + circle.boundingSphere.r)) { return false; }
	//must be intersection
	if (circleDistancex <= (rect.boundingBoxWidth / 2.0f + circle.boundingSphere.r)) { return true; }
	if (circleDistancey <= (rect.boundingBoxHeight / 2.0f + circle.boundingSphere.r)) { return true; }
	//check for corner of rectangle intersection
	float cornerDistance_sq = (circleDistancex - rect.boundingBoxWidth / 2.0f) * (circleDistancex - rect.boundingBoxWidth / 2.0f) + 
		(circleDistancey - rect.boundingBoxHeight / 2.0f) * (circleDistancey - rect.boundingBoxHeight / 2.0f);
	return (cornerDistance_sq <= (circle.boundingSphere.r * circle.boundingSphere.r));
}

void Physics::CircleRectCollisionResponse(PhysicsObject& circle, PhysicsObject& rect) {
	float e = 1.0f;
	float halfRectHeight = rect.boundingBoxHeight / 2.0f;
	float halfRectWidth = rect.boundingBoxWidth / 2.0f;
	//circle hitting bottom side of rectangle
	if (rect.pos.x - halfRectWidth <= circle.pos.x && circle.pos.x <= rect.pos.x + halfRectWidth && circle.vel.y > 0.0f) {
		//make sure circle actually trying to leave bottom side of rectangle does not get stuck
		if (circle.pos.y > rect.pos.y) {
			return;
		}
		Vec3 normal(0.0f, -1.0f, 0.0f);
		Vec3 normalizedNormal = MATH::VMath::normalize(normal);
		Vec3 projection = MATH::VMath::dot(-circle.vel, normalizedNormal) * normalizedNormal;
		Vec3 newVel = circle.vel + 2 * projection;

		float velDirectionCheck = MATH::VMath::dot(projection, normal);   //check if sphere was already moving away from plane
		float angle = acosf(velDirectionCheck / (MATH::VMath::mag(projection)) * (MATH::VMath::mag(normal))) * 180 / M_PI;
		if (angle == 180) {
			return;
		}
		circle.setVel(newVel * e);
		while (CircleRectCollision(circle, rect) == true) {
			SimpleNewtonMotion(circle, 0.001);
		}
	}
	//circle hitting top side of rectangle
	else if (rect.pos.x - halfRectWidth <= circle.pos.x && circle.pos.x <= rect.pos.x + halfRectWidth && circle.vel.y < 0.0f) {
		//make sure circle actually trying to leave right side of rectangle does not get stuck
		if (circle.pos.y < rect.pos.y) {
			return;
		}
		Vec3 normal(0.0f, 1.0f, 0.0f);
		Vec3 normalizedNormal = MATH::VMath::normalize(normal);
		Vec3 projection = MATH::VMath::dot(-circle.vel, normalizedNormal) * normalizedNormal;
		Vec3 newVel = circle.vel + 2 * projection;

		float velDirectionCheck = MATH::VMath::dot(projection, normal);   //check if sphere was already moving away from plane
		float angle = acosf(velDirectionCheck / (MATH::VMath::mag(projection)) * (MATH::VMath::mag(normal))) * 180 / M_PI;
		if (angle == 180) {
			return;
		}
		circle.setVel(newVel * e);
		while (CircleRectCollision(circle, rect) == true) {
			SimpleNewtonMotion(circle, 0.001);
		}
	}
	//circle hitting left side of rectangle
	else if (rect.pos.y - halfRectHeight <= circle.pos.y && circle.pos.y <= rect.pos.y + halfRectHeight && circle.vel.x > 0.0f ) {
		//make sure circle actually trying to leave right side of rectangle does not get stuck
		if (circle.pos.x > rect.pos.x) {
			return;
		}
		Vec3 normal(-1.0f, 0.0f, 0.0f);
		Vec3 normalizedNormal = MATH::VMath::normalize(normal);
		Vec3 projection = MATH::VMath::dot(-circle.vel, normalizedNormal) * normalizedNormal;
		Vec3 newVel = circle.vel + 2 * projection;

		float velDirectionCheck = MATH::VMath::dot(projection, normal);   //check if sphere was already moving away from plane
		float angle = acosf(velDirectionCheck / (MATH::VMath::mag(projection)) * (MATH::VMath::mag(normal))) * 180 / M_PI;
		if (angle == 180) {
			return;
		}
		circle.setVel(newVel * e);
		while (CircleRectCollision(circle, rect) == true) {
			SimpleNewtonMotion(circle, 0.001);
		}
	}
	//circle hitting right side of rectangle
	else if (rect.pos.y - halfRectHeight <= circle.pos.y && circle.pos.y <= rect.pos.y + halfRectHeight && circle.vel.x < 0.0f) {
		//make sure circle actually trying to leave left side of rectangle does not get stuck
		if (circle.pos.x < rect.pos.x) {
			return;
		}
		Vec3 normal(1.0f, 0.0f, 0.0f);
		Vec3 normalizedNormal = MATH::VMath::normalize(normal);
		Vec3 projection = MATH::VMath::dot(-circle.vel, normalizedNormal) * normalizedNormal;
		Vec3 newVel = circle.vel + 2 * projection;

		float velDirectionCheck = MATH::VMath::dot(projection, normal);   //check if sphere was already moving away from plane
		float angle = acosf(velDirectionCheck / (MATH::VMath::mag(projection)) * (MATH::VMath::mag(normal))) * 180 / M_PI;
		if (angle == 180) {
			return;
		}
		circle.setVel(newVel * e);
		while (CircleRectCollision(circle, rect) == true) {
			SimpleNewtonMotion(circle, 0.001);
		}
	}
	else {
		return;
	}
}