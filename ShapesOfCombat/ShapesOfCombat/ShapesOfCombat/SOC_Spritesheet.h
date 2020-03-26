

#ifndef SOC_SPRITE_SHEET_H
#define SOC_SPRITE_SHEET_H

#include <wincodec.h>
#include"SOC_Graphics.h"

class SOC_SpriteSheet
{
public:
	SOC_SpriteSheet(const wchar_t* filename, SOC_Graphics* newGraphics);
	SOC_SpriteSheet(const wchar_t* filename, SOC_Graphics* newGraphics, float spriteWidth, float spriteHeight, int newAmountOfFrames);
	~SOC_SpriteSheet();

	void Draw();
	void Draw(float x, float y);

	void SetSpriteWidth(float newW) { spriteWidth = newW; }
	void SetSpriteHeight(float newH) { spriteHeight = newH; }

	void IncrementFrame() { frame = frame + 1; frame = frame % amountOfFrames; }

	int GetAmountOfFrames() { return amountOfFrames; }

private:
	SOC_Graphics* graphics;
	ID2D1Bitmap* bmp;
	float spriteWidth, spriteHeight;
	int spriteAccross;
	int frame;
	int amountOfFrames;
};


#endif // !SOC_SPRITE_SHEET_H
