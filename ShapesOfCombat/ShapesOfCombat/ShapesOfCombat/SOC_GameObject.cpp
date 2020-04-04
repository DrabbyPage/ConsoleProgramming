

#include "SOC_GameObject.h"

SOC_GameObject::SOC_GameObject()
{
	objectPhysics = NULL;
	objectSpriteSheet = NULL;
	objectGraphics = NULL;
}

SOC_GameObject::SOC_GameObject(const wchar_t* filename, HWND newWinHandle,float frameWidth, float frameHeight, int amountOfFrames)
{
	objectGraphics = new SOC_Graphics();
	objectGraphics->Init(newWinHandle);

	objectSpriteSheet = new SOC_SpriteSheet(filename, objectGraphics, frameWidth, frameHeight, amountOfFrames);
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
	objectGraphics->BeginDraw();

	//objectGraphics->ClearScreen(0, 0, 0);

	objectSpriteSheet->Draw(objectPhysics->GetPosition().xVal, objectPhysics->GetPosition().yVal, objectPhysics->GetRotation());

	//objectSpriteSheet->IncrementFrame();

	objectGraphics->EndDraw();

	
}