#ifndef MISSION_MANAGER_H
#define MISSION_MANAGER_H

#include <map>
#include "Mission.h"
#include "UI.h"
#include "DirectXGame.h"
#include "GameStatusBar.h"
#include "GameState.h"

class MissionManager
{
public:

	//TankPlayer* _Mario;
	CDirectXGame* _DirectXGame;
	//GameStatusBar* _StatusBar;
	
	map<GameState,Scene*> _listScene;

	GameState CurrentState;
	Scene* CurrentScene;

	bool *IsEndGame;
	bool IsPause;

	MissionManager(CDirectXGame* DirectXGame);
	~MissionManager();

	

	void Init();

	void GetAllMission();

	void UpdateWorld();
	void RenderFrame();
	void EndMission();

	virtual void Control(GameState State);
	void GotoScene(GameState State);
	void GotoWinGameStateScene(GameState State, RECT * TankRECT);

	void ProcessInput();
	void OnKeyDown(int KeyCode);
	void OnKeyUp(int KeyCode);
};

#endif