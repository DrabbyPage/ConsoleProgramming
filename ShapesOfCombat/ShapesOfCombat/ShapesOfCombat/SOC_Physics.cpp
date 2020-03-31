
#include "SOC_Physics.h"

void SOC_Physics2D::UpdatePosition(float deltaTime)
{
	kinematics.position = kinematics.position + kinematics.velocity * deltaTime;
}

void SOC_Physics2D::UpdateRotation(float deltaTime)
{
	kinematics.rotation = kinematics.rotation + kinematics.angularVelocity * deltaTime;
}