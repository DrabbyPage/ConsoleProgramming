
#include "SOC_GameController.h"
#include "SOC_Graphics.h"
#include "SOC_Level1.h"


void SOC_Level1::Load(HWND newWindowHandle)
{
	y = ySpeed = 0;
	//spritesheet = new SOC_SpriteSheet(L"test.png", graphics,60,60);
	testObject = new SOC_GameObject(L"Player_Image.png", newWindowHandle, 64, 64, 1);
	frame = 0;
}

void SOC_Level1::Unload()
{
	if (testObject)
	{
		delete testObject;
	}
}

void SOC_Level1::Render()
{
	graphics->BeginDraw();

	//graphics->ClearScreen(0.0, 0.0, 0.0);

	graphics->DrawCircle(375, y, 50, 1, 0.5, 0.5, 1.0);

	//spritesheet->Draw(frame%10, 100, 100);
	testObject->Render();

	
}

void SOC_Level1::Update()
{
	testObject->Update();

	// update
	ySpeed += 1.0f;
	y += ySpeed;

	if (y > 600)
	{
		y = 600;
		ySpeed = -30;
	}

	frame++;
}
