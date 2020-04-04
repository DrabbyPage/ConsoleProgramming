

#ifndef SOC_PHYSICS_H
#define SOC_PHYSICS_H

#include "SOC_Vector.h"

enum SOC_ObjectType
{
    DISK_INERTIA = 0,
    RECT_INERTIA
};

struct SOC_Kinematic
{
	SOC_Vector2 position;
	SOC_Vector2 velocity;

	float rotation;
	float angularVelocity;
};

class SOC_Physics2D
{
public:
    
	void UpdatePosition(float deltaTime);
	void UpdateRotation(float deltaTime);
	 
	void SetVelocity(SOC_Vector2 newVel) { kinematics.velocity = newVel; }
	void SetAngularVelocity(float newAngVel) { kinematics.angularVelocity = newAngVel; }
    
	SOC_Vector2 GetPosition() { return kinematics.position; }
	SOC_Vector2 GetVelocity() { return kinematics.velocity; }
	float GetRotation() { return kinematics.rotation; }
	float GetAngularRotation() { return kinematics.angularVelocity; }

private:
	SOC_Kinematic kinematics;

};

#endif