
#include "SOC_GameLevel.h"

bool SOC_GameLevel::GetGameOver()
{ 
	return gameIsOver;
}

void SOC_GameLevel::SetGameIsOver(bool newBool)
{ 
	gameIsOver = newBool; 
}