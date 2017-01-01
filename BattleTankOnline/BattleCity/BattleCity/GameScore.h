#ifndef GAME_SCORE_H
#define GAME_SCORE_H
#pragma once
#include <stdlib.h>
#include "ConfigsManager.h"

enum ScoreEvent
{
	Score_LightTank1,
	Score_LightTank2,
	Score_DetroyerTank1,
	Score_DetroyerTank2,
	Score_RapidTank1,
	Score_ArmoredVehicle,
	Score_HeavyTank1,
	Score_HeavyTank2,
};
struct TankBattleInfo
{

	//Multi
	int UID = -1;
	int Kill = 0;
	int Death = 0;
};
struct MissionInfo
{
	int Kill[7];
};
class GameScore
{
private:
	static GameScore* _instance;
	
	GameScore();
	~GameScore();
public:
	TankBattleInfo* MulTiplayerInfo[4];
	MissionInfo* SinglePlayerInfo;
	int TotalScore = 0;

	int WinState = 1;
public:
	static GameScore* Instance();

	void ResetGame();

	void GetScore(int type);

	void Kill(int tankid);
};
#endif