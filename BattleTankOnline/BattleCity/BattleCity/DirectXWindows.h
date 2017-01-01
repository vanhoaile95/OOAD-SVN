#ifndef DIRECTX_WINDOWS_H
#define DIRECTX_WINDOWS_H
#pragma once
#include <Windows.h>
#include "ConfigsManager.h"


class CWindows
{
protected:
	HINSTANCE _hInstance;	// Handle of the game instance
	HWND _hWnd;				// Handle of the Game Window
	HICON _hIcon;
public:
	CWindows(HINSTANCE hInstance);
	void InitWindow();
	void EndWindow();
	static LRESULT CALLBACK _WinProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
	~CWindows();
};

#endif