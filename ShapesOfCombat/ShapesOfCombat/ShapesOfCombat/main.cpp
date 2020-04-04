

#include <Windows.h>
#include <string>
#include "SOC_Graphics.h"
#include"SOC_Level1.h"
#include "SOC_GameController.h"
#include <iostream>
//https://www.youtube.com/watch?v=p91FvlnyOyo&list=PLKK11Ligqitij8r6hd6tfqqesh3T_xWJA

SOC_Graphics* graphics;

/*
 * VK_0 - VK_9 are the same as ASCII '0' - '9' (0x30 - 0x39)
 * 0x3A - 0x40 : unassigned
 * VK_A - VK_Z are the same as ASCII 'A' - 'Z' (0x41 - 0x5A)
 */

enum KeyboardKey
{
	VK_0 = 0x30,
	VK_1 = 0x31,
	VK_2 = 0x32,
	VK_3 = 0x33,
	VK_4 = 0x34,
	VK_5 = 0x35,
	VK_6 = 0x36,
	VK_7 = 0x37,
	VK_8 = 0x38,
	VK_9 = 0x39,
	VK_A = 0x41,
	VK_B = 0x42,
	VK_C = 0x43,
	VK_D = 0x44,
	VK_E = 0x45,
	VK_F = 0x46,
	VK_G = 0x47,
	VK_H = 0x48,
	VK_I = 0x49,
	VK_J = 0x4A,
	VK_K = 0x4B,
	VK_L = 0x4C,
	VK_M = 0x4D,
	VK_N = 0x4E,
	VK_O = 0x4F,
	VK_P = 0x50,
	VK_Q = 0x51,
	VK_R = 0x52,
	VK_S = 0x53,
	VK_T = 0x54,
	VK_U = 0x55,
	VK_V = 0x56,
	VK_W = 0x57,
	VK_X = 0x58,
	VK_Y = 0x59,
	VK_Z = 0x5A,
};

// LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch (uMsg)
	{
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	case WM_KEYDOWN:

		break;
	default:
		break;
	}

	switch (uMsg)
	{
	case WM_ACTIVATEAPP:

		break;

	case WM_KEYDOWN:
	case WM_SYSKEYDOWN:

		break;

	case WM_KEYUP:
	case WM_SYSKEYUP:
		break;

	default:
		break;
	}

	int vk = static_cast<int>(wParam);
	switch (vk)
	{


	case VK_SHIFT:
		// to test it PostQuitMessage(0);
		break;
	case VK_A:
		// to test is PostQuitMessage(0);
		break;
	case VK_CONTROL:
		vk = (static_cast<UINT>(lParam) & 0x01000000) ? VK_RCONTROL : VK_LCONTROL;
		break;

	case VK_MENU:
		break;
	}
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

	SOC_Vector2 windowPos = SOC_Vector2(0, 0);

	HWND windowHandle = CreateWindow(windowClass.lpszClassName, actualWindowName, WS_OVERLAPPEDWINDOW, (int)windowPos.xVal, (int)windowPos.yVal,
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

	SOC_GameController::LoadInitialLevel(new SOC_Level1(), windowHandle, windowPos);

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