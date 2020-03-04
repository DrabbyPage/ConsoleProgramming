

#ifndef SOC_COLLISION_HULL_2D_H
#define SOC_COLLISION_HULL_2D_H

#include "SOC_VectorMath.h"

#include "SOC_CircleCollisionHull2D.h"
#include "SOC_AABBCollisionHull2D.h"
#include "SOC_OBBCollisionHull2D.h"

enum CollisionType
{
	Circle_Collision_Enum,
	AABB_RECT_COLLISION_Enum,
	OBB_RECT_COLLISION_Enum
};

struct Contact
{
	SOC_Vector2 point;
	SOC_Vector2 normal;
	float restitution;
	float penetration;
};


class Collision
{
public:
	Contact contacts[4];
	int contactCount;
	bool status;
	SOC_Vector2 closingVelocity;
	Collision() {}
};

class SOC_CollsionHull2D
{
public:
	CollisionType type;
	float restitution;
	bool isColliding;

	virtual bool TestCollisionVSSphere(SOC_CircleCollisionHull2D other);
	virtual bool TestCollisionVSAABB(SOC_AABBCollisionHull2D other);
	virtual bool TestCollisionVSOBB(SOC_OBBCollisionHull2D other);

private:
};

#endif