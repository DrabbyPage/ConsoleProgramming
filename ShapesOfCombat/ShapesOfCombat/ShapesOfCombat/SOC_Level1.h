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

private:
	
	int frame;

	float enemyMoveTimer = 1;

	SOC_GameObject* testObject;

	SOC_GameObject* player;

	SOC_GameObject* enemy;
	//SOC_SpriteSheet* spritesheet;
};