#include "DirectXWindows.h"

CWindows::CWindows(HINSTANCE hInstance)
{
	this->_hInstance = hInstance;
}
void CWindows::InitWindow()
{
	WNDCLASSEX wc;
	wc.cbSize = sizeof(WNDCLASSEX);

	wc.style = CS_HREDRAW | CS_VREDRAW;
	wc.hInstance = _hInstance;

	wc.lpfnWndProc = (WNDPROC) _WinProc;
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.hIcon = NULL;
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);
	wc.hbrBackground = (HBRUSH) GetStockObject(WHITE_BRUSH);
	wc.lpszMenuName = NULL;
	wc.lpszClassName = GAME_NAME;
	wc.hIconSm = NULL;

	RegisterClassEx(&wc);

	DWORD style;
	if (FULL_SCREEN)
		style = WS_EX_TOPMOST | WS_VISIBLE | WS_POPUP;
	else
		style = WS_OVERLAPPEDWINDOW;

	_hWnd =
		CreateWindow(
			GAME_NAME,
			GAME_NAME,
			style,
			CW_USEDEFAULT,
			CW_USEDEFAULT,
			SCREEN_WIDTH,
			SCREEN_HEIGHT,
			NULL,
			NULL,
			_hInstance,
			NULL);

	if (!_hWnd)
	{
		//trace(L"[ERROR] Failed to created window!");
		DWORD ErrCode = GetLastError();
	}

	ShowWindow(_hWnd, SW_SHOWNORMAL);
	UpdateWindow(_hWnd);
}

void CWindows::EndWindow()
{
	if (_hWnd)
	{
		DestroyWindow(_hWnd);
	}
}

LRESULT CALLBACK CWindows::_WinProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}
	return 0;
}

CWindows::~CWindows()
{

}
