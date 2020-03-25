

#include "SOC_GameObject.h"

SOC_GameObject::SOC_GameObject()
{
	objectPhysics = NULL;
	objectSpriteSheet = NULL;
}

SOC_GameObject::SOC_GameObject(const wchar_t* filename, SOC_Graphics* newGraphics,int frameWidth, int frameHeight, int amountOfFrames)
{
	objectSpriteSheet = new SOC_SpriteSheet(filename, newGraphics, frameWidth, frameHeight, amountOfFrames);
	objectPhysics = new SOC_Physics2D();
}

SOC_GameObject::~SOC_GameObject()
{
	if (objectSpriteSheet)
	{
		delete objectSpriteSheet;
	}
}

void SOC_GameObject::Update()
{

}

void SOC_GameObject::Render()
{

}