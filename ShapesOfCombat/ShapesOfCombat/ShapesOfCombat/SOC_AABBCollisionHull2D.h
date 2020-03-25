

#ifndef SOC_AABB_COLLISION_H
#define SOC_AABB_COLLISION_H

#include "SOC_Vector.h"

class SOC_AABBCollisionHull2D : public SOC_CollisionHull2D
{
public:

    SOC_Vector2 position;
    float height, width;

    SOC_Vector2 upLeft = SOC_Vector2(position.xVal - width * 0.5f, position.yVal + height * 0.5f);
    SOC_Vector2 upRight = SOC_Vector2(position.xVal + width * 0.5f, position.yVal + height * 0.5f);
    SOC_Vector2 botLeft = SOC_Vector2(position.xVal - width * 0.5f, position.yVal - height * 0.5f);
    SOC_Vector2 botRight = SOC_Vector2(position.xVal + width * 0.5f, position.yVal - height * 0.5f);

    SOC_AABBCollisionHull2D()
    {
        position = SOC_Vector2(0, 0);
        height = 0;
        width = 0;
    }

    SOC_AABBCollisionHull2D(SOC_Vector2 newVec, float newHeight, float newWidth)
    {
        position = newVec;
        height = newHeight;
        width = newWidth;
    }

    SOC_AABBCollisionHull2D(float newXVal, float newYVal, float newHeight, float newWidth)
    {
        position = SOC_Vector2(newXVal, newYVal);
        height = newHeight;
        width = newWidth;
    }

    ~SOC_AABBCollisionHull2D()
    {

    }

    float ChooseMax(float left, float right)
    {
        if (left > right)
        {
            return left;
        }
        else
        {
            return right;
        }
    }

    float ChooseMin(float left, float right)
    {
        if (left < right)
        {
            return left;
        }
        else
        {
            return right;
        }
    }

    // FOR SUCCESSFUL COLLISION, CHANGE COLOR
    bool TestCollisionVSCircle(SOC_CircleCollisionHull2D other)
    {
        // cam did this part

        float circleX = other.thisCenter.xVal;
        float circleY = other.thisCenter.yVal;
        float circleRadius = other.radius;

        float rectX = position.xVal;
        float rectY = position.yVal;

        float DeltaX = circleX - ChooseMax(rectX, ChooseMin(circleX, rectX + width * 0.5f));
        float DeltaY = circleY - ChooseMax(rectY, ChooseMin(circleY, rectY + height * 0.5f));
        return (DeltaX * DeltaX + DeltaY * DeltaY) < (circleRadius * circleRadius);

    }

    bool TestCollisionVSAABB(SOC_AABBCollisionHull2D other)
    {
        // for each dimension, max extent of A greater than min extent of B

        // position - 1/2(length or width) for min point in x or y
        float thisXMin = position.xVal - width * 0.5f;

        // position + 1/2(length or width) for max point in x or y
        float thisXMax = position.xVal + width * 0.5f;

        // position - 1/2(length or width) for min point in x or y
        float thisYMin = position.yVal - height * 0.5f;

        // position + 1/2(length or width) for max point in x or y
        float thisYMax = position.yVal + height * 0.5f;

        // position - 1/2(length or width) for min point in x or y
        float otherXMin = other.position.xVal - width * 0.5f;

        // position + 1/2(length or width) for max point in x or y
        float otherXMax = other.position.xVal + width * 0.5f;

        // position - 1/2(length or width) for min point in x or y
        float otherYMin = other.position.yVal - height * 0.5f;

        // position + 1/2(length or width) for max point in x or y
        float otherYMax = other.position.yVal + height * 0.5f;


        // check which min is greater, greater min becomes the one, other becomes other
        // if one max.x < other max.x && one max.x > other min.x
        if (otherXMin < thisXMax && thisXMax < otherXMax)
        {
            // if this passes, check same thing with y
            if (otherYMin < thisYMax && thisYMax < otherYMax)
            {
                return true;
            }
            else if (otherYMin < thisYMin && thisYMin < otherYMax)
            {
                return true;
            }
        }

        // check which min is greater, greater min becomes the one, other becomes other
        // if one min.x < other max.x && one min.x > other min.x
        if (otherXMin < thisXMin && thisXMin < otherXMax)
        {
            // if this passes, check same thing with y
            if (otherYMin < thisYMax && thisYMax < otherYMax)
            {
                return true;
            }
            else if (otherYMin < thisYMin && thisYMin < otherYMax)
            {
                return true;
            }
        }


        return false;
    }

    bool TestCollisionVSOBB(SOC_OBBCollisionHull2D other)
    {
        // Same as above twive
        // first, test AABB vs max extents of OBB
        // then, multiply by OBB inverse matrix, do test again 

        // Same as OBB vs OBB, but only project to ABB up and right normal
        // check the points

        SOC_AABBCollisionHull2D thisAABB = SOC_AABBCollisionHull2D(position, height, width);
        thisAABB.upLeft = SOC_Vector2(position.xVal - width * 0.5f, position.yVal + height * 0.5f);
        thisAABB.upRight = SOC_Vector2(position.xVal + width * 0.5f, position.yVal + height * 0.5f);
        thisAABB.botLeft = SOC_Vector2(position.xVal - width * 0.5f, position.yVal - height * 0.5f);
        thisAABB.botRight = SOC_Vector2(position.xVal + width * 0.5f, position.yVal - height * 0.5f);

        return other.TestCollisionVSAABB(thisAABB);
    }
};

#endif