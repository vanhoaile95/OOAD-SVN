#ifndef GAME_SCORE_H
#define GAME_SCORE_H
#pragma once
#include <stdlib.h>
#include "ConfigsManager.h"

enum ScoreEvent
{
	KILL_SIMPLE_ENEMY,
	FLY_TO_SIMPLE_ENEMY, 
	KILL_FLY_ENEMY,
	NORMAL_TO_SHELL_TURTLE,
	FLY_TO_NORMAL_FLYTURTLE,
	NORMAL_TO_SHELL_FLYTURTLE,
	KICK_TURTLE_SHELL,
	GET_COIN,
	GET_POWERUP,
	GET_ONEUP,
};

class GameScore
{
private:
	int _Score;
	int _Coin;
	static GameScore* Instance;
	GameScore();
	~GameScore();
public:
	static GameScore* GetInstance(); 
	void AddScore(ScoreEvent Event, float X = 0, float Y = 0);
	int* GetScorePointer();
	int* GetCoinPointer();
	void ResetGame();
};
#endif