#include "Game.h"
#include "Global.h"

Game::Game(HINSTANCE hInstance):CDirectXGame(hInstance)
{
}

Game::~Game()
{

}
void Game::Init()
{
	CDirectXGame::Init();
	DrawLoadingScreen();
	TextureManager::GetInstance()->InitTexture();
	//ClientManager::Instance()->Init();
	isEndGame = false;

	_MissionManager = new MissionManager(this);

	Global::Instance()->MissionManager = _MissionManager;

	//_MissionManager->GetEndGamePointer(&isEndGame);
	_MissionManager->Init();
	//LoadResources();
}
void Game::LoadResources()
{

}

void Game::Run()
{
	MSG msg;
	int done = 0;

	while (!done)
	{
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			if (msg.message == WM_QUIT) done = 1;

			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
		ProcessKeyBoard();
		ProcessInput();
		if (ClientTimeManager::Instance()->CanCreateNewFrame())
		{	
			//ClientManager::Instance()->Run();
			UpdateWorld();
			RenderFrame();
		}
		else
		{
			ClientTimeManager::Instance()->SleepToNewFrame();
		}
	}
}
void Game::UpdateWorld()
{
	if (!isEndGame)
	{
		_MissionManager->UpdateWorld();
	}
}
void Game::RenderFrame()
{
	if (_d3ddv->BeginScene())
	{
		// Clear back buffer with BLACK
		_d3ddv->ColorFill(_BackBuffer, NULL, D3DCOLOR_XRGB(0, 0, 0));
		DrawAll();
		_d3ddv->EndScene();
	}
	_d3ddv->Present(NULL, NULL, NULL, NULL);
}
void Game::DrawAll()
{
	Camera::GetInstance()->BeginDraw();
	
	if (!isEndGame)
	{
		_MissionManager->RenderFrame();
	}
	else
	{
		//_LoadingScreen->EndGameDraw();
	}
	
	Camera::GetInstance()->EndDraw();
}

void Game::End()
{
	ClientManager::Instance()->End();
	CDirectXGame::End();
}


void Game::ProcessInput()
{
	if (!isEndGame)
	{
		_MissionManager->ProcessInput();
	}
}
void Game::OnKeyDown(int KeyCode)
{
	if (!isEndGame)
	{
		_MissionManager->OnKeyDown(KeyCode);
	}
	KeyHold += 1;
	
}
void Game::OnKeyUp(int KeyCode)
{
	if (KeyHold < 1) return;
	if (!isEndGame)
	{
		_MissionManager->OnKeyUp(KeyCode);
	}
	KeyHold -= 1;
}
void Game::DrawLoadingScreen()
{
	TextureManager::GetInstance()->InitLoading();
	_LoadingScreen = new LoadingScreen();
	_LoadingScreen->Init();
	_d3ddv->BeginScene();
	if (_d3ddv->BeginScene())
	{
		Camera::GetInstance()->BeginDraw();
		_d3ddv->ColorFill(_BackBuffer, NULL, D3DCOLOR_XRGB(0, 0, 0));
		_LoadingScreen->RenderFrame();
		Camera::GetInstance()->EndDraw();
		_d3ddv->EndScene();
	}
	_d3ddv->Present(NULL, NULL, NULL, NULL);
}


