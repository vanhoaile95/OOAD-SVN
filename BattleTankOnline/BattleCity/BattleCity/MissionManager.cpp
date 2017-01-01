#include "MissionManager.h"
#include "MainMenu.h"
#include "MultiplayerMain.h"
#include "WinGameScene.h"

MissionManager::MissionManager(CDirectXGame* DirectXGame)
{
	_DirectXGame = DirectXGame;
	//_Mario = new MarioPlayer(0, 0,MARIO_INIT_LEVEL);
	//_StatusBar = new GameStatusBar();
	CurrentState = GameState::Loading;
	IsPause = false;
	//*IsEndGame = false;
}
void MissionManager::ProcessInput()
{
	if (!IsPause)// && !_CurrentMission->IsWining())
	{
		CurrentScene->ProcessInput();
	}
}
void MissionManager::OnKeyDown(int KeyCode)
{
	if (!IsPause )// && !_CurrentMission->IsWining())
	{
		if (KeyCode == DIK_RETURN)
		{
			if (CurrentState == GameState::MainMenuScene)
			{
				if (CurrentScene->GetValue() == SelectedValue::SinglePlayerMode)
					Control(GameState::Map1);
				else if (CurrentScene->GetValue() == SelectedValue::MultiPlayerMode)
				{
					Control(GameState::MultiplayerMenuScene);
				}
					
			}
			else if (CurrentState == GameState::MultiplayerMenuScene)
			{
				CurrentScene->HandlerAction(CurrentScene->GetValue());
			}
			else if (CurrentState == GameState::WinGameStateScene)
			{
			}
		}
		else if (KeyCode == DIK_F1 && CurrentState != GameState::MainMenuScene)
		{
			Control(GameState::MainMenuScene);
		}
		else
		{
			CurrentScene->OnKeyDown(KeyCode);
		}
	}
	else
	{
		switch (KeyCode)
		{
		case DIK_V:
			IsPause = !IsPause;
			break;
		}
	}
}
void MissionManager::OnKeyUp(int KeyCode)
{
	if (!IsPause) 
	{
		CurrentScene->OnKeyUp(KeyCode);
	}
}

MissionManager::~MissionManager()
{

}



void MissionManager::Init()
{
	GetAllMission();
	Control(GameState::MainMenuScene);
	//Control(GameState::WinGameStateScene);
}
void MissionManager::GetAllMission()
{
	
	Scene* mission1 = new Mission();
	pair<GameState, Scene*> p1(GameState::Map1, mission1);
	_listScene.insert(p1);

	Scene* main = new MainMenu();
	pair<GameState, Scene*> pmain(GameState::MainMenuScene, main);
	_listScene.insert(pmain);

	Scene* multiplayermain = new MultiplayerMain();
	pair<GameState, Scene*> pmulmain(GameState::MultiplayerMenuScene, multiplayermain);
	_listScene.insert(pmulmain);

	Scene* winscene = new WinGameScene();
	pair<GameState, Scene*> pwinscene(GameState::WinGameStateScene, winscene);
	_listScene.insert(pwinscene);
}
void MissionManager::UpdateWorld()
{
	CurrentScene->UpdateWorld();
	if (CurrentScene->Value == SelectedValue::WinGameMode)
	{
		Control(GameState::WinGameStateScene);
	}
}
void MissionManager::RenderFrame()
{
	CurrentScene->RenderFrame();
}
void MissionManager::EndMission()
{

}

void MissionManager::Control(GameState State)
{
	switch (State)
	{
	case Loading:
		break;
	case MainMenuScene:
	case MultiplayerMenuScene:
	case WinGameStateScene:
	case Map1:
	case Map2:
	case Map3:
		GotoScene(State);
		break;
		break;
	case Pause:
		break;
	case EndGame:
		break;
	default:
		break;
	}
}
void MissionManager::GotoScene(GameState State)
{
	CurrentState = State;
	CurrentScene = _listScene.find(State)->second;
	CurrentScene->Init();
	CurrentScene->UpdateData();
}
