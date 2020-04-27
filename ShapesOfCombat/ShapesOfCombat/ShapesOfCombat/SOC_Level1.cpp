
#include "SOC_GameController.h"
#include "SOC_Graphics.h"
#include "SOC_Level1.h"
#include <ctime> 


void SOC_Level1::Load(HWND newWindowHandle, SOC_Vector2 newWindowPos)
{
	player = new SOC_GameObject(L"PlayerUp.png", newWindowHandle, newWindowPos, 64, 64, 1);
	player->AddSprite(L"PlayerRight.png", newWindowHandle, newWindowPos, 64, 64, 1);
	player->AddSprite(L"PlayerDown.png", newWindowHandle, newWindowPos, 64, 64, 1);
	player->AddSprite(L"PlayerLeft.png", newWindowHandle, newWindowPos, 64, 64, 1);

	enemy = new SOC_GameObject(L"SpaceZapEnemyUp.png", newWindowHandle, newWindowPos, 64, 64, 1);
	enemy->AddSprite(L"SpaceZapEnemyRight.png", newWindowHandle, newWindowPos, 64, 64, 1);
	enemy->AddSprite(L"SpaceZapEnemyDown.png", newWindowHandle, newWindowPos, 64, 64, 1);
	enemy->AddSprite(L"SpaceZapEnemyLeft.png", newWindowHandle, newWindowPos, 64, 64, 1);

	windoeHandler = newWindowHandle;
	windowPos = newWindowPos;
	frame = 0;
}

void SOC_Level1::CreateBullet(GameInput direction, float time)
{
	SOC_GameObject* newBullet = new SOC_GameObject(L"EnemyBullet.png", windoeHandler, windowPos, 64, 64, 1);

	SOC_Vector2 newVel = SOC_Vector2(0, 0);
	SOC_Vector2 newPos = SOC_Vector2(0, 0);

	float adjustment = 32;

	SOC_Vector2 topSpot = graphics->GetWindowSize();
	topSpot.xVal *= 0.5f;
	topSpot.yVal *= 0.1f;
	topSpot.yVal += adjustment;
	SOC_Vector2 rightSpot = graphics->GetWindowSize();
	rightSpot.xVal *= 0.85f;
	rightSpot.yVal *= 0.5f;
	rightSpot.xVal -= adjustment;
	SOC_Vector2 botSpot = graphics->GetWindowSize();
	botSpot.xVal *= 0.5f;
	botSpot.yVal *= 0.9f;
	botSpot.yVal -= adjustment;
	SOC_Vector2 leftSpot = graphics->GetWindowSize();
	leftSpot.xVal *= 0.15f;
	leftSpot.yVal *= 0.5f;
	leftSpot.xVal += adjustment;

	float moveSpeed = 100 + time * 10.0f;

	if(moveSpeed >=700)
	{
		moveSpeed = 700;
	}

	switch (direction)
	{
	case GameInput::up:
	{
		newVel = SOC_Vector2(0, -moveSpeed);
		newPos = botSpot;
		break;
	}
	case GameInput::down:
	{
		newVel = SOC_Vector2(0, moveSpeed);
		newPos = topSpot;
		break;
	}
	case GameInput::left :
	{
		newVel = SOC_Vector2(-moveSpeed, 0);
		newPos = rightSpot;
		break;
	}
	case GameInput::right:
	{
		newVel = SOC_Vector2(moveSpeed, 0);
		newPos = leftSpot;
		break;
	}
	}

	newBullet->SetObjectVelocity(newVel);
	newBullet->SetObjectPosition(newPos);

	bullets.push_back(newBullet);
}

void SOC_Level1::Unload()
{
	if (player != nullptr)
	{
		delete player;
	}

	if (enemy != nullptr)
	{
		delete enemy;
	}

	bullets.clear();
}

void SOC_Level1::Render()
{
	graphics->BeginDraw();

	graphics->ClearScreen(0.0, 0.0, 0.0);

	
	player->Render();


	graphics->DrawRectangle(player->GetObjectPosition().xVal, player->GetObjectPosition().yVal, 64, 64, 1, 1, 0, 1);

	enemy->Render();

	for (int i = 0; i < bullets.size(); i++)
	{
		if (bullets[i] != nullptr)
			bullets[i]->Render();
	}
	

	graphics->EndDraw();

}

void SOC_Level1::Update(float deltaTime, GameInput direction)
{

	// update
	totalLevelTime += deltaTime;

	SOC_Vector2 topSpot = graphics->GetWindowSize();
	topSpot.xVal *= 0.5f;
	topSpot.yVal *= 0.1f;
	SOC_Vector2 rightSpot = graphics->GetWindowSize();
	rightSpot.xVal *= 0.85f;
	rightSpot.yVal *= 0.5f;
	SOC_Vector2 botSpot = graphics->GetWindowSize();
	botSpot.xVal *= 0.5f;
	botSpot.yVal *= 0.9f;

	SOC_Vector2 leftSpot = graphics->GetWindowSize();
	leftSpot.xVal *= 0.15f;
	leftSpot.yVal *= 0.5f;


	player->ChangeToSprite((int)direction);
	player->SetObjectPos(graphics->GetWindowSize() / 2);

	float closestPos = 1000000000;

	switch (direction)
	{
	case GameInput::up:
	{
		for (int i = 0; i < bullets.size(); i++)
		{
			SOC_Vector2 distToBullet = bullets[i]->GetObjectPosition() - player->GetObjectPosition();

			if (bullets[i]->GetObjectPosition().yVal > player->GetObjectPosition().yVal+3 &&
				distToBullet.magnitude() < closestPos)
			{

			}
		}
	}
	case GameInput::down:
	{

	}
	case GameInput::left:
	{

	}
	case GameInput::right:
	{

	}
	}

	int shoot = rand() % 3;

	if (enemyAbleToBeSeenTimer <= 0)
	{
		enemyAbleToBeSeenTimer = originalSeenTimer;
		enemy->SetIsActiveInScene(false);
	}
	else
	{
		enemyAbleToBeSeenTimer -= deltaTime;
	}

	if (enemyMoveTimer <= 0)
	{
		enemy->SetIsActiveInScene(true);

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
		if (shoot == 2)
		{
			CreateBullet((GameInput)enemy->GetCurrentSprite(), totalLevelTime);
		}
	}
	else
	{
		enemyMoveTimer -= deltaTime;
	}

	for (int i = 0; i < bullets.size(); i++)
	{
		bullets[i]->Update(deltaTime);

		SOC_Vector2 diff = player->GetObjectPosition() - bullets[i]->GetObjectPosition();

		if (diff.magnitude() <= 32)
		{
			bullets.erase(bullets.begin() + i);
		}
	}

}
