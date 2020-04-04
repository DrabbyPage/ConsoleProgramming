

#ifndef SOC_GAME_CONTROLLER_H
#define SOC_GAME_CONTROLLER_H

#include "SOC_GameLevel.h"
#include "SOC_Graphics.h"

class SOC_GameController
{
public:
	static bool loadingLevel;

	static void Init();

	static void LoadInitialLevel(SOC_GameLevel* level, HWND newWinHandle,SOC_Vector2 newWinPos);
	static void SwitchLevel(SOC_GameLevel* level, HWND newWinHandle, SOC_Vector2 newWinPos);

	static void Render();
	static void Update();

private:
	SOC_GameController();
	static SOC_GameLevel* currentLevel;
};


#endif // !SOC_GAME_CONTROLLER_H

