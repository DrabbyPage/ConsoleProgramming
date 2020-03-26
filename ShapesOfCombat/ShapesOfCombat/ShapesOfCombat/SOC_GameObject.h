

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
	SOC_GameObject(const wchar_t* filename, SOC_Graphics* newGraphics,float frameWidth, float frameHeight, int amountOfFrames);
	~SOC_GameObject();

	void Update();
	void Render();

private:

	SOC_SpriteSheet* objectSpriteSheet;
	SOC_Physics2D* objectPhysics;
};

#endif