#ifndef WIN_GAME_SCENE_H
#define WIN_GAME_SCENE_H
#pragma once
#include "UI.h"
#include "MultiPlayerHud.h"

class WinGameScene : public UI
{
public:
	WinGameScene();
	~WinGameScene();

	MultiPlayerHud* MultiplayerHud;
	UIObject * WhiteTeamWin, *GreenTeamWin;
public:
	virtual void Init();
	virtual void UpdateData();
	virtual void RenderFrame();
	virtual void UpdateWorld();

	virtual void ProcessInput() {};
	virtual void OnKeyDown(int KeyCode);
	virtual void OnKeyUp(int KeyCode);
};
#endif //WIN_GAME_SCENE_H
