

#include "SOC_GameObject.h"
#include <math.h>
#include <iostream>

#define PI 3.14159265f
extern SOC_Graphics* graphics;

SOC_GameObject::SOC_GameObject()
{
	objectPhysics = NULL;
}

SOC_GameObject::SOC_GameObject(const wchar_t* filename, HWND newWinHandle, SOC_Vector2 newWinPos, float frameWidth, float frameHeight, int amountOfFrames)
{

	SOC_SpriteSheet* newSpriteSheet = new SOC_SpriteSheet(filename, graphics, frameWidth, frameHeight, amountOfFrames);
	objectPhysics = new SOC_Physics2D();

	objectPhysics->SetPosition(SOC_Vector2(250, 250));

	listOfSprites.push_back(newSpriteSheet);
	
}

void SOC_GameObject::AddSprite(const wchar_t* filename, HWND newWinHandle, SOC_Vector2 windowPos, float frameWidth, float frameHeight, int amountOfFrames)
{
	SOC_SpriteSheet* newSpriteSheet = new SOC_SpriteSheet(filename, graphics, frameWidth, frameHeight, amountOfFrames);

	listOfSprites.push_back(newSpriteSheet);
}
void SOC_GameObject::ChangeToSprite(int spriteID)
{
	if (spriteID != -1 && spriteID < listOfSprites.size())
	{
		currentSpriteSheet = spriteID;
	}
}


SOC_GameObject::~SOC_GameObject()
{
	if (objectPhysics)
	{
		delete objectPhysics;
	}
}

void SOC_GameObject::Update()
{
	//POINT cursorPos;

	// this is how to get direction to mouse ( if the pos of the window is 0,0)
	SOC_Vector2 objPos = objectPhysics->GetPosition();

	SOC_Vector2 cursorPos = graphics->GetCursorPosFromGraphics();

	SOC_Vector2 diff = SOC_Vector2(cursorPos.yVal - objPos.yVal, cursorPos.xVal - objPos.xVal);

	float newRot = atan2(diff.yVal, diff.xVal) * 180.0f / PI;

	newRot = -newRot + 180;

	std::cout << "rotation: " << newRot << ", ";

	objectPhysics->SetRotation(newRot);
}


void SOC_GameObject::Render()
{

	listOfSprites[currentSpriteSheet]->Draw(objectPhysics->GetPosition().xVal, objectPhysics->GetPosition().yVal, objectPhysics->GetRotation());

	// need some sort of frame counter and/ or timer to switch
	if (listOfSprites[currentSpriteSheet]->GetAmountOfFrames() > 1)
	{
		listOfSprites[currentSpriteSheet]->IncrementFrame();
	}
}

