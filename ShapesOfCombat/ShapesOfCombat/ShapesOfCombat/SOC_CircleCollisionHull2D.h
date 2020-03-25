

#ifndef SOC_CIRCLE_COLLISION_H
#define SOC_CIRCLE_COLLISION_H

#include "SOC_Vector.h"

class SOC_CircleCollisionHull2D : public SOC_CollisionHull2D
{
public:
    SOC_Vector2 thisCenter;
    float radius;

    SOC_CircleCollisionHull2D()
    {
        type = Circle_Collision_Enum;
        radius = 0;
        thisCenter = SOC_Vector2(0, 0);
    }

    SOC_CircleCollisionHull2D(SOC_Vector2 newPos, float newRadius)
    {
        type = Circle_Collision_Enum;
        radius = newRadius;
        thisCenter = newPos;
    }

    ~SOC_CircleCollisionHull2D()
    {

    }

    bool TestCollisionVSCircle(SOC_CircleCollisionHull2D other)
    {
        //ROB
        // Passes if distance between centers <= sum of radii
        // optimized collision passes if (distance between centers) squared <= (sum of radii) squared
        // 1. Get the two centers
        SOC_Vector2 otherCenter = other.thisCenter;

        // 2. difference between centers
        SOC_Vector2 distanceVec = otherCenter - thisCenter;

        //float distance = (otherCenter.x - thisCenter.x) * (otherCenter.x - thisCenter.x) 
        //               + (otherCenter.y - thisCenter.y) * (otherCenter.y - thisCenter.y);
        //distance *= distance;

        // 3. distance squared = dot(diff, diff)
        float distance = distanceVec.Dot(distanceVec);

        // 4. Sum of radii
        float totalRadii = radius + other.radius;

        // 5. square sum
        totalRadii *= totalRadii;

        // 6. Do the test: distSqr <= sumSqr
        if (distance <= totalRadii)
        {
            return true;
        }

        return false;
    }

    bool TestCollisionVSAABB(SOC_AABBCollisionHull2D other)
    {
        // calculate closest point by clamping circle center on each dimension
        // Find the vector2 distance between box & circle
        // Normalize that vector
        // multiply the vector by the radius to get the closest point on the circumference
        // Check if closest point is within box bounds
        // pass if closest point vs. circle passes
        SOC_CircleCollisionHull2D thisCircle = SOC_CircleCollisionHull2D(thisCenter, radius);

        return other.TestCollisionVSCircle(thisCircle);
    }

    bool TestCollisionVSOBB(SOC_OBBCollisionHull2D other)
    {
        // Same as above, but first...
        // transform circle position by multiplying by box world matrix inverse
        // Find four points on circle, pos.x + cos(a), pos.x - cos(a), pos.y + sin(a), pos.y - sin(a)
        // Project four points on box normal, project box maxes and mins on circle normal
        // Run AABB test
        SOC_CircleCollisionHull2D thisCircle = SOC_CircleCollisionHull2D(thisCenter, radius);

        return other.TestCollisionVSCircle(thisCircle);
    }
};

#endif