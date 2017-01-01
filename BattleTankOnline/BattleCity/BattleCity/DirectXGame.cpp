#include "DirectXGame.h"


CDirectXGame::CDirectXGame(HINSTANCE hInstance) : CWindows(hInstance)
{
	_d3d = NULL;
	_d3ddv = NULL;
	_BackBuffer = NULL;
	_di = NULL;
	_Keyboard = NULL;
}

CDirectXGame::~CDirectXGame()
{
	
}

void CDirectXGame::InitDirectX()
{
	_d3d = Direct3DCreate9(D3D_SDK_VERSION);

	D3DPRESENT_PARAMETERS d3dpp;
	ZeroMemory(&d3dpp, sizeof(d3dpp));

	d3dpp.Windowed = FULL_SCREEN ? FALSE : TRUE;

	d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;

	d3dpp.BackBufferFormat = BACK_BUFFER_FORMAT;
	d3dpp.BackBufferCount = 1;
	d3dpp.BackBufferHeight = SCREEN_HEIGHT;
	d3dpp.BackBufferWidth = SCREEN_WIDTH;

	_d3d->CreateDevice(
		D3DADAPTER_DEFAULT,
		D3DDEVTYPE_HAL,
		_hWnd,
		D3DCREATE_SOFTWARE_VERTEXPROCESSING,
		&d3dpp,
		&_d3ddv);

	if (_d3ddv == NULL)
	{

	}
	_d3ddv->GetBackBuffer(0, 0, D3DBACKBUFFER_TYPE_MONO, &_BackBuffer);

}

void CDirectXGame::EndDirectX()
{
	if (_BackBuffer != NULL)
	{
		_BackBuffer->Release();
		_BackBuffer = NULL;
	}

	if (_d3ddv != NULL)
	{
		_d3ddv->Release();
		_d3ddv = NULL;
	}

	if (_d3d != NULL)
	{
		_d3d->Release();
		_d3d = NULL;
	}
}

void CDirectXGame::Init()
{
	InitWindow();
	InitDirectX();
	InitKeyboard();
	InitDirectXSound(_hWnd);
	GameSound::GetInstance()->InitSound();
	ClientTimeManager::Instance()->Init();


	D3DXCreateSprite(_d3ddv, &Camera::GetInstance()->_SpriteHandler);
	TextureManager::GetInstance()->GetD3DDevice(&_d3ddv);
	TextureManager::GetInstance()->GetSpriteHandler(&Camera::GetInstance()->_SpriteHandler);
}

void CDirectXGame::End()
{
	EndWindow();
	EndDirectX();
	EndKeyboard();
}

void CDirectXGame::InitKeyboard()
{
	HRESULT
		hr = DirectInput8Create
		(
			_hInstance,
			DIRECTINPUT_VERSION,
			IID_IDirectInput8, (VOID**) &_di, NULL
			);

	// TO-DO: put in exception handling
	if (hr != DI_OK) return;

	//trace(L"DirectInput has been created");

	hr = _di->CreateDevice(GUID_SysKeyboard, &_Keyboard, NULL);

	// TO-DO: put in exception handling
	if (hr != DI_OK) return;

	//trace(L"DirectInput keyboard has been created");

	// Set the data format to "keyboard format" - a predefined data format 
	//
	// A data format specifies which controls on a device we
	// are interested in, and how they should be reported.
	//
	// This tells DirectInput that we will be passing an array
	// of 256 bytes to IDirectInputDevice::GetDeviceState.

	hr = _Keyboard->SetDataFormat(&c_dfDIKeyboard);

	//trace(L"SetDataFormat for keyboard successfully");

	hr = _Keyboard->SetCooperativeLevel(_hWnd, DISCL_FOREGROUND | DISCL_NONEXCLUSIVE);

	//trace(L"SetCooperativeLevel for keyboard successfully");

	// IMPORTANT STEP TO USE BUFFERED DEVICE DATA!
	//
	// DirectInput uses unbuffered I/O (buffer size = 0) by default.
	// If you want to read buffered data, you need to set a nonzero
	// buffer size.
	//
	// Set the buffer size to DINPUT_BUFFERSIZE (defined above) elements.
	//
	// The buffer size is a DWORD property associated with the device.
	DIPROPDWORD dipdw;

	dipdw.diph.dwSize = sizeof(DIPROPDWORD);
	dipdw.diph.dwHeaderSize = sizeof(DIPROPHEADER);
	dipdw.diph.dwObj = 0;
	dipdw.diph.dwHow = DIPH_DEVICE;
	dipdw.dwData = KEYBOARD_BUFFER_SIZE; // Arbitary buffer size

	//trace(L"SetProperty for keyboard successfully");

	hr = _Keyboard->SetProperty(DIPROP_BUFFERSIZE, &dipdw.diph);
	if (hr != DI_OK) return;

	hr = _Keyboard->Acquire();
	if (hr != DI_OK) return;

	//trace(L"Keyboard has been acquired successfully");
}

void CDirectXGame::EndKeyboard()
{
	if (_Keyboard)
	{
		_Keyboard->Unacquire();
		_Keyboard->Release();
	}

	if (_di) _di->Release();
}

void CDirectXGame::RenderFrame()
{
	if (_d3ddv->BeginScene())
	{
		// Clear back buffer with BLACK
		_d3ddv->ColorFill(_BackBuffer, NULL, D3DCOLOR_XRGB(156, 252, 240));
		DrawAll();
		_d3ddv->EndScene();
	}
	_d3ddv->Present(NULL, NULL, NULL, NULL);
}

void CDirectXGame::DrawAll()
{
	_d3ddv->ColorFill(_BackBuffer, NULL, D3DCOLOR_XRGB(156,252,240));
}

void CDirectXGame::UpdateWorld(int Delta) {}

int CDirectXGame::IsKeyDown(int KeyCode)
{
	return (_KeyStates[KeyCode] & 0x80) > 0;
}
void CDirectXGame::OnKeyUp(int KeyCode) { }

void CDirectXGame::OnKeyDown(int KeyCode) { }

void CDirectXGame::ProcessKeyBoard()
{
	// Collect all key states first
	_Keyboard->Poll();
	if (FAILED(_Keyboard->GetDeviceState(sizeof(_KeyStates), (LPVOID) &_KeyStates)))
	{
		//keyboard device lost, try to re-acquire
		_Keyboard->Acquire();
	}

	_Keyboard->GetDeviceState(sizeof(_KeyStates), (LPVOID) &_KeyStates);

	if (IsKeyDown(DIK_ESCAPE))
	{
		PostMessage(_hWnd, WM_QUIT, 0, 0);
	}

	// Collect all buffered events
	DWORD dwElements = KEYBOARD_BUFFER_SIZE;
	HRESULT hr = _Keyboard->GetDeviceData(sizeof(DIDEVICEOBJECTDATA), _KeyEvents, &dwElements, 0);


	

	// Scan through all data, check if the key is pressed or released
	for (DWORD i = 0; i < dwElements; i++)
	{
		int KeyCode = _KeyEvents[i].dwOfs;
		int KeyState = _KeyEvents[i].dwData;
		if ((KeyState & 0x80) > 0)
			OnKeyDown(KeyCode);
		else
			OnKeyUp(KeyCode);
	}
}
void CDirectXGame::ProcessInput() { }