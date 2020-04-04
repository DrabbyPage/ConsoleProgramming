

#include "SOC_GameObject.h"
#include <math.h>
#include <iostream>

#define PI 3.14159265f

SOC_GameObject::SOC_GameObject()
{
	objectPhysics = NULL;
	objectSpriteSheet = NULL;
	objectGraphics = NULL;
}

SOC_GameObject::SOC_GameObject(const wchar_t* filename, HWND newWinHandle, SOC_Vector2 newWinPos, float frameWidth, float frameHeight, int amountOfFrames)
{
	objectGraphics = new SOC_Graphics();
	objectGraphics->SetWindowPos(newWinPos);
	objectGraphics->Init(newWinHandle);

	objectSpriteSheet = new SOC_SpriteSheet(filename, objectGraphics, frameWidth, frameHeight, amountOfFrames);
	objectPhysics = new SOC_Physics2D();

	objectPhysics->SetPosition(SOC_Vector2(250, 250));
	
}

SOC_GameObject::~SOC_GameObject()
{
	if (objectSpriteSheet)
	{
		delete objectSpriteSheet;
	}
	if (objectPhysics)
	{
		delete objectPhysics;
	}
	if (objectGraphics)
	{
		delete objectGraphics;
	}
}

void SOC_GameObject::Update()
{
	//POINT cursorPos;

	// this is how to get direction to mouse ( if the pos of the window is 0,0)
	SOC_Vector2 objPos = objectPhysics->GetPosition();

	SOC_Vector2 cursorPos = objectGraphics->GetCursorPosFromGraphics();

	SOC_Vector2 diff = SOC_Vector2(cursorPos.yVal - objPos.yVal, cursorPos.xVal - objPos.xVal);

	float newRot = atan2(diff.yVal, diff.xVal) * 180.0f / PI;

	newRot = -newRot + 180;

	std::cout << "rotation: " << newRot << ", ";

	objectPhysics->SetRotation(newRot);
}

void SOC_GameObject::BeginDrawing()
{
	objectGraphics->BeginDraw();
}


void SOC_GameObject::ClearScreenBeforeRender(float r, float g, float b)
{
	objectGraphics->ClearScreen(r, g, b);
}

void SOC_GameObject::Render()
{
	objectSpriteSheet->Draw(objectPhysics->GetPosition().xVal, objectPhysics->GetPosition().yVal, objectPhysics->GetRotation());

	// need some sort of frame counter and/ or timer to switch
	if (objectSpriteSheet->GetAmountOfFrames() > 1)
	{
		objectSpriteSheet->IncrementFrame();
	}
}

void SOC_GameObject::EndDrawing()
{
	objectGraphics->EndDraw();
}
