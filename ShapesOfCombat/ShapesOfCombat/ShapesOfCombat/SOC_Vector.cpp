
#include "SOC_Vector.h"

SOC_Vector2 operator+(SOC_Vector2 left, SOC_Vector2 right)
{
	SOC_Vector2 newVec2(0, 0);

	newVec2.xVal = left.xVal + right.xVal;
	newVec2.yVal = left.yVal + right.yVal;

	return newVec2;
}

SOC_Vector2 operator+=(SOC_Vector2 left, SOC_Vector2 right)
{
	SOC_Vector2 newVec2(0, 0);

	newVec2.xVal = left.xVal + right.xVal;
	newVec2.yVal = left.yVal + right.yVal;

	return newVec2;
}

SOC_Vector2 operator-(SOC_Vector2 left, SOC_Vector2 right)
{
	SOC_Vector2 newVec2(0, 0);

	newVec2.xVal = left.xVal - right.xVal;
	newVec2.yVal = left.yVal - right.yVal;

	return newVec2;
}

SOC_Vector2 operator-=(SOC_Vector2 left, SOC_Vector2 right)
{
	SOC_Vector2 newVec2(0, 0);

	newVec2.xVal = left.xVal - right.xVal;
	newVec2.yVal = left.yVal - right.yVal;

	return newVec2;
}

SOC_Vector2 operator/(SOC_Vector2 left, float right)
{
	SOC_Vector2 newVec2(0, 0);

	newVec2.xVal = left.xVal / right;
	newVec2.yVal = left.yVal / right;

	return newVec2;
}

SOC_Vector2 operator*(SOC_Vector2 left, float right)
{
	SOC_Vector2 newVec2(0, 0);

	newVec2.xVal = left.xVal * right;
	newVec2.yVal = left.yVal * right;

	return newVec2;
}

SOC_Vector2 operator*(float left, SOC_Vector2 right)
{
	SOC_Vector2 newVec2(0, 0);

	newVec2.xVal = right.xVal * left;
	newVec2.yVal = right.yVal * left;

	return newVec2;
}