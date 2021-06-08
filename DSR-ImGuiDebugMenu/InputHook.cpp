#include "stdafx.h"
#include "InputHook.h"

using namespace ImGui;

extern LRESULT ImGui_ImplWin32_WndProcHandler(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

WNDPROC	oWndProc;

void InputHook::Init(HWND hWindow)
{
	oWndProc = (WNDPROC)SetWindowLongPtr(hWindow, GWLP_WNDPROC, (__int3264)(LONG_PTR)WndProc);
}

void InputHook::Remove(HWND hWindow)
{
	SetWindowLongPtr(hWindow, GWLP_WNDPROC, (LONG_PTR)oWndProc);
}

LRESULT APIENTRY WndProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch (uMsg)
	{
	case WM_CHAR:
		switch (wParam)
		{
		case '0':
			GetIO().AddInputCharacter('0');
			break;
		case '1':
			GetIO().AddInputCharacter('1');
			break;
		case '2':
			GetIO().AddInputCharacter('2');
			break;
		case '3':
			GetIO().AddInputCharacter('3');
			break;
		case '4':
			GetIO().AddInputCharacter('4');
			break;
		case '5':
			GetIO().AddInputCharacter('5');
			break;
		case '6':
			GetIO().AddInputCharacter('6');
			break;
		case '7':
			GetIO().AddInputCharacter('7');
			break;
		case '8':
			GetIO().AddInputCharacter('8');
			break;
		case '9':
			GetIO().AddInputCharacter('9');
			break;
		default:
			break;
		}
		break;
	case WM_KEYDOWN:
		switch (wParam)
		{
		case VK_BACK:
			GetIO().KeysDown[GetIO().KeyMap[ImGuiKey_Backspace]] = true; return DefWindowProc(hwnd, uMsg, wParam, lParam);
			break;
		}
		break;
	case WM_KEYUP:
		switch (wParam)
		{
		case VK_BACK:
			GetIO().KeysDown[GetIO().KeyMap[ImGuiKey_Backspace]] = false; return DefWindowProc(hwnd, uMsg, wParam, lParam);
			break;
		}
		break;
	case WM_LBUTTONDOWN:
		GetIO().MouseDown[0] = true; return DefWindowProc(hwnd, uMsg, wParam, lParam);
		break;
	case WM_LBUTTONUP:
		GetIO().MouseDown[0] = false; return DefWindowProc(hwnd, uMsg, wParam, lParam);
		break;
	case WM_RBUTTONDOWN:
		GetIO().MouseDown[1] = true; return DefWindowProc(hwnd, uMsg, wParam, lParam);
		break;
	case WM_RBUTTONUP:
		GetIO().MouseDown[1] = false; return DefWindowProc(hwnd, uMsg, wParam, lParam);
		break;
	case WM_MBUTTONDOWN:
		GetIO().MouseDown[2] = true; return DefWindowProc(hwnd, uMsg, wParam, lParam);
		break;
	case WM_MBUTTONUP:
		GetIO().MouseDown[2] = false; return DefWindowProc(hwnd, uMsg, wParam, lParam);
		break;
	case WM_MOUSEWHEEL:
		GetIO().MouseWheel += GET_WHEEL_DELTA_WPARAM(wParam) > 0 ? +1.0f : -1.0f; return DefWindowProc(hwnd, uMsg, wParam, lParam);
		break;
	case WM_MOUSEMOVE:
		GetIO().MousePos.x = (signed short)(lParam); GetIO().MousePos.y = (signed short)(lParam >> 16); return DefWindowProc(hwnd, uMsg, wParam, lParam);
		break;
	}

	return CallWindowProc(oWndProc, hwnd, uMsg, wParam, lParam);
}