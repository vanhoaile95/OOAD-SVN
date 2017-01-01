#define GAME_STATE
#ifdef GAME_STATE
#pragma once
enum GameState
{
	Loading,
	MainMenuScene,
	MultiplayerMenuScene,
	WinGameStateScene,
	Pause,
	EndGame,

	Map1,
	Map2,
	Map3,
};
#endif