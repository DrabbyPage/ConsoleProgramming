#pragma once

#include "SOC_Graphics.h"
#include "SOC_GameLevel.h"
#include "SOC_Spritesheet.h"
#include "SOC_GameObject.h"
#include "GameInput.h"

class SOC_Level1 : public SOC_GameLevel
{
public:
	void Load(HWND newWinHandle, SOC_Vector2 windowPos) override;
	void Unload() override;
	void Render() override;
	void Update(float deltaTime, GameInput direction) override;

	void CreateBullet(GameInput direction, float time);

private:
	
	RECT playerShotRect;

	int frame;
	bool shot = false;

	float totalLevelTime = 0;
	float enemyMoveTimer = 1;
	float originalSeenTimer = 0.7f;
	float enemyAbleToBeSeenTimer = 0.7f;

	SOC_GameObject* player;
	SOC_GameObject* enemy;

	HWND windoeHandler;
	SOC_Vector2 windowPos;
	std::vector<SOC_GameObject*> bullets;
	//SOC_SpriteSheet* spritesheet;
};