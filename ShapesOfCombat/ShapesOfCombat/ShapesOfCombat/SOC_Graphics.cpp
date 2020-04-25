
#include "SOC_Graphics.h"


SOC_Graphics::SOC_Graphics()
{
	factory = NULL;
	renderTarget = NULL;


	brush = NULL;
}

SOC_Graphics::~SOC_Graphics()
{
	if (factory)
	{
		factory->Release();
	}

	if (renderTarget)
	{
		renderTarget->Release();
	}

	if (brush)
	{
		brush->Release();
	}
}

bool SOC_Graphics::Init(HWND windowHandle)
{
	HRESULT res = D2D1CreateFactory(D2D1_FACTORY_TYPE::D2D1_FACTORY_TYPE_SINGLE_THREADED, &factory);

	if (res != S_OK)
	{
		return false;
	}

	RECT rect;
	GetClientRect(windowHandle, &rect);

	res = factory->CreateHwndRenderTarget(
		D2D1::RenderTargetProperties(),
		D2D1::HwndRenderTargetProperties(windowHandle, D2D1::SizeU(rect.right, rect.bottom)),
		&renderTarget);

	windowSize = SOC_Vector2((float)rect.right, (float)rect.bottom);

	if(res != S_OK)
	{
		return false;
	}

	D2D1::ColorF defaultColor = (0, 0, 0, 1);

	res = renderTarget->CreateSolidColorBrush(defaultColor, &brush);

	if (res != S_OK)
	{
		return false;
	}

	return true;
}

void SOC_Graphics::ClearScreen(float r, float g, float b)
{
	renderTarget->Clear(D2D1::ColorF(r, g, b));
}

void SOC_Graphics::DrawCircle(float x, float y, float radius, float r, float g, float b, float a)
{
	brush->SetColor(D2D1::ColorF(r, g, b, a));
	renderTarget->CreateSolidColorBrush(D2D1::ColorF(r, g, b, a), &brush);
	renderTarget->DrawEllipse(D2D1::Ellipse(D2D1::Point2F(x, y), radius, radius), brush, 3.0f);

}

SOC_Vector2 SOC_Graphics::GetCursorPosFromGraphics()
{
	POINT actualCursorPos;
	GetCursorPos(&actualCursorPos);
	cursorPos = SOC_Vector2(actualCursorPos.x + windowPos.xVal, actualCursorPos.y + windowPos.yVal);
	return cursorPos;
}
