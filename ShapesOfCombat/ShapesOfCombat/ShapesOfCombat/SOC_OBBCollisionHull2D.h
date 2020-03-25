

#ifndef SOC_OBB_COLLISION_H
#define SOC_OBB_COLLISION_H

#include "SOC_Vector.h"

class SOC_OBBCollisionHull2D : public SOC_CollisionHull2D
{
public:
    float rotation;

    SOC_Vector2 position;

    float height;
    float width;

    SOC_Vector2 transformRight = SOC_Vector2(1, 0);
    SOC_Vector2 transformLeft = SOC_Vector2(-1, 0);
    SOC_Vector2 transformUp = SOC_Vector2(0, 1);
    SOC_Vector2 transformDown = SOC_Vector2(0, -1);

    SOC_Vector2 topLeftAxis;
    SOC_Vector2 topRightAxis;
    SOC_Vector2 botLeftAxis;
    SOC_Vector2 botRightAxis;

    SOC_OBBCollisionHull2D()
    {
        rotation = 0;
        position = SOC_Vector2(0, 0);

        height = 0;
        width = 0;

        topLeftAxis = position + (transformUp * (height * 0.5f) - transformRight * (width * 0.5f));
        topRightAxis = position + (transformUp * (height * 0.5f) + transformRight * (width * 0.5f));
        botLeftAxis = position + (transformDown * (height * 0.5f) - transformRight * (width * 0.5f));
        botRightAxis = position + (transformRight * (width * 0.5f) - transformUp * (height * 0.5f));
    }

