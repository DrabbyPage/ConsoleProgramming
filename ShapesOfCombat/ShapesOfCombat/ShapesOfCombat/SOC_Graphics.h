

#ifndef SOC_GRAPHICS_H
#define SOC_GRAPHICS_H

#include <d2d1.h>
#include "SOC_Vector.h"

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
	void DrawRectangle(float left, float top, float right, float bottom, float r, float g, float b, float a);

	SOC_Vector2 GetCursorPosFromGraphics();

	void SetWindowPos(SOC_Vector2 newWinPos) { windowPos = newWinPos; }
	SOC_Vector2 GetWindowSize() { return windowSize; }
private:
	ID2D1Factory* factory;
	ID2D1HwndRenderTarget* renderTarget;
	ID2D1SolidColorBrush* brush;

	SOC_Vector2 windowPos;
	SOC_Vector2 windowSize;
	SOC_Vector2 cursorPos;

	HWND graphicsWindowHandler;

};


#endif // !SOC_GRAPHICS_H
