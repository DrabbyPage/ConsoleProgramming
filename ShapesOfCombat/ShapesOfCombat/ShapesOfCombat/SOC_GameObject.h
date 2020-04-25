

#ifndef SOC_GAME_OBJECT_H
#define SOC_GAME_OBJECT_H

#include <wincodec.h>
#include "SOC_Graphics.h"
#include "SOC_Spritesheet.h"

#include "SOC_Physics.h"

class SOC_GameObject
{
public: 
	SOC_GameObject();
	SOC_GameObject(const wchar_t* filename, HWND newWinHandle, SOC_Vector2 windowPos, float frameWidth, float frameHeight, int amountOfFrames);
	~SOC_GameObject();

	void Update();
	void Render();

	void AddSprite(const wchar_t* filename, HWND newWinHandle, SOC_Vector2 windowPos, float frameWidth, float frameHeight, int amountOfFrames);
	void ChangeToSprite(int spriteID);

	void SetObjectPos(SOC_Vector2 newPos) { objectPhysics->SetPosition(newPos); }


private:

	std::vector< SOC_SpriteSheet*> listOfSprites;
	int currentSpriteSheet = 0;

	SOC_Physics2D* objectPhysics;

};

#endif