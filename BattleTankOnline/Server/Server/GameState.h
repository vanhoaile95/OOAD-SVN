#define GAME_STATE
#ifdef GAME_STATE
#pragma once
enum GameState
{
	Loading,
	Running,
	MainMenuScene,
	MultiplayerMenuScene,
	Pause,
	EndGame,

	Map1,
	Map2,
	Map3,
};
#endif