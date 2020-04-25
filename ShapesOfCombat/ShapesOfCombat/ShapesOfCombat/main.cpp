
#include <Windows.h>
#include <string>
#include "GameInput.h"
#include "SOC_Graphics.h"
#include"SOC_Level1.h"
#include "SOC_GameController.h"
#include <iostream>
#include <Xinput.h>
#include "GamePad.h"
//https://www.youtube.com/watch?v=p91FvlnyOyo&list=PLKK11Ligqitij8r6hd6tfqqesh3T_xWJA

using namespace std;

SOC_Graphics* graphics;
Gamepad gamepad; // Gamepad instance


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


// This example checks input on all gamepad buttons (Guide/logo
// button not supported). For example code on using the triggers
// and thumbsticks, please refer to the tutorial.
GameInput TestInput()
{
	// GetButtonDown only returns true on the frame it was first pressed.
	if (gamepad.GetButtonDown(xButtons.A) || GetKeyState(VK_S) ||
		gamepad.GetButtonDown(xButtons.DPad_Down) )
	{
		cout << " Button [A] pressed" << endl;
		//PostQuitMessage(0);
		return GameInput::down;
	}

	if (gamepad.GetButtonDown(xButtons.X) || GetKeyState(VK_A) ||
		gamepad.GetButtonDown(xButtons.DPad_Left) )
	{
		cout << " Button [X] pressed" << endl;
		//PostQuitMessage(0);
		return GameInput::left;
	}

	// GetButtonPressed will keep returning true until the button is released.
	if (gamepad.GetButtonPressed(xButtons.Y) || GetKeyState(VK_W) ||
		gamepad.GetButtonDown(xButtons.DPad_Up) )
	{
		cout << " Button [Y] held, see how this doesn't appear just once?" << endl;
		//PostQuitMessage(0);
		return GameInput::up;
	}

	if (gamepad.GetButtonDown(xButtons.B) || GetKeyState(VK_D) || 
		gamepad.GetButtonDown(xButtons.DPad_Right) )
	{
		cout << " Button [B] pressed" << endl;
		//PostQuitMessage(0);
		return GameInput::right;
	}

	return GameInput::null;

	// Check the D-Pad buttons
	if (gamepad.GetButtonDown(xButtons.DPad_Up))
	{
		cout << " Button [DPad Up] pressed" << endl;
	}

	if (gamepad.GetButtonDown(xButtons.DPad_Down))
	{
		cout << " Button [DPad Down] pressed" << endl;
	}

	if (gamepad.GetButtonDown(xButtons.DPad_Left))
	{
		cout << " Button [DPad Left] pressed" << endl;
	}

	if (gamepad.GetButtonDown(xButtons.DPad_Right))
	{
		cout << " Button [DPad Right] pressed" << endl;
	}

	// Check the Shoulder ('bumper') buttons
	if (gamepad.GetButtonDown(xButtons.L_Shoulder))
	{
		cout << " Button [L Bumper] pressed" << endl;
	}

	if (gamepad.GetButtonDown(xButtons.R_Shoulder))
	{
		cout << " Button [R Bumper] pressed" << endl;
	}

	// Check the BACK and START buttons
	if (gamepad.GetButtonDown(xButtons.Back))
	{
		cout << " Button [BACK] pressed" << endl;
	}

	if (gamepad.GetButtonDown(xButtons.Start))
	{
		cout << " Button [START] pressed" << endl;
	}

	// Check the Thumbstick buttons (press in the thumbstick)
	if (gamepad.GetButtonDown(xButtons.L_Thumbstick))
	{
		cout << " Button [L STICK] pressed" << endl;
	}

	if (gamepad.GetButtonDown(xButtons.R_Thumbstick))
	{
		cout << " Button [R STICK] pressed" << endl;
	}
}


// LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	if (gamepad.GetButtonDown(xButtons.A))
	{
		//PostQuitMessage(0);
	}
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
	case VK_W:
	case VK_UP:
	case XINPUT_GAMEPAD_DPAD_UP:
	case XINPUT_GAMEPAD_Y:
	{
		//PostQuitMessage(0);
		break;
	}
	case VK_A:
	case VK_LEFT:
	case XINPUT_GAMEPAD_DPAD_LEFT:
	case XINPUT_GAMEPAD_X:
	{
		//PostQuitMessage(0);
		break;
	}
	case VK_S:
	case VK_DOWN:
	case XINPUT_GAMEPAD_DPAD_DOWN:
	case XINPUT_GAMEPAD_A:
	{
		break;
	}
	case VK_D:
	case VK_RIGHT:
	case XINPUT_GAMEPAD_DPAD_RIGHT:
	case XINPUT_GAMEPAD_B:
	{
		break;
	}
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
	gamepad = Gamepad(1); // Set gamepad ID to 1

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
			gamepad.Update(); // Update gamepad

			TestInput();

			SOC_GameController::Update(TestInput());
			// render
			SOC_GameController::Render();


			/*
			if (gamepad.Connected())
			{
				// Run gamepad input test
				//TestGamepad();
				TestInput();
			}
			*/
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