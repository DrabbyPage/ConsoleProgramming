
#include "SOC_Spritesheet.h"


SOC_SpriteSheet::SOC_SpriteSheet(const wchar_t* filename, SOC_Graphics* newGraphics)
{
	this->graphics = newGraphics;
	bmp = NULL;

	HRESULT hr;

	IWICImagingFactory* wicFactory = NULL;

	hr = CoCreateInstance(CLSID_WICImagingFactory, NULL, CLSCTX_INPROC_SERVER, IID_IWICImagingFactory, (LPVOID*)&wicFactory);

	IWICBitmapDecoder* wicDecoder = NULL;
	hr = wicFactory->CreateDecoderFromFilename(filename, NULL, GENERIC_READ, WICDecodeMetadataCacheOnLoad, &wicDecoder);

	IWICBitmapFrameDecode* wicFrame = NULL;
	hr = wicDecoder->GetFrame(0, &wicFrame);

	IWICFormatConverter* wicConverter = NULL;
	hr = wicFactory->CreateFormatConverter(&wicConverter);

	hr = wicConverter->Initialize(wicFrame, GUID_WICPixelFormat32bppPRGBA, WICBitmapDitherTypeNone, NULL, 0.0, WICBitmapPaletteTypeCustom);

	hr = newGraphics->GetRenderTarget()->CreateBitmapFromWicBitmap(wicConverter, NULL, &bmp);

	if (wicFactory)
	{
		wicFactory->Release();
	}
	if (wicDecoder)
	{
		wicDecoder->Release();
	}
	if (wicConverter)
	{
		wicConverter->Release();
	}
	if (wicFrame)
	{
		wicFrame->Release();
	}

	spriteWidth = bmp->GetSize().width;
	spriteHeight = bmp->GetSize().height;
	spriteAccross = 5;
}

SOC_SpriteSheet::SOC_SpriteSheet(const wchar_t* filename, SOC_Graphics* newGraphics, int newWidth, int newHeight, int newAmountOfFrames):
	SOC_SpriteSheet(filename, newGraphics)
{
	this->spriteWidth = newWidth;
	this->spriteHeight = newHeight;
	this->spriteAccross = bmp->GetSize().width / spriteWidth;
	this->amountOfFrames = newAmountOfFrames;
}

SOC_SpriteSheet::~SOC_SpriteSheet()
{
	if (bmp)
	{
		bmp->Release();
	}
}

void SOC_SpriteSheet::Draw()
{
	graphics->GetRenderTarget()->DrawBitmap(
		bmp,
		D2D1::Rect(0.0f, 0.0f,
			bmp->GetSize().width, bmp->GetSize().height),
		1.0f,
		D2D1_BITMAP_INTERPOLATION_MODE::D2D1_BITMAP_INTERPOLATION_MODE_NEAREST_NEIGHBOR,
		D2D1::RectF(0.0f, 0.0f,
			bmp->GetSize().width, bmp->GetSize().height)
		);
}

void SOC_SpriteSheet::Draw(int index, int x, int y)
{
	// 9:30
	D2D_RECT_F src = D2D1::RectF(
		(float)((index % spriteAccross) * spriteWidth),
		(float)((index / spriteAccross) * spriteHeight),
		(float)((index % spriteAccross) * spriteWidth) + spriteWidth,
		(float)((index / spriteAccross) * spriteHeight) + spriteHeight);

	D2D_RECT_F dest = D2D1::RectF
	(
		x, y, 
		x + spriteWidth,
		y + spriteHeight
		);

	graphics->GetRenderTarget()->DrawBitmap(
		bmp,
		dest,
		1.0f,
		D2D1_BITMAP_INTERPOLATION_MODE::D2D1_BITMAP_INTERPOLATION_MODE_NEAREST_NEIGHBOR,
		src
		);
}
