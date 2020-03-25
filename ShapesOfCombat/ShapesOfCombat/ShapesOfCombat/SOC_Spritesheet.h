

#ifndef SOC_SPRITE_SHEET_H
#define SOC_SPRITE_SHEET_H

#include <wincodec.h>
#include"SOC_Graphics.h"

class SOC_SpriteSheet
{
public:
	SOC_SpriteSheet(const wchar_t* filename, SOC_Graphics* newGraphics);
	SOC_SpriteSheet(const wchar_t* filename, SOC_Graphics* newGraphics, int spriteWidth, int spriteHeight, int newAmountOfFrames);
	~SOC_SpriteSheet();

	void Draw();
	void Draw(int index, int x, int y);

	void SetSpriteWidth(int newW) { spriteWidth = newW; }
	void SetSpriteHeight(int newH) { spriteHeight = newH; }

	void IncrementFrame() { frame++;}

private:
	SOC_Graphics* graphics;
	ID2D1Bitmap* bmp;
	int spriteWidth, spriteHeight;
	int spriteAccross;
	int frame;
	int amountOfFrames;
};


#endif // !SOC_SPRITE_SHEET_H
