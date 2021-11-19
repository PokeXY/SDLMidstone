#ifndef PHYSICSOBJECT_H
#define PHYSICSOBJECT_H
#include "Vector.h"
#include "Sphere.h"
#include "MMath.h"

using namespace MATH;

class PhysicsObject {
	friend class Physics;
protected:
	Vec3 pos, vel, accel;
	double mass;
	Sphere boundingSphere;
	double angle, angularVel, angularAccel, rotationalI;
	bool fixedStatus;
	float boundingBoxHeight, boundingBoxWidth;
public:
	PhysicsObject();
	virtual ~PhysicsObject();
public:
	/// Untility functions so small they cane be inlined
	inline void setFixedStatus(const bool fixed_) { fixedStatus = fixed_; }
	inline bool getFixedStatus() { return fixedStatus; }
	inline Sphere getBoundingSphere() { return boundingSphere; }
	inline void setBoundingSphere(const Sphere& sphere_) { boundingSphere = sphere_; }
	inline void setMass(const double mass_) { mass = mass_; }
	inline void setRotationalI(const double rotationalI_) { rotationalI = rotationalI_; }
	inline void setPos(const Vec3& pos_) { pos = pos_; }
	inline Vec3 getPos() { return pos; }
	inline void setVel(const Vec3& vel_) { vel = vel_; }
	inline Vec3 getVel() { return vel; }
	inline void setAccel(const Vec3& accel_) { accel = accel_; }
	inline Vec3 getAccel() { return accel; }
	inline void setAngle(const double angle_) { angle = angle_; }
	inline double getAngle() { return angle; }
	inline void setAngularVel(const double angularVel_) { angularVel = angularVel_; }
	inline double getAngularVel() { return angularVel; }
	inline void setAngularAccel(const double angularAccel_) { angularAccel = angularAccel_; }
	inline double getAngularAccel() { return angularAccel; }
	inline void setBoundingBoxWidth(const float boundingBoxWidth_) { boundingBoxWidth = boundingBoxWidth_; }
	inline float getBoundingBoxWidth() { return boundingBoxWidth; }
	inline void setBoundingBoxHeight(const float boundingBoxHeight_) { boundingBoxHeight = boundingBoxHeight_; }
	inline float getBoundingBoxHeight() { return boundingBoxHeight; }
	//simple physics functions
	inline void applyTorque(const double torque) { angularAccel = torque / rotationalI; }
	inline void applyForce(const Vec3 force) {accel = force / mass; }
};
#endif
