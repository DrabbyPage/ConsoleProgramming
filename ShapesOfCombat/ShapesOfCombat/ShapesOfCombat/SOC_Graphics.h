

#ifndef SOC_GRAPHICS_H
#define SOC_GRAPHICS_H

#include <d2d1.h>

class SOC_Graphics
{
public:
	SOC_Graphics();
	~SOC_Graphics();

	bool Init(HWND windowHandle);

	ID2D1RenderTarget* GetRenderTarget()
	{
		return renderTarget;
	}

	void BeginDraw() { renderTarget->BeginDraw(); }
	void EndDraw() { renderTarget->EndDraw(); }

	void ClearScreen(float r, float g, float b);
	void DrawCircle(float x, float y, float radius, float r, float g, float b, float a);

private:
	ID2D1Factory* factory;
	ID2D1HwndRenderTarget* renderTarget;
	ID2D1SolidColorBrush* brush;

};


#endif // !SOC_GRAPHICS_H
