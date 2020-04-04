
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
	spriteAccross = (int)(bmp->GetSize().width / spriteWidth);
	amountOfFrames = 1;
	frame = 0;
}

SOC_SpriteSheet::SOC_SpriteSheet(const wchar_t* filename, SOC_Graphics* newGraphics, float newWidth, float newHeight, int newAmountOfFrames):
	SOC_SpriteSheet(filename, newGraphics)
{
	this->frame = 0;
	this->spriteWidth = newWidth;
	this->spriteHeight = newHeight;
	this->spriteAccross = (int)(bmp->GetSize().width / spriteWidth);
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

void SOC_SpriteSheet::Draw(float x, float y, float rotation)
{
	// 9:30
	D2D_RECT_F src;

	/*
    // Apply the rotation transform to the render target.
    m_pRenderTarget->SetTransform(
        D2D1::Matrix3x2F::Rotation(
            45.0f,
            D2D1::Point2F(468.0f, 331.5f))
        );
	*/
	if (amountOfFrames > 1)
	{
		src = D2D1::RectF(
			((frame / spriteAccross) * spriteHeight),
			((frame % spriteAccross) * spriteWidth) + spriteWidth,
			((frame % spriteAccross) * spriteWidth),
			((frame / spriteAccross) * spriteHeight) + spriteHeight
			);

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

		graphics->GetRenderTarget()->SetTransform(D2D1::Matrix3x2F::Rotation(rotation, D2D1::Point2F(x, y)));
	}
	else
	{
		D2D_RECT_F dest = D2D1::RectF
		(
			x - spriteWidth / 2,
			y - spriteHeight / 2,
			x + spriteWidth / 2,
			y + spriteHeight / 2
			);

		graphics->GetRenderTarget()->DrawBitmap(
			bmp,
			dest,
			1.0f,
			D2D1_BITMAP_INTERPOLATION_MODE::D2D1_BITMAP_INTERPOLATION_MODE_NEAREST_NEIGHBOR,
			D2D1::RectF(0.0f, 0.0f,
				bmp->GetSize().width, bmp->GetSize().height)
			);

		graphics->GetRenderTarget()->SetTransform(D2D1::Matrix3x2F::Rotation(rotation, D2D1::Point2F(x, y)));
	}

}
