
#include "SOC_GameController.h"
#include "SOC_Graphics.h"
#include "SOC_Level1.h"


void SOC_Level1::Load(HWND newWindowHandle, SOC_Vector2 windowPos)
{
	player = new SOC_GameObject(L"PlayerUp.png", newWindowHandle, windowPos, 64, 64, 1);
	player->AddSprite(L"PlayerRight.png", newWindowHandle, windowPos, 64, 64, 1);
	player->AddSprite(L"PlayerDown.png", newWindowHandle, windowPos, 64, 64, 1);
	player->AddSprite(L"PlayerLeft.png", newWindowHandle, windowPos, 64, 64, 1);

	enemy = new SOC_GameObject(L"SpaceZapEnemyUp.png", newWindowHandle, windowPos, 64, 64, 1);
	enemy->AddSprite(L"SpaceZapEnemyRight.png", newWindowHandle, windowPos, 64, 64, 1);
	enemy->AddSprite(L"SpaceZapEnemyDown.png", newWindowHandle, windowPos, 64, 64, 1);
	enemy->AddSprite(L"SpaceZapEnemyLeft.png", newWindowHandle, windowPos, 64, 64, 1);
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

	graphics->ClearScreen(0.0, 0.0, 0.0);

	
	player->Render();
	//enemy->Render();
	

	graphics->EndDraw();

}

void SOC_Level1::Update(GameInput direction)
{

	// update

	player->ChangeToSprite((int)direction);
	player->SetObjectPos()

}
