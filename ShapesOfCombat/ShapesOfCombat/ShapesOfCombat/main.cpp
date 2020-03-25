

#include <Windows.h>
#include <string>
#include "SOC_Graphics.h"
#include"SOC_Level1.h"
#include "SOC_GameController.h"

//https://www.youtube.com/watch?v=p91FvlnyOyo&list=PLKK11Ligqitij8r6hd6tfqqesh3T_xWJA

SOC_Graphics* graphics;

LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	if(uMsg == WM_DESTROY)
	{
		PostQuitMessage(0);
		return 0;
	}
	
	/*
	if (uMsg == WM_PAINT)
	{
		graphics->BeginDraw();

		// clears the screen to a certain color
		graphics->ClearScreen(1,1,0);

		// draws a non filled circle
		graphics->DrawCircle(100, 100, 50, 1.0f, 0.0, 0.0, 1.0f);

		graphics->EndDraw();
	}
	*/



	return DefWindowProc(hwnd, uMsg, wParam, lParam);
}

int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE prevInstance, LPWSTR cmd, int nCmdShow)
{
	// making the window appear
	std::string className = "MainWindow";
	std::wstring ctemp = std::wstring(className.begin(), className.end());
	LPCWSTR actualClassName = ctemp.c_str();

	std::string windowName = "DirectXTutorial";
	std::wstring wtemp = std::wstring(windowName.begin(), windowName.end());
	LPCWSTR actualWindowName = wtemp.c_str();

	WNDCLASSEX windowClass;
	ZeroMemory(&windowClass, sizeof(WNDCLASSEX));

	windowClass.cbSize = sizeof(WNDCLASSEX);
	windowClass.hbrBackground = (HBRUSH)COLOR_WINDOW;
	windowClass.hInstance = hInstance;
	windowClass.lpfnWndProc = WindowProc;
	windowClass.lpszClassName = actualClassName;
	windowClass.style = CS_HREDRAW | CS_VREDRAW;

	RegisterClassEx(&windowClass);

	RECT rect{ 0,0,800,600 };
	AdjustWindowRectEx(&rect, WS_OVERLAPPEDWINDOW, false, WS_EX_OVERLAPPEDWINDOW);

	HWND windowHandle = CreateWindow(windowClass.lpszClassName, actualWindowName, WS_OVERLAPPEDWINDOW, 100,100,
		rect.right - rect.left, rect.bottom - rect.top, NULL, NULL, hInstance,0);

	if (!windowHandle)
	{
		return -1;
	}

	graphics = new SOC_Graphics();
	if (!graphics->Init(windowHandle))
	{
		delete graphics;
		return -1;
	}

	SOC_GameLevel::Init(graphics);

	ShowWindow(windowHandle, nCmdShow);

	SOC_GameController::LoadInitialLevel(new SOC_Level1());

	MSG message;
	message.message = WM_NULL;
	while (message.message != WM_QUIT)
	{
		if (PeekMessage(&message, NULL, 0, 0, PM_REMOVE))
		{
			DispatchMessage(&message);
		}
		else
		{
			SOC_GameController::Update();
			// render
			graphics->BeginDraw();
			SOC_GameController::Render();

			graphics->EndDraw();

		}
	}

	/*
	MSG message;a6
	while (GetMessage(&message, NULL, 0, 0))
	{
		DispatchMessage(&message);
	}
	*/
	// done with the window stuff

	delete graphics;
	return 0;
}