

#ifndef SOC_PHYSICS_H
#define SOC_PHYSICS_H

#include "SOC_Vector.h"

enum SOC_ObjectType
{
    DISK_INERTIA = 0,
    RECT_INERTIA
};

struct kinematic
{
	SOC_Vector2 position;
	SOC_Vector2 velocity;

	float rotation;
	float angularVelocity;
};

class SOC_Physics2D
{
public:
    SOC_Physics2D()
    {
        // set the basic stats
        position = SOC_Vector2(0, 0);
        velocity = SOC_Vector2(0, 0);
        acceleration = SOC_Vector2(0, 0);

        // set the rotational stats
        rotation = 0;
        angularVelocity = 0;
        angularAcceleration = 0;

        // set inv mass and mass
        SetMass(0);

        // make the forces 0
        force = SOC_Vector2(0, 0);
        angularForce = SOC_Vector2(0, 0);

    }

    SOC_Physics2D(float newPosX, float newPosY, float newRot, float newMass)
    {
        position.xVal = newPosX;
        position.yVal = newPosY;

        velocity = SOC_Vector2(0, 0);
        acceleration = SOC_Vector2(0, 0);

        SetMass(newMass);

        // set the rotational stats
        rotation = newRot;
        angularVelocity = 0;
        angularAcceleration = 0;


        // make the forces 0
        force = SOC_Vector2(0, 0);
        angularForce = SOC_Vector2(0, 0);
    }

    ~SOC_Physics2D()
    {

    }

    void AddForce(SOC_Vector2 newForce)
    {
        // D'Alembert
        force += newForce;
    }

    void AddAngRotationForce(SOC_Vector2 newAngRotForce)
    {
        angularForce += newAngRotForce;
    }

    void UpdateAcceleration()
    {
        // Newton 2
        acceleration = force * massInv;

        force.xVal = 0;
        force.yVal = 0;
    }

    // positional and rotational update functions
    void UpdatePositionKinematic(float dt)
    {
        position += velocity * dt + 0.5f * (acceleration * dt * dt);
        velocity += acceleration * dt;
    }

    void UpdateRotationKinematic(float dt)
    {
        rotation += angularVelocity * dt + 0.5f * angularAcceleration * dt * dt;
        angularVelocity += angularAcceleration * dt;
    }

    // inertia and angular acc update functions
    void UpdateInertia()
    {
        switch (objType)
        {
        case DISK_INERTIA: // disk
            momentOfInertia = CalcDiskInertia(diskRadius);
            break;
        case RECT_INERTIA: // rect
            momentOfInertia = CalcRectangleInertia(rectHeight, rectWidth);
            break;
        }

        invInertia = 1 / momentOfInertia;
    }

    void UpdateAngAcc()
    {
        //Debug.Log(momentOfInertia);
        angularAcceleration = torque * invInertia;
        torque = 0;
    }

    float CalcDiskInertia(float diskRadius)
    {
        float inertia = 0.0f;
        inertia = 0.5f * mass * diskRadius * diskRadius;
        return inertia;
    }

    float CalcRectangleInertia(float rectHeight, float rectWidth)
    {
        float inertia = 0.0f;
        inertia = (1.0f / 12.0f) * mass * (rectHeight * rectHeight + rectWidth * rectWidth);
        return inertia;
    }

    //mutators:
    void SetMass(float newMass)
    {
        //mass = newMass > 0.0f ? newMass: 0.0f;
        if (newMass > 0)
        {
            mass = newMass;
        }
        massInv = mass > 0 ? 1.0f / mass : 0.0f;
    }

    void SetAcceleration(SOC_Vector2 newAcc)
    {
        acceleration = newAcc;
    }

    // accessors:
    float GetMass()
    {
        return mass;
    }

    float GetInvMass()
    {
        return massInv;
    }

private:
    // basics physical components
    SOC_Vector2 position, velocity, acceleration;
    float rotation, angularVelocity, angularAcceleration;

    // including mass
    float mass, massInv;

    // forces
    SOC_Vector2 force;

    // angular force
    float torque;
    float momentOfInertia;
    float invInertia;
    SOC_Vector2 pointOfAppliedForce;
    SOC_Vector2 angularForce;

    // object type
    SOC_ObjectType objType;

    // inertia object stats
    float rectHeight, rectWidth;
    float diskRadius;

    //SOC_CollsionHull2D collisionHull;
};

#endif