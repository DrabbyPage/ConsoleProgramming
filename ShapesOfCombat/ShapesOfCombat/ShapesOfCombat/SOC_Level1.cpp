
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
	enemy->Render();
	

	graphics->EndDraw();

}

void SOC_Level1::Update(float deltaTime, GameInput direction)
{

	// update

	SOC_Vector2 topSpot = graphics->GetWindowSize();
	topSpot.xVal *= 0.5f;
	topSpot.yVal *= 0.25f;
	SOC_Vector2 rightSpot = graphics->GetWindowSize();
	rightSpot.xVal *= 0.75f;
	rightSpot.yVal *= 0.5f;
	SOC_Vector2 botSpot = graphics->GetWindowSize();
	botSpot.xVal *= 0.5f;
	botSpot.yVal *= 0.75f;
	SOC_Vector2 leftSpot = graphics->GetWindowSize();
	leftSpot.xVal *= 0.25f;
	leftSpot.yVal *= 0.5f;


	player->ChangeToSprite((int)direction);
	player->SetObjectPos(graphics->GetWindowSize() / 2);

	if (enemyMoveTimer <= 0)
	{
		enemyMoveTimer = 1;

		int randPos = -1;
		randPos = rand() % 4;

		switch (randPos)
		{
		case 0:
			enemy->SetObjectPos(topSpot);
			enemy->ChangeToSprite((int)GameInput::down);
			break;
		case 1:
			enemy->SetObjectPos(rightSpot);
			enemy->ChangeToSprite((int)GameInput::left);
			break;
		case 2:
			enemy->SetObjectPos(botSpot);
			enemy->ChangeToSprite((int)GameInput::up);
			break;
		case 3:
			enemy->SetObjectPos(leftSpot);
			enemy->ChangeToSprite((int)GameInput::right);
			break;
		}
	}
	else
	{
		enemyMoveTimer -= deltaTime;
	}

}
