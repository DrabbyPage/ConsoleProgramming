

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

	void Update(float deltaTime);
	void Render();

	void AddSprite(const wchar_t* filename, HWND newWinHandle, SOC_Vector2 windowPos, float frameWidth, float frameHeight, int amountOfFrames);
	void ChangeToSprite(int spriteID);

	void SetObjectPos(SOC_Vector2 newPos) { objectPhysics->SetPosition(newPos); }

	bool GetIsActiveInScene() { return isActiveInScene; }
	void SetIsActiveInScene(bool newBool) { isActiveInScene = newBool; }

	int GetCurrentSprite() { return currentSpriteSheet; }

	void SetObjectVelocity(SOC_Vector2 newVel) { objectPhysics->SetVelocity(newVel); }
	SOC_Vector2 GetObjectVelocity() { return objectPhysics->GetVelocity(); }
	void SetObjectPosition(SOC_Vector2 newPos) { objectPhysics->SetPosition(newPos); }
	SOC_Vector2 GetObjectPosition() { return objectPhysics->GetPosition(); }
private:
	bool isActiveInScene = true;

	std::vector< SOC_SpriteSheet*> listOfSprites;
	int currentSpriteSheet = 0;

	SOC_Physics2D* objectPhysics;

};

#endif