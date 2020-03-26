#pragma once

#include "SOC_Graphics.h"
#include "SOC_GameLevel.h"
#include "SOC_Spritesheet.h"
#include "SOC_GameObject.h"

class SOC_Level1 : public SOC_GameLevel
{
public:
	void Load() override;
	void Unload() override;
	void Render() override;
	void Update() override;

private:
	float y;
	float ySpeed;
	
	int frame;

	SOC_GameObject* testObject;
	//SOC_SpriteSheet* spritesheet;
};