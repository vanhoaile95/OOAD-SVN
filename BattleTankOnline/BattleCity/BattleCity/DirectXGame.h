#ifndef DIRECTX_GAME_H
#define DIRECTX_GAME_H
#pragma once
#include <d3d9.h>
#include <d3dx9.h>
#include <dinput.h>
#include "DirectXWindows.h"
#include "TextureManager.h"

#include "GameSound.h"
#include "ClientTimeManager.h"
#include "Camera.h"


class CDirectXGame: CWindows
{
public:
	LPDIRECT3D9 _d3d;
	LPDIRECT3DDEVICE9 _d3ddv;		// Rendering device
	LPDIRECT3DSURFACE9 _BackBuffer;	// Pointer to backbuffer 

	LPDIRECTINPUT8       _di;		// The DirectInput object         
	LPDIRECTINPUTDEVICE8 _Keyboard;	// The keyboard device 

	BYTE  _KeyStates[256];			// DirectInput keyboard state buffer 

	DIDEVICEOBJECTDATA _KeyEvents[KEYBOARD_BUFFER_SIZE];



public:

	CDirectXGame(HINSTANCE hInstance);
	~CDirectXGame();
	
	void Init();
	void End();
	void InitDirectX();
	void EndDirectX();
	void InitKeyboard();
	void EndKeyboard();
	virtual void RenderFrame();
	virtual void DrawAll();
	virtual void UpdateWorld(int Delta);
	int IsKeyDown(int KeyCode);
	virtual void OnKeyUp(int KeyCode);
	virtual void OnKeyDown(int KeyCode);
	void ProcessKeyBoard();
	virtual void ProcessInput();
};
#endif
