

#ifndef SOC_GAME_CONTROLLER_H
#define SOC_GAME_CONTROLLER_H

#include "SOC_GameLevel.h"
#include "SOC_Graphics.h"
#include "GameInput.h"

class SOC_GameController
{
public:
	static bool loadingLevel;

	static void Init();

	static void LoadInitialLevel(SOC_GameLevel* level, HWND newWinHandle,SOC_Vector2 newWinPos);
	static void UnloadLevel();

	static void SwitchLevel(SOC_GameLevel* level, HWND newWinHandle, SOC_Vector2 newWinPos);

	static void Render();
	static void Update(float deltaTime, GameInput direction);

	static SOC_GameLevel* GetCurrentLevel() { return currentLevel; }

private:
	SOC_GameController();
	static SOC_GameLevel* currentLevel;
};


#endif // !SOC_GAME_CONTROLLER_H