    SOC_OBBCollisionHull2D(SOC_Vector2 newPos, float newHeight, float newWidth, float newRot)
    {
        rotation = newRot;
        position = newPos;

        height = newHeight;
        width = newWidth;

        topLeftAxis = position + (transformUp * (height * 0.5f) - transformRight * (width * 0.5f));
        topRightAxis = position + (transformUp * (height * 0.5f) + transformRight * (width * 0.5f));
        botLeftAxis = position + (transformDown * (height * 0.5f) - transformRight * (width * 0.5f));
        botRightAxis = position + (transformRight * (width * 0.5f) - transformUp * (height * 0.5f));
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

    bool TestCollisionVSCircle(SOC_CircleCollisionHull2D other)
    {


        // find the min and max components of the obb
        float minX = ChooseMin(topLeftAxis.xVal, ChooseMin(topRightAxis.xVal, ChooseMin(botLeftAxis.xVal, botRightAxis.xVal)));
        float maxX = ChooseMax(topLeftAxis.xVal, ChooseMax(topRightAxis.xVal, ChooseMax(botLeftAxis.xVal, botRightAxis.xVal)));

        float minY = ChooseMin(topLeftAxis.yVal, ChooseMin(topRightAxis.yVal, ChooseMin(botLeftAxis.yVal, botRightAxis.yVal)));
        float maxY = ChooseMax(topLeftAxis.yVal, ChooseMax(topRightAxis.yVal, ChooseMax(botLeftAxis.yVal, botRightAxis.yVal)));

        // calculate closest point by clamping circle center on each dimension
        // Find the vector2 distance between box & circle
        SOC_Vector2 diff = position - other.thisCenter;

        // Normalize that vector
        // multiply the vector by the radius to get the closest point on the circumference
        diff = diff.normalized() * other.radius + other.thisCenter;

        // check for the collision
        return IsIntersectingCircle(minX, maxX, minY, maxY, diff.xVal, diff.yVal);
    }

    static bool IsIntersectingCircle(float r1_minX, float r1_maxX, float r1_minY, float r1_maxY, float circClosestX, float circClosestY)
    {
        bool isIntersecting = false;

        // if the closest point of the circle is within the bounds of the square return true
        if (r1_minX < circClosestX && circClosestX < r1_maxX)
        {
            if (r1_minY < circClosestY && circClosestY < r1_maxY)
            {
                isIntersecting = true;
            }
        }

        return isIntersecting;
    }

    bool TestCollisionVSAABB(SOC_AABBCollisionHull2D other)
    {
        // Same as OBB vs OBB, but only project to ABB up and right normal
        // check the points        
        bool isIntersecting = false;

        //Find out if the rectangles are intersecting by approximating them with rectangles 
        //with no rotation and then use AABB intersection
        //Will make it faster if the probability that the rectangles are intersecting is low
        if (!IsIntersectingAABB_OBB(other))
        {
            return isIntersecting;
        }

        //Find out if the rectangles are intersecting by using the Separating Axis Theorem (SAT)
        isIntersecting = SATRectangleRectangle(other);

        return isIntersecting;
    }

    bool TestCollisionVSOBB(SOC_OBBCollisionHull2D other)
    {
        SOC_OBBCollisionHull2D thisOBB = SOC_OBBCollisionHull2D(position, height, width, rotation);
        // AABB-OBB part 2 twice
        // Call projection function four times, if even one fails, the collision fails

        // take each corner multiply by the non axis aligned box and 

        bool isIntersecting = false;

        //We have just 4 normals because the other 4 normals are the same but in another direction
        //So we only need a maximum of 4 tests if we have rectangles
        //It is enough if one side is not overlapping, if so we know the rectangles are not intersecting

        //Test 1
        SOC_Vector2 normal1 = GetNormal(other.botLeftAxis, other.topLeftAxis);

        if (!IsOverlapping(normal1, other, thisOBB))
        {
            //No intersection is possible!
            return isIntersecting;
        }

        //Test 2
        SOC_Vector2 normal2 = GetNormal(other.topLeftAxis, other.topRightAxis);

        if (!IsOverlapping(normal2, other, thisOBB))
        {
            return isIntersecting;
        }

        //Test 3
        SOC_Vector2 normal3 = GetNormal(botLeftAxis, topLeftAxis);

        if (!IsOverlapping(normal3, other, thisOBB))
        {
            return isIntersecting;
        }

        //Test 4
        SOC_Vector2 normal4 = GetNormal(topLeftAxis, topRightAxis);

        if (!IsOverlapping(normal4, other, thisOBB))
        {
            return isIntersecting;
        }

        //If we have come this far, then we know all sides are overlapping
        //So the rectangles are intersecting!
        isIntersecting = true;

        return isIntersecting;

    }

    bool IsIntersectingAABB_OBB(SOC_AABBCollisionHull2D other)
    {
        bool isIntersecting = false;

        SOC_Vector2 otherTL = other.upLeft;
        SOC_Vector2 otherTR = other.upRight;
        SOC_Vector2 otherBL = other.botLeft;
        SOC_Vector2 otherBR = other.botRight;

        SOC_Vector2 thisTL = topLeftAxis;
        SOC_Vector2 thisTR = topRightAxis;
        SOC_Vector2 thisBL = botLeftAxis;
        SOC_Vector2 thisBR = botRightAxis;

        //Find the min/max values for the AABB algorithm
        float r1_minX = ChooseMin(otherTL.xVal, ChooseMin(otherTR.xVal, ChooseMin(otherBL.xVal, otherBR.xVal)));
        float r1_maxX = ChooseMax(otherTL.xVal, ChooseMax(otherTR.xVal, ChooseMax(otherBL.xVal, otherBR.xVal)));

        float r2_minX = ChooseMin(thisTL.xVal, ChooseMin(thisTR.xVal, ChooseMin(thisBL.xVal, thisBR.xVal)));
        float r2_maxX = ChooseMax(thisTL.xVal, ChooseMax(thisTR.xVal, ChooseMax(thisBL.xVal, thisBR.xVal)));

        float r1_minY = ChooseMin(otherTL.yVal, ChooseMin(otherTR.yVal, ChooseMin(otherBL.yVal, otherBR.yVal)));
        float r1_maxY = ChooseMax(otherTL.yVal, ChooseMax(otherTR.yVal, ChooseMax(otherBL.yVal, otherBR.yVal)));

        float r2_minY = ChooseMin(thisTL.yVal, ChooseMin(thisTR.yVal, ChooseMin(thisBL.yVal, thisBR.yVal)));
        float r2_maxY = ChooseMax(thisTL.yVal, ChooseMax(thisTR.yVal, ChooseMax(thisBL.yVal, thisBR.yVal)));

        if (IsIntersectingAABB(r1_minX, r1_maxX, r1_minY, r1_maxY, r2_minX, r2_maxX, r2_minY, r2_maxY))
        {
            isIntersecting = true;
        }

        return isIntersecting;
    }

    //Intersection: AABB-AABB (Axis-Aligned Bounding Box) - rectangle-rectangle in 2d space with no orientation
    bool IsIntersectingAABB(float r1_minX, float r1_maxX, float r1_minZ, float r1_maxZ, float r2_minX, float r2_maxX, float r2_minZ, float r2_maxZ)
    {
        //If the min of one box in one dimension is greater than the max of another box then the boxes are not intersecting
        //They have to intersect in 2 dimensions. We have to test if box 1 is to the left or box 2 and vice versa
        bool isIntersecting = true;

        //X axis
        if (r1_minX > r2_maxX)
        {
            isIntersecting = false;
        }
        else if (r2_minX > r1_maxX)
        {
            isIntersecting = false;
        }
        //Z axis
        else if (r1_minZ > r2_maxZ)
        {
            isIntersecting = false;
        }
        else if (r2_minZ > r1_maxZ)
        {
            isIntersecting = false;
        }


        return isIntersecting;
    }

    //Find out if 2 rectangles with orientation are intersecting by using the SAT algorithm
    bool SATRectangleRectangle(SOC_AABBCollisionHull2D other)
    {
        SOC_OBBCollisionHull2D thisOBB = SOC_OBBCollisionHull2D(position, height, width, rotation);

        bool isIntersecting = false;

        //We have just 4 normals because the other 4 normals are the same but in another direction
        //So we only need a maximum of 4 tests if we have rectangles
        //It is enough if one side is not overlapping, if so we know the rectangles are not intersecting

        SOC_Vector2 otherTL = other.upLeft;
        SOC_Vector2 otherTR = other.upRight;
        SOC_Vector2 otherBL = other.botLeft;
        SOC_Vector2 otherBR = other.botRight;

        SOC_Vector2 thisTL = topLeftAxis;
        SOC_Vector2 thisTR = topRightAxis;
        SOC_Vector2 thisBL = botLeftAxis;
        SOC_Vector2 thisBR = botRightAxis;

        //Test 1
        SOC_Vector2 normal1 = GetNormal(otherBL, otherTL);

        if (!IsOverlappingABB(normal1, other, thisOBB))
        {
            //No intersection is possible!
            return isIntersecting;
        }

        //Test 2
        SOC_Vector2 normal2 = GetNormal(otherTL, otherTR);

        if (!IsOverlappingABB(normal2, other, thisOBB))
        {
            return isIntersecting;
        }

        //Test 3
        SOC_Vector2 normal3 = GetNormal(thisBL, thisTL);

        if (!IsOverlappingABB(normal3, other, thisOBB))
        {
            return isIntersecting;
        }

        //Test 4
        SOC_Vector2 normal4 = GetNormal(thisTL, thisTR);

        if (!IsOverlappingABB(normal4, other, thisOBB))
        {
            return isIntersecting;
        }

        //If we have come thisOBB far, then we know all sides are overlapping
        //So the rectangles are intersecting!
        isIntersecting = true;

        return isIntersecting;
    }

    //Get the normal from 2 points. This normal is pointing left in the direction start -> end
    //But it doesn't matter in which direction the normal is pointing as long as you have the same
    //algorithm for all edges
    SOC_Vector2 GetNormal(SOC_Vector2 startPos, SOC_Vector2 endPos)
    {
        //The direction
        SOC_Vector2 dir = endPos - startPos;

        //The normal, just flip x and Y and make one negative (don't need to normalize it)
        SOC_Vector2 normal = SOC_Vector2(-dir.yVal, dir.xVal);

        return normal;
    }

    //Is thisOBB side overlapping?
    bool IsOverlapping(SOC_Vector2 normal, SOC_OBBCollisionHull2D other, SOC_OBBCollisionHull2D self)
    {
        bool isOverlapping = false;

        //Project the corners of rectangle 1 onto the normal
        float dot1 = normal.Dot(other.topLeftAxis);
        float dot2 = normal.Dot(other.topRightAxis);
        float dot3 = normal.Dot(other.botLeftAxis);
        float dot4 = normal.Dot(other.botRightAxis);

        //Find the range
        float min1 = ChooseMin(dot1, ChooseMin(dot2, ChooseMin(dot3, dot4)));
        float max1 = ChooseMax(dot1, ChooseMax(dot2, ChooseMax(dot3, dot4)));


        //Project the corners of rectangle 2 onto the normal
        float dot5 = normal.Dot(self.topLeftAxis);
        float dot6 = normal.Dot(self.topLeftAxis);
        float dot7 = normal.Dot(self.botLeftAxis);
        float dot8 = normal.Dot(self.botRightAxis);

        //Find the range
        float min2 = ChooseMin(dot5, ChooseMin(dot6, ChooseMin(dot7, dot8)));
        float max2 = ChooseMax(dot5, ChooseMax(dot6, ChooseMax(dot7, dot8)));


        //Are the ranges overlapping?
        if (min1 <= max2 && min2 <= max1)
        {
            isOverlapping = true;
        }

        return isOverlapping;
    }

    bool IsOverlappingABB(SOC_Vector2 normal, SOC_AABBCollisionHull2D other, SOC_OBBCollisionHull2D self)
    {
        bool isOverlapping = false;

        //Project the corners of rectangle 1 onto the normal
        float dot1 = normal.Dot(other.upLeft);
        float dot2 = normal.Dot(other.upRight);
        float dot3 = normal.Dot(other.botLeft);
        float dot4 = normal.Dot(other.botRight);

        //Find the range
        float min1 = ChooseMin(dot1, ChooseMin(dot2, ChooseMin(dot3, dot4)));
        float max1 = ChooseMax(dot1, ChooseMax(dot2, ChooseMax(dot3, dot4)));


        //Project the corners of rectangle 2 onto the normal
        float dot5 = normal.Dot(self.topLeftAxis);
        float dot6 = normal.Dot(self.topLeftAxis);
        float dot7 = normal.Dot(self.botLeftAxis);
        float dot8 = normal.Dot(self.botRightAxis);

        //Find the range
        float min2 = ChooseMin(dot5, ChooseMin(dot6, ChooseMin(dot7, dot8)));
        float max2 = ChooseMax(dot5, ChooseMax(dot6, ChooseMax(dot7, dot8)));


        //Are the ranges overlapping?
        if (min1 <= max2 && min2 <= max1)
        {
            isOverlapping = true;
        }

        return isOverlapping;
    }
};

#endif