

#ifndef  SOC_VECTOR_H
#define SOC_VECTOR_H

#include <math.h>
#include <vector>

struct SOC_Vector2
{
	float xVal;
	float yVal;

	SOC_Vector2()
	{
		xVal = 0;
		yVal = 0;
	}

	SOC_Vector2(float newXVal, float newYVal)
	{
		xVal = newXVal;
		yVal = newYVal;
	}

	float magnitude() { return (float)sqrt((double)xVal * (double)xVal + (double)yVal * (double)yVal); }

	float Dot(SOC_Vector2 other)
	{
		float result = (xVal * other.xVal) + (yVal * other.yVal);

		return result;
	}

	float sqrMagnitude()
	{
		return (xVal * xVal + yVal * yVal);
	}

	SOC_Vector2 normalized()
	{
		SOC_Vector2 normalVersion = SOC_Vector2();
		float newMag = magnitude();

		normalVersion.xVal = xVal / newMag;
		normalVersion.yVal = yVal / newMag;

		return normalVersion;
	}
};

SOC_Vector2 operator+(SOC_Vector2 left, SOC_Vector2 right);

SOC_Vector2 operator+=(SOC_Vector2 left, SOC_Vector2 right);

SOC_Vector2 operator-(SOC_Vector2 left, SOC_Vector2 right);

SOC_Vector2 operator-=(SOC_Vector2 left, SOC_Vector2 right);

SOC_Vector2 operator/(SOC_Vector2 left, float right);

SOC_Vector2 operator*(SOC_Vector2 left, float right);

SOC_Vector2 operator*(float left, SOC_Vector2 right);

#endif // ! SOC_VECTOR_H
