#ifndef GAME_H
#define GAME_H
#pragma once
#include "ClientManager.h"
#include "MissionManager.h"
#include "LoadingScreen.h"
#include "DirectXGame.h"


class Game: public CDirectXGame
{
private:
	LoadingScreen* _LoadingScreen;
	int KeyHold = 0;
public:
	bool isEndGame;
	MissionManager *_MissionManager;
	Game(HINSTANCE hInstance);
	~Game();
	void LoadResources();
	void Run();
	void Init();
	void End();
	void UpdateWorld();
	void RenderFrame();
	void DrawAll();
	void ProcessInput();
	void OnKeyDown(int KeyCode);
	void OnKeyUp(int KeyCode);
	void DrawLoadingScreen();
};
#endif
