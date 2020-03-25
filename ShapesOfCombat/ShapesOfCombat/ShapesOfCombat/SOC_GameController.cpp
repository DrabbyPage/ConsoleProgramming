

#include "SOC_GameController.h"

SOC_GameLevel* SOC_GameController::currentLevel;
bool SOC_GameController::loadingLevel = false;

void SOC_GameController::LoadInitialLevel(SOC_GameLevel* level)
{
	SOC_GameController::loadingLevel = true;

	currentLevel = level;
	currentLevel->Load();

	loadingLevel = false;
}

void SOC_GameController::SwitchLevel(SOC_GameLevel* level)
{
	loadingLevel = true;

	currentLevel->Unload();
	level->Load();
	delete currentLevel;
	currentLevel = level;

	loadingLevel = false;
}

void SOC_GameController::Render()
{
	currentLevel->Render();
}

void SOC_GameController::Update()
{
	currentLevel->Update();
}

void SOC_GameController::Init()
{
	loadingLevel = true;
	currentLevel = 0;
}
