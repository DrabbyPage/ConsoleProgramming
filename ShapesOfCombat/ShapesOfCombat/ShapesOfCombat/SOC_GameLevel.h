

#ifndef GAME_LEVEL_H
#define GAME_LEVEL_H

#include "SOC_Graphics.h"

class SOC_GameLevel
{
public:
	virtual void Load(HWND newWinHandle, SOC_Vector2 windowPos) = 0;
	virtual void Unload() = 0;
	virtual void Render() = 0;
	virtual void Update() = 0;

	static void Init(SOC_Graphics* newGraphics)
	{
		graphics = newGraphics;
	}

protected:
	static SOC_Graphics* graphics;

private:
	 
};

#endif